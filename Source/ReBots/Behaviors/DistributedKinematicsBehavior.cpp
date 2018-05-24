// Fill out your copyright notice in the Description page of Project Settings.
///TODO: What if I am an end-effector and the leader?
 
#include "DistributedKinematicsBehavior.h"
/**
* @brief constructor
*/
DistributedKinematicsBehavior::DistributedKinematicsBehavior() {
	Init();
	this->Name = "DistributedKinematics";
	HasReturned = std::vector<bool>(6);
	HasReturnedDFK = std::vector<bool>(6);
	for (int i = 0; i < 6; i++) {
		HasReturned[i] = false;
		HasReturnedDFK[i] = false;
	}

}
/**
* @brief constructor
* @param W world
* @param NameOfModule name of module
*/
DistributedKinematicsBehavior::DistributedKinematicsBehavior(UWorld* W, std::string NameOfModule) {

	this->Name = "DistributedKinematics";
	this->World = W;
	this->ModuleName = NameOfModule;

	TActorIterator< ASuperBotModule > SuperBotIt = TActorIterator< ASuperBotModule >(World);
	vector<int> SuperbotIDs;
	while (SuperBotIt) {
		SuperbotIDs.push_back((*SuperBotIt)->GetIDNumber());
		if ((*SuperBotIt)->GetName().compare(ModuleName) == 0) {
			SModule = *SuperBotIt;
		}
		++SuperBotIt;
	}

	NumModuleConnectors = SModule->GetNumConnectors();
	Init();

	TActorIterator<AStackableObjectActor> StackableIt = TActorIterator <AStackableObjectActor>(World);
	if (this->SModule->GetIDNumber() == SuperbotIDs[0]) {
		GEngine->AddOnScreenDebugMessage(1, 10.0, FColor::Red, FString("I am leader"));
		SModule->SetModuleColor(SUPERBOT_BLUE);
		this->AmILeader = true;
	}
	else {
		this->AmILeader = false;
	}
	HasReturned = std::vector<bool>(NumModuleConnectors);
	HasReturnedDFK = std::vector<bool>(NumModuleConnectors);
	for (int i = 0; i < NumModuleConnectors; i++) {
		HasReturned[i] = false;
		HasReturnedDFK[i] = false;
	}
}
/**
* @brief destructor
*/
DistributedKinematicsBehavior::~DistributedKinematicsBehavior() {}



/**
* @brief find pose relative to foot and update number of end effectors
* @return true if completed, false otherwise
*/
bool DistributedKinematicsBehavior::FindPoseToFootAndEndEffectors() {
	if (CanSendMessage && !AmIEngagedToGround && !AmIEndEffector) {
		CanSendMessage = false;
		for (int i = 0; i < NumModuleConnectors; i++) {
			TreeMessage tm;
			tm.Command = "FootProbe";
			ModuleDockFace cDock = (ModuleDockFace)i;
			tm.DockStack.push(cDock);
			if (CurrentDockEngagedStatus[cDock]) {
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(cDock), tm));
			}
			else {
				HasReturned[cDock] = true;
			}
		}
	}
	else if (CanSendMessage && AmIEngagedToGround) {
		CanSendMessage = false;
		ModuleDockFace GroundDockFace = DOCK_0;
		if (CurrentDockEngagedToGroundStatus[DOCK_1]) {
			GroundDockFace = DOCK_1;
		}
		HasReturned[GroundDockFace] = true;
		ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
		FTransform T = SuperbotKinematics::computeTransformFromDock(mv, GroundDockFace)*
			SuperbotKinematics::computeTransformToDock(mv, GroundDockFace)*
			ASuperBotModule::SuperbotFix*(SModule)->GetMasterInnerMesh()->GetComponentTransform();
		CurrentTransform = T;

		for (int i = 0; i < NumModuleConnectors; i++) {
			if ((ModuleDockFace)i != GroundDockFace) {
				TreeMessage tm;
				tm.Command = "FootProbe";
				ModuleDockFace cDock = (ModuleDockFace)i;
				tm.DockStack.push(cDock);
				if (CurrentDockEngagedStatus[cDock]) {
					AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(cDock), tm));
				}
				else {
					HasReturned[cDock] = true;
				}
			}
		}
	}
	else if (CanSendMessage && AmIEndEffector) {
		CanSendMessage = false;
		ModuleDockFace EEDockFace = DOCK_0;
		if (CurrentDockEngagedStatus[DOCK_0]) {
			EEDockFace = DOCK_1;
		}

		NumEndEffectors++;
		HasReturned[EEDockFace] = true;
		for (int i = 0; i < NumModuleConnectors; i++) {
			if ((ModuleDockFace)i != EEDockFace) {
				TreeMessage tm;
				tm.Command = "FootProbe";
				ModuleDockFace cDock = (ModuleDockFace)i;
				tm.DockStack.push(cDock);
				if (CurrentDockEngagedStatus[cDock]) {
					AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(cDock), tm));
				}
				else {
					HasReturned[cDock] = true;
				}
			}
		}
	}
	return true;
}
/**
* @brief process message
* @param aEE am i end effector?
* @param cTG connected to ground?
* @param messages messages vector
*/
void DistributedKinematicsBehavior::ProcessMessages(vector<TreeMessage> messages) {
	for (int i = 0; i<messages.size(); i++) {
		TreeMessage m = messages[i];
		if (m.Command.compare("FootProbe") == 0) {
			m.DockStack.push(m.GetReceivingDock().GetDockFace());
			if (AmIEngagedToGround) {
				ModuleDockFace GroundDockFace = DOCK_0;
				if (CurrentDockEngagedToGroundStatus[DOCK_1]) {
					GroundDockFace = DOCK_1;
				}
				ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
				FTransform T = SuperbotKinematics::computeTransformFromDock(mv, GroundDockFace)*
					SuperbotKinematics::computeTransformToDock(mv, GroundDockFace)*
					ASuperBotModule::SuperbotFix*(SModule)->GetMasterInnerMesh()->GetComponentTransform();
				ModuleDockFace d = m.DockStack.top();
				T = SuperbotKinematics::computeTransformToDock(mv, d)*T;
				TreeMessage tm;
				tm.Command = "FootReturn";
				tm.Transform = T;
				tm.DockStack = m.DockStack;
				tm.TerminalIsGroundEffector = true;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(d), tm));
			}
			else if (AmIEndEffector) {
				ModuleDockFace d = m.DockStack.top();
				TreeMessage tm;
				tm.Command = "FootReturn";
				tm.DockStack = m.DockStack;
				tm.TerminalIsEndEffector = true;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(d), tm));
			} else	{
				for (int i = 0; i < NumModuleConnectors; i++) {
					ModuleDockFace cDock = (ModuleDockFace)i;
					if (cDock != m.GetReceivingDock().GetDockFace()) {
						TreeMessage tm;
						tm.Command = m.Command;
						tm.Transform = m.Transform;
						tm.DockStack = m.DockStack;
						tm.DockStack.push(cDock);
						AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(cDock), tm));
					}
				}
			}
		}
		else if (m.Command.compare("FootReturn") == 0) {
			if (m.DockStack.size() > 2) {
				ModuleDockFace rFace = m.DockStack.top();
				m.DockStack.pop();
				ModuleDockFace d1 = m.DockStack.top();
				m.DockStack.pop();
				ModuleDockFace d2 = m.DockStack.top();
				ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
				FTransform fromTrans = SuperbotKinematics::computeTransformFromDock(mv, d1);
				FTransform toTrans = SuperbotKinematics::computeTransformToDock(mv, d2);
				m.Transform = toTrans*fromTrans*GetCorrectiveDockingTransform(rFace,d1)*m.Transform;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(d2), m));
			}
			else {
				//At receiving module
				ModuleDockFace rDock = m.GetReceivingDock().GetDockFace();
				HasReturned[rDock] = true;
				ModuleDockFace rFace = m.DockStack.top();
				m.DockStack.pop();
				ModuleDockFace d1 = m.DockStack.top();
				ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
				FTransform fromTrans = SuperbotKinematics::computeTransformFromDock(mv, d1);
				if (m.TerminalIsEndEffector) {
					NumEndEffectors++;
				}
				else {
					CurrentTransform = fromTrans*GetCorrectiveDockingTransform(rFace, d1)*m.Transform;
				}


				bool HaveFoundAll = true;
				for (int i = 0; i < NumModuleConnectors; i++) {
					if (!HasReturned[i]) HaveFoundAll = false;
				}
				if (HaveFoundAll) {
					GEngine->AddOnScreenDebugMessage(2, 15.0, FColor::Green, FString::Printf(TEXT("Found %d End Effectors"),NumEndEffectors));
				}
			}
		}
		else if (m.Command.compare("DFKUpdate") == 0) {
				m.DockStack.push(m.GetReceivingDock().GetDockFace());
				//Termination point for DFK messages
				if (AmIEngagedToGround) {
					TreeMessage tm;
					tm.Command = "DFKGroundReturn";
					tm.DockStack = m.DockStack;
					ModuleDockFace d = tm.DockStack.top();
					ModuleDockFace GroundDockFace = DOCK_0;
					if (CurrentDockEngagedToGroundStatus[DOCK_1]) {
						GroundDockFace = DOCK_1;
					}

					ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
					FTransform T = SuperbotKinematics::computeTransformToDock(mv, GroundDockFace)*
						SuperbotKinematics::computeTransformFromDock(mv, d)*
						GetCorrectiveDockingTransform(m.GetSendingDock().GetDockFace(),
							d)*m.Transform;
					tm.Transform = T;

					AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(d), tm));
				} else if (AmIEndEffector) {
					TreeMessage tm;
					tm.Command = "DFKUpdateReturn";
					tm.DockStack = m.DockStack;
					ModuleDockFace d = tm.DockStack.top();
					ModuleDockFace EEDockFace = DOCK_1;
					if (CurrentDockEngagedStatus[DOCK_1]) {
						EEDockFace = DOCK_0;
					}

					ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
					FTransform T = SuperbotKinematics::computeTransformToDock(mv, EEDockFace)*
						SuperbotKinematics::computeTransformFromDock(mv, d)*
						GetCorrectiveDockingTransform(m.GetSendingDock().GetDockFace(),
							d)*m.Transform;
					tm.Transform = T;
					AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(d), tm));
				}
				else {
					//Intermediate module
					for (int i = 0; i < NumModuleConnectors; i++) {
						ModuleDockFace cDock = (ModuleDockFace)i;
						if (cDock != m.GetReceivingDock().GetDockFace()) {
							TreeMessage tm;
							tm.Command = m.Command;
							ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
							FTransform Correction = GetCorrectiveDockingTransform(m.GetSendingDock().GetDockFace(),
								m.GetReceivingDock().GetDockFace());
							FTransform fromT = SuperbotKinematics::computeTransformFromDock(mv,m.GetReceivingDock().GetDockFace());
							FTransform toT = SuperbotKinematics::computeTransformToDock(mv, cDock);
							tm.Transform = toT*fromT*Correction*m.Transform;
							tm.DockStack = m.DockStack;
							tm.DockStack.push(cDock);
							AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(cDock), tm));
						}
					}

				}
		}
		else if (m.Command.compare("DFKUpdateReturn") == 0) {
			if (m.DockStack.size() > 2) {
				//Intermediate module
				m.DockStack.pop();
				m.DockStack.pop();
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(m.DockStack.top()), m));
			}
			else {
				//Back at starting point
				ModuleDockFace rDock = m.GetReceivingDock().GetDockFace();
				HasReturnedDFK[rDock] = true;
				EETransforms.push_back(m.Transform);
				bool HaveFoundAll = true;
				for (int i = 0; i < NumModuleConnectors; i++) {
					if (!HasReturnedDFK[i]) HaveFoundAll = false;
				}
				if (HaveFoundAll) {
					GEngine->AddOnScreenDebugMessage(3, 15.0, FColor::Green, FString::Printf(TEXT("Found  Poses of  %d End Effectors"), EETransforms.size()));
				}
			}
		}
		else if (m.Command.compare("DFKGroundReturn") == 0) {
			if (m.DockStack.size() > 2) {
				//Intermediate module
				m.DockStack.pop();
				m.DockStack.pop();
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(m.DockStack.top()), m));
			}
			else {
				//Back at starting point
				ModuleDockFace rDock = m.GetReceivingDock().GetDockFace();
				HasReturnedDFK[rDock] = true;
				bool HaveFoundAll = true;
				for (int i = 0; i < NumModuleConnectors; i++) {
					if (!HasReturnedDFK[i]) HaveFoundAll = false;
				}
				if (HaveFoundAll) {
					GEngine->AddOnScreenDebugMessage(2, 15.0, FColor::Green, FString::Printf(TEXT("Found  Poses of  %d End Effectors"), EETransforms.size()));
				}
				TransformOfGround = m.Transform;
			}
		}
	}
}
/**
* @brief get end-effector transforms
* @return end-effector transforms
*/
std::vector<FTransform> DistributedKinematicsBehavior::GetEndEffectorTransforms() {
	return EETransforms;
}
/**
* @brief get transform of ground
* @return transform of ground
*/
FTransform DistributedKinematicsBehavior::GetTransformOfGround() {
	return TransformOfGround;
}
/**
* @brief get transform
* @return transform
*/
FTransform DistributedKinematicsBehavior::GetTransform() {
	return this->CurrentTransform;
}
/**
* @brief update the current joint angles
*/
void DistributedKinematicsBehavior::UpdateCurrentAngles() {
	float motor0Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor0Angle;
	float motor1Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor1Angle;
	float motor2Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor2Angle;
	if (this->ProgramCounter == 0) {
		CurrentAngles[0] = motor0Angle;
		CurrentAngles[1] = motor1Angle;
		CurrentAngles[2] = motor2Angle;
		CAngleDiffs[0] = 0;
		CAngleDiffs[1] = 0;
		CAngleDiffs[2] = 0;
	}
	else {
		CAngleDiffs[0] += motor0Angle - CurrentAngles[0];
		CAngleDiffs[1] += motor1Angle - CurrentAngles[1];
		CAngleDiffs[2] += motor2Angle - CurrentAngles[2];
		CurrentAngles[0] = motor0Angle;
		CurrentAngles[1] = motor1Angle;
		CurrentAngles[2] = motor2Angle;
	}
}
/**
* @brief update dock engaged status
*/
void DistributedKinematicsBehavior::UpdateDockEngagedStatus() {
	bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_0];
	bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_1];
	bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_2];
	bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_3];
	bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_4];
	bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_5];

	if (this->ProgramCounter == 0) {
		CDockDiffs[DOCK_0] = 0;
		CDockDiffs[DOCK_1] = 0;
		CDockDiffs[DOCK_2] = 0;
		CDockDiffs[DOCK_3] = 0;
		CDockDiffs[DOCK_4] = 0;
		CDockDiffs[DOCK_5] = 0;
		this->CurrentDockEngagedStatus[DOCK_0] = currentDock0;
		this->CurrentDockEngagedStatus[DOCK_1] = currentDock1;
		this->CurrentDockEngagedStatus[DOCK_2] = currentDock2;
		this->CurrentDockEngagedStatus[DOCK_3] = currentDock3;
		this->CurrentDockEngagedStatus[DOCK_4] = currentDock4;
		this->CurrentDockEngagedStatus[DOCK_5] = currentDock5;
	}
	else {
		CDockDiffs[DOCK_0] = CurrentDockEngagedStatus[DOCK_0] - currentDock0;
		CDockDiffs[DOCK_1] = CurrentDockEngagedStatus[DOCK_1] - currentDock1;
		CDockDiffs[DOCK_2] = CurrentDockEngagedStatus[DOCK_2] - currentDock2;
		CDockDiffs[DOCK_3] = CurrentDockEngagedStatus[DOCK_3] - currentDock3;
		CDockDiffs[DOCK_4] = CurrentDockEngagedStatus[DOCK_4] - currentDock4;
		CDockDiffs[DOCK_5] = CurrentDockEngagedStatus[DOCK_5] - currentDock5;
		this->CurrentDockEngagedStatus[DOCK_0] = currentDock0;
		this->CurrentDockEngagedStatus[DOCK_1] = currentDock1;
		this->CurrentDockEngagedStatus[DOCK_2] = currentDock2;
		this->CurrentDockEngagedStatus[DOCK_3] = currentDock3;
		this->CurrentDockEngagedStatus[DOCK_4] = currentDock4;
		this->CurrentDockEngagedStatus[DOCK_5] = currentDock5;
	}
}
/**
* @brief update dock engaged status
*/
void DistributedKinematicsBehavior::UpdateDockEngagedToGroundStatus() {
	bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_0];
	bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_1];
	bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_2];
	bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_3];
	bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_4];
	bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_5];
	if (this->ProgramCounter == 0) {
		CDockToGroundDiffs[DOCK_0] = 0;
		CDockToGroundDiffs[DOCK_1] = 0;
		CDockToGroundDiffs[DOCK_2] = 0;
		CDockToGroundDiffs[DOCK_3] = 0;
		CDockToGroundDiffs[DOCK_4] = 0;
		CDockToGroundDiffs[DOCK_5] = 0;
		this->CurrentDockEngagedToGroundStatus[DOCK_0] = currentDock0;
		this->CurrentDockEngagedToGroundStatus[DOCK_1] = currentDock1;
		this->CurrentDockEngagedToGroundStatus[DOCK_2] = currentDock2;
		this->CurrentDockEngagedToGroundStatus[DOCK_3] = currentDock3;
		this->CurrentDockEngagedToGroundStatus[DOCK_4] = currentDock4;
		this->CurrentDockEngagedToGroundStatus[DOCK_5] = currentDock5;
	}
	else {
		CDockToGroundDiffs[DOCK_0] = CurrentDockEngagedToGroundStatus[DOCK_0] - currentDock0;
		CDockToGroundDiffs[DOCK_1] = CurrentDockEngagedToGroundStatus[DOCK_1] - currentDock1;
		CDockToGroundDiffs[DOCK_2] = CurrentDockEngagedToGroundStatus[DOCK_2] - currentDock2;
		CDockToGroundDiffs[DOCK_3] = CurrentDockEngagedToGroundStatus[DOCK_3] - currentDock3;
		CDockToGroundDiffs[DOCK_4] = CurrentDockEngagedToGroundStatus[DOCK_4] - currentDock4;
		CDockToGroundDiffs[DOCK_5] = CurrentDockEngagedToGroundStatus[DOCK_5] - currentDock5;
		this->CurrentDockEngagedToGroundStatus[DOCK_0] = currentDock0;
		this->CurrentDockEngagedToGroundStatus[DOCK_1] = currentDock1;
		this->CurrentDockEngagedToGroundStatus[DOCK_2] = currentDock2;
		this->CurrentDockEngagedToGroundStatus[DOCK_3] = currentDock3;
		this->CurrentDockEngagedToGroundStatus[DOCK_4] = currentDock4;
		this->CurrentDockEngagedToGroundStatus[DOCK_5] = currentDock5;
	}
}
/**
* @brief update dock engaged to object status
*/
void DistributedKinematicsBehavior::UpdateDockEngagedToObjectStatus() {
	bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_0];
	bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_1];
	bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_2];
	bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_3];
	bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_4];
	bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedToObjectStatus()[DOCK_5];
	if (this->ProgramCounter == 0) {
		CDockToObjectDiffs[DOCK_0] = 0;
		CDockToObjectDiffs[DOCK_1] = 0;
		CDockToObjectDiffs[DOCK_2] = 0;
		CDockToObjectDiffs[DOCK_3] = 0;
		CDockToObjectDiffs[DOCK_4] = 0;
		CDockToObjectDiffs[DOCK_5] = 0;
		this->CurrentDockEngagedToObjectStatus[DOCK_0] = currentDock0;
		this->CurrentDockEngagedToObjectStatus[DOCK_1] = currentDock1;
		this->CurrentDockEngagedToObjectStatus[DOCK_2] = currentDock2;
		this->CurrentDockEngagedToObjectStatus[DOCK_3] = currentDock3;
		this->CurrentDockEngagedToObjectStatus[DOCK_4] = currentDock4;
		this->CurrentDockEngagedToObjectStatus[DOCK_5] = currentDock5;
	}
	else {
		CDockToObjectDiffs[DOCK_0] = CurrentDockEngagedToObjectStatus[DOCK_0] - currentDock0;
		CDockToObjectDiffs[DOCK_1] = CurrentDockEngagedToObjectStatus[DOCK_1] - currentDock1;
		CDockToObjectDiffs[DOCK_2] = CurrentDockEngagedToObjectStatus[DOCK_2] - currentDock2;
		CDockToObjectDiffs[DOCK_3] = CurrentDockEngagedToObjectStatus[DOCK_3] - currentDock3;
		CDockToObjectDiffs[DOCK_4] = CurrentDockEngagedToObjectStatus[DOCK_4] - currentDock4;
		CDockToObjectDiffs[DOCK_5] = CurrentDockEngagedToObjectStatus[DOCK_5] - currentDock5;
		this->CurrentDockEngagedToObjectStatus[DOCK_0] = currentDock0;
		this->CurrentDockEngagedToObjectStatus[DOCK_1] = currentDock1;
		this->CurrentDockEngagedToObjectStatus[DOCK_2] = currentDock2;
		this->CurrentDockEngagedToObjectStatus[DOCK_3] = currentDock3;
		this->CurrentDockEngagedToObjectStatus[DOCK_4] = currentDock4;
		this->CurrentDockEngagedToObjectStatus[DOCK_5] = currentDock5;
	}
}
/**
* @brief update dock diffs
*/
void DistributedKinematicsBehavior::UpdateDockDiffs() {
	int diffTotalDocks = 0;
	for (int i = 0; i<NumModuleConnectors; i++) {
		diffTotalDocks += abs(CDockDiffs[i]);
	}
	int diffTotalDocksToGround = 0;
	for (int i = 0; i<NumModuleConnectors; i++) {
		diffTotalDocksToGround += abs(CDockToGroundDiffs[i]);
	}
	int diffTotalDocksToObject = 0;
	for (int i = 0; i<NumModuleConnectors; i++) {
		diffTotalDocksToObject += abs(CDockToObjectDiffs[i]);
	}

	if (diffTotalDocksToGround > 0) {
		cout << "Change of Base: " << this->CurrentModel.GetCurrentState().GetIDNumber() << endl;
		//GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Blue, FString::Printf(TEXT("Base Changed: %d"),
		//	this->CurrentModel.GetCurrentState().GetIDNumber()));
	}
	if (diffTotalDocksToObject > 0) {
		//GEngine->AddOnScreenDebugMessage(ObjectChangeKey, 5.0, FColor::Green, FString("Object picked up"));
	}

	if ((fabs(CAngleDiffs[0]) > 1.0 || fabs(CAngleDiffs[1]) > 1.0 || fabs(CAngleDiffs[2]) > 1.0 || abs(diffTotalDocks) > 0) ||
		abs(diffTotalDocksToGround) > 0 || abs(diffTotalDocksToObject) > 0) {
		CAngleDiffs[0] = 0.0;
		CAngleDiffs[1] = 0.0;
		CAngleDiffs[2] = 0.0;
		CDockDiffs[0] = 0;
		CDockDiffs[1] = 0;
		CDockDiffs[2] = 0;
		CDockDiffs[3] = 0;
		CDockDiffs[4] = 0;
		CDockDiffs[5] = 0;
		CDockToGroundDiffs[0] = 0;
		CDockToGroundDiffs[1] = 0;
		CDockToGroundDiffs[2] = 0;
		CDockToGroundDiffs[3] = 0;
		CDockToGroundDiffs[4] = 0;
		CDockToGroundDiffs[5] = 0;
		CDockToObjectDiffs[0] = 0;
		CDockToObjectDiffs[1] = 0;
		CDockToObjectDiffs[2] = 0;
		CDockToObjectDiffs[3] = 0;
		CDockToObjectDiffs[4] = 0;
		CDockToObjectDiffs[5] = 0;
		if (diffTotalDocksToGround > 0 || diffTotalDocksToObject > 0) {
			this->ProgramCounter = 1;
		}

	}
}
/**
* @brief update engaged to ground
*/
void DistributedKinematicsBehavior::UpdateEngagedToGround() {
	AmIEngagedToGround = (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1]);
	if (AmIEngagedToGround) {
		if (CurrentDockEngagedToGroundStatus[0]) {
			GDock = DOCK_0;
		}
		else if (CurrentDockEngagedToGroundStatus[1]) {
			GDock = DOCK_1;
		}
	}
}
/**
* @brief update whether or not I am end effector
*/
void DistributedKinematicsBehavior::UpdateEndEffectorStatus() {
	int numDocksConnected = 0;
	for (int i = 0; i<NumModuleConnectors; i++) {
		numDocksConnected += CurrentDockEngagedStatus[i];
	}
	if (numDocksConnected == 1) {
		AmIEndEffector = true;
	}
	else {
		AmIEndEffector = false;
	}
}
/**
* @brief update connected to object
*/
void DistributedKinematicsBehavior::UpdateConnectedToObject() {
	AmIConnectedToObject = (CurrentDockEngagedToObjectStatus[0] || CurrentDockEngagedToObjectStatus[1]);
}
/**
* @brief get corrective docking transform
* @param d1 dock 1
* @param d2 dock 2
* @return corrective trnasform
*/
FTransform DistributedKinematicsBehavior::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
	if (d1 == DOCK_0 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI));
	}
	else if (d1 == DOCK_0 && d2 == DOCK_2) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_2 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_3 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_0 && d2 == DOCK_3) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_2) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_2 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_3 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_3) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_0 && d2 == DOCK_4) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_4 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_4) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_4 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_0 && d2 == DOCK_5) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_5 && d2 == DOCK_0) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	else if (d1 == DOCK_1 && d2 == DOCK_5) {
		return FTransform(FQuat(FVector(0, 1, 0), -M_PI_2));
	}
	else if (d1 == DOCK_5 && d2 == DOCK_1) {
		return FTransform(FQuat(FVector(0, 1, 0), M_PI_2));
	}
	return FTransform(FVector(0, 0, 0));
}
/**
* @brief get the selected end effector
*/
ModuleDockFace DistributedKinematicsBehavior::GetEndEffectorDockFace() {
	return EEDock;
}
/**
* @brief get the selected end effector
*/
int DistributedKinematicsBehavior::GetSelectedEndEffector() {
	return SelectedEndEffector;
}
/**
* @brief get the selected end effector
*/
int DistributedKinematicsBehavior::GetGroundModule() {
	return this->GroundModule;
}
/**
* @brief get the selected end effector
*/
ModuleDockFace DistributedKinematicsBehavior::GetGroundDockFace() {
	return this->GDock;
}
/**
* @brief get am i end effector
* @return am I an end effector
*/
bool DistributedKinematicsBehavior::GetAmIEndEffector() {
	return this->AmIEndEffector;
}
/**
* @brief get am i connected to ground
* @return am I connected to ground
*/
bool DistributedKinematicsBehavior::GetAmIConnectedToGround() {
	return this->AmIEngagedToGround;
}
/**
* @brief should reinitialize program ?
* @return whether or not we need to re init program
*/
bool DistributedKinematicsBehavior::ShouldReInit() {
	return false;
}




/**
* @brief init program
*/
void DistributedKinematicsBehavior::Init() {
	this->NeighborAngles = std::vector<std::vector<float> >(NumModuleConnectors);
	for (int i = 0; i<NumModuleConnectors; i++) {
		this->NeighborAngles[i] = std::vector<float>(3);
	}
	for (int i = 0; i<NumModuleConnectors; i++) {
		for (int j = 0; j<3; j++) {
			this->NeighborAngles[i][j] = -1000;
		}
	}
	this->CurrentAngles = std::vector<float>(3);
	this->CurrentDockEngagedStatus = std::vector<bool>(NumModuleConnectors);
	this->CurrentDockEngagedToGroundStatus = std::vector<bool>(NumModuleConnectors);
	this->CurrentDockEngagedToObjectStatus = std::vector<bool>(NumModuleConnectors);
	for (int i = 0; i<NumModuleConnectors; i++) {
		this->CurrentDockEngagedStatus[i] = false;
		this->CurrentDockEngagedToGroundStatus[i] = false;
		this->CurrentDockEngagedToObjectStatus[i] = false;
	}
	this->CAngleDiffs = std::vector<float>(3);
	this->CDockDiffs = std::vector<int>(NumModuleConnectors);
	this->CDockToGroundDiffs = std::vector<int>(NumModuleConnectors);
	this->CDockToObjectDiffs = std::vector<int>(NumModuleConnectors);
	for (int i = 0; i<NumModuleConnectors; i++) {
		this->CDockDiffs[i] = 0;
		this->CDockToGroundDiffs[i] = 0;
		this->CDockToObjectDiffs[i] = 0;
	}
	this->CAngleDiffs[0] = 0.0;
	this->CAngleDiffs[1] = 0.0;
	this->CAngleDiffs[2] = 0.0;
}
/**
* @brief set am i the leader
* @param l am i the leader
*/
void DistributedKinematicsBehavior::SetAmILeader(bool l) {
	this->AmILeader = l;
}
/**
* @brief get am i the leader
* @return am i the leader
*/
bool DistributedKinematicsBehavior::GetAmILeader() {
	return AmILeader;
}
/**
* @brief get tree action for dock face
*/
ModuleAction DistributedKinematicsBehavior::GetTreeActionForDockFace(ModuleDockFace d) {
	if (d == DOCK_0) {
		return SEND_TREE_MESSAGE_FRONT_DOCK;
	}
	else if (d == DOCK_1) {
		return SEND_TREE_MESSAGE_BACK_DOCK;
	}
	else if (d == DOCK_2) {
		return SEND_TREE_MESSAGE_LEFT_DOCK;
	}
	else if (d == DOCK_3) {
		return SEND_TREE_MESSAGE_RIGHT_DOCK;
	}
	else if (d == DOCK_4) {
		return SEND_TREE_MESSAGE_UP_DOCK;
	}
	else if (d == DOCK_5) {
		return SEND_TREE_MESSAGE_DOWN_DOCK;
	}
	return SEND_TREE_MESSAGE_FRONT_DOCK;
}
/**
* @brief step function of behavior
* @param jointVals superbot sensor values
* @param desiredVals desired sensor values
* @return action values
*/
void DistributedKinematicsBehavior::Tick(ModuleModel model) {
	ClearAllActions(); /** clear all the actions from the queue*/
	this->CurrentModel = model;
	UpdateCurrentAngles(); /** update current joint angles of this module */
	UpdateDockEngagedStatus(); /** update dock engaged statuses for each dock of this module */
	UpdateDockEngagedToGroundStatus(); /** update dock engaged statuses for each dock of this module */
	UpdateDockEngagedToObjectStatus(); /** update dock engaged statuses for object */
	UpdateEngagedToGround(); /** update engaged to ground */
	UpdateEndEffectorStatus(); /** update end effector status */
	UpdateConnectedToObject(); /** update connected to object */
	std::vector<RangedMessage> rms = model.GetCurrentState().GetRangedMessages(); /** Get ranged messages */
	std::vector<Message> ms = model.GetCurrentState().GetMessages(); /** Get messages */
	std::vector<KinematicsMessage> kms = model.GetCurrentState().GetKinematicsMessages(); /** Get kinematics messages */
	std::vector<TreeMessage> tms = model.GetCurrentState().GetTreeMessages(); /** Get tree messages */
	UpdateDockDiffs(); /** Update dock differences */

	ProcessMessages(tms); /** Process any messages this module has received */

	if (AmILeader) {
		
		FindPoseToFootAndEndEffectors();


		if (CanSendDFKMessage) {
			EETransforms.clear();
			CanSendDFKMessage = false;
			if (AmIEndEffector && !AmIEngagedToGround) {
				ModuleDockFace EEDockFace = DOCK_0;
				if (CurrentDockEngagedStatus[DOCK_0]) {
					EEDockFace = DOCK_1;
				}
				ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
				EETransforms.push_back(SuperbotKinematics::computeTransformToDock(mv, EEDockFace));
				HasReturnedDFK[EEDockFace] = true;
				for (int i = 0; i < NumModuleConnectors; i++) {
					if ((ModuleDockFace)i != EEDockFace) {
						TreeMessage tm;
						tm.Command = "DFKUpdate";
						ModuleDockFace cDock = (ModuleDockFace)i;
						tm.DockStack.push(cDock);
						ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
						tm.Transform = SuperbotKinematics::computeTransformToDock(mv, cDock);
						if (CurrentDockEngagedStatus[cDock]) {
							AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(cDock), tm));
						}
						else {
							HasReturnedDFK[i] = true;
						}
					}
				}
			}
			else {
				for (int i = 0; i < NumModuleConnectors; i++) {
					TreeMessage tm;
					tm.Command = "DFKUpdate";
					ModuleDockFace cDock = (ModuleDockFace)i;
					tm.DockStack.push(cDock);
					ModuleMotorVector mv(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
					tm.Transform = SuperbotKinematics::computeTransformToDock(mv, cDock);
					if (CurrentDockEngagedStatus[cDock]) {
						AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDockFace(cDock), tm));
					}
					else {
						HasReturnedDFK[i] = true;
					}
				}
			}
		}

	}
	//AddAngleAction(std::pair<ModuleAction, float>(SET_MOTOR_0, 10.0));
	//AddAngleAction(std::pair<ModuleAction, float>(SET_MOTOR_1, -20.0));
	//AddAngleAction(std::pair<ModuleAction, float>(SET_MOTOR_2, 10.0));
	this->ProgramCounter++;

}
