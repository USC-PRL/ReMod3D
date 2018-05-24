// Fill out your copyright notice in the Description page of Project Settings.

 
#include "DistributedIK.h"
///TODO: Add object to collision detection mechanism
/**
* @brief constructor
*/
DistributedIKBehavior::DistributedIKBehavior() {
	Init();
	this->Name = "DIK";
	Seed = std::chrono::system_clock::now().time_since_epoch().count();
	Generator = std::mt19937(Seed);
}
/**
* @brief constructor
* @param W world
* @param NameOfModule name of module
*/
DistributedIKBehavior::DistributedIKBehavior(UWorld* W, std::string NameOfModule) {
	Init();
	this->Name = "DIK";
	Seed = std::chrono::system_clock::now().time_since_epoch().count();
	Generator = std::mt19937(Seed);
	this->World = W;
	this->ModuleName = NameOfModule;
	TActorIterator< AStaticMeshActor > ActorIt = TActorIterator< AStaticMeshActor >(World);
	TActorIterator< AManipulatorObjectActor > MActorIt = TActorIterator< AManipulatorObjectActor >(World);
	TActorIterator< AReferenceFrameActor > TActorIt = TActorIterator< AReferenceFrameActor >(World);
	if (TActorIt) {
		TarRef = *TActorIt;
	}
	while (ActorIt) {
		if (std::string(TCHAR_TO_UTF8(*(*ActorIt)->GetName())).compare("Floor") == 0) {
			Floor = *ActorIt;
			break;
		}
		++ActorIt;
	}
	if (MActorIt) {
		ManipOb = *MActorIt;
	}
	TActorIterator< ASuperBotModule > SuperBotIt = TActorIterator< ASuperBotModule >(World);
	while (SuperBotIt) {
		if ((*SuperBotIt)->GetName().compare(ModuleName) == 0) {
			SModule = *SuperBotIt;
			break;
		}
		++SuperBotIt;
	}
	TActorIterator<AStackableObjectActor> StackableIt = TActorIterator <AStackableObjectActor>(World);
	while (StackableIt) {
		StackableObs.push_back(*StackableIt);
		++StackableIt;
	}
	std::cout << StackableObs.size() << " Stackable objects" << std::endl;
}
/**
* @brief destructor
*/
DistributedIKBehavior::~DistributedIKBehavior() {}
///Special transforms relating module frames and world frame objects
/**
* @brief get module base to ground transform
* @return module base to ground transform
*/
FTransform DistributedIKBehavior::GetModuleBaseToGroundTransform() {
	return ModuleBaseToGroundTransform;
}








///Collision detection
/**
* @brief collision function
* @param point point to check
* @return collision (true) or not (false)
*/
bool DistributedIKBehavior::CollisionFunction(std::vector<float> point) {
	return IsInCollisionWithGroundDetailed(point);
}
/**
* @brief state valid
* @param point point to check
* @return true if state valid false otherwise
*/
bool DistributedIKBehavior::StateValid(std::vector<float> point) {
	return !CollisionFunction(point);
}
/**
* @brief detect ground collision
* @param point point to check
* @return is position in collision with ground
*/
bool DistributedIKBehavior::IsInCollisionWithGroundDetailed(std::vector<float> point) {
	vector<ModuleNode*> Mods(st.GetVertices().size());
	ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);
	FTransform ActualBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);

	vector<ModuleMotorVector> mvsFinals;
	ModuleMotorVector groundAngles;
	vector<ModuleDockFace> mvsDocks;
	groundAngles = ModuleMotorVector(point[0], point[1], point[2]);
	//FTransform LocalBaseTransform = SuperbotKinematics::computeTransformFromDock(groundAngles, GDock);
	FTransform BaseTransform = FTransform(FVector(0, 0, 0));
	for (int i = 0; i<st.GetVertices().size(); i++) {
		if (st.GetVertices()[i]->GetAmIEndEffector()) {
			mvsFinals.push_back(ModuleMotorVector(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]));
			ModuleDockFace D = (ModuleDockFace)st.GetVertices()[i]->GetDockFacePath()[st.GetVertices()[i]->GetDockFacePath().size() - 1].first;
			if (D == DOCK_0) {
				mvsDocks.push_back(DOCK_1);
			}
			else {
				mvsDocks.push_back(DOCK_0);
			}
		}
	}


	FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
	FTransform GroundTransform = Floor->GetTransform();
	GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
	FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
	BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
	FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(groundAngles, GDock);
	FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
		ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
	FTransform AGroundTransform = BaseToGround*LocalBaseTransform;


	physx::PxTransform transGround;
	physx::PxBoxGeometry groundGeometry;
	if (GDock == DOCK_0) {
		BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
	}
	else {
		BaseTransform = FTransform(FVector(-250, 0, 0))*ModuleBaseToGroundTransform*BaseTransform;
	}
	FTransform GroundFix = FTransform(FVector(-225, 0, 0));
	if (GDock == DOCK_0) {
		//FTransform GroundFix = FTransform(FVector(-225, 0, 0));
	}
	physx::PxTransform transBase = U2PTransform(GroundFix*AGroundTransform);
	groundGeometry = physx::PxBoxGeometry(200, 1000, 1000);
	PxBoxGeometry objGeom(ObjectExtents.X / 3.0, ObjectExtents.Y / 3.0, ObjectExtents.Z / 3.0);
	for (int i = 0; i<Ts.size(); i++) {
		FTransform MInnerTrans = FTransform(FVector(30.0, 0.0, 0))*Ts[i] * LocalBaseTransform;
		FTransform SInnerTrans = FTransform(FVector(-30.0, 0.0, 0))*Ts[i] * LocalBaseTransform;
		SInnerTrans = FTransform(FQuat(FVector(1, 0, 0), (M_PI / 180.0)*point[3 * i + 1]))*SInnerTrans;
		ModuleMotorVector currJoints(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]);
		FTransform MOuterTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_0)*
			Ts[i] * LocalBaseTransform;
		FTransform SOuterTrans = SuperbotKinematics::computeTransformToDock(currJoints, DOCK_1)*
			Ts[i] * LocalBaseTransform;
		FTransform MOuterLeftTrans = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterTrans;
		FTransform MOuterRightTrans = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterTrans;
		FTransform SOuterLeftTrans = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterTrans;
		FTransform SOuterRightTrans = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterTrans;
		MOuterTrans = FTransform(FVector(-10, 0, 0))*MOuterTrans;
		SOuterTrans = FTransform(FVector(10, 0, 0))*SOuterTrans;
		physx::PxTransform trans1 = U2PTransform(MInnerTrans);
		physx::PxBoxGeometry geom1(30, 37.5, 37.5);
		physx::PxTransform trans2 = U2PTransform(SInnerTrans);
		physx::PxBoxGeometry geom2(30, 37.5, 37.5);
		physx::PxTransform trans3 = U2PTransform(MOuterTrans);
		physx::PxBoxGeometry geom3(5, 37.5, 37.5);
		physx::PxTransform trans4 = U2PTransform(SOuterTrans);
		physx::PxBoxGeometry geom4(5, 37.5, 37.5);
		physx::PxTransform trans5 = U2PTransform(MOuterLeftTrans);
		physx::PxBoxGeometry geom5(50, 37.5, 9);
		physx::PxTransform trans6 = U2PTransform(MOuterRightTrans);
		physx::PxBoxGeometry geom6(50, 37.5, 9);
		physx::PxTransform trans7 = U2PTransform(SOuterLeftTrans);
		physx::PxBoxGeometry geom7(50, 37.5, 9);
		physx::PxTransform trans8 = U2PTransform(SOuterRightTrans);
		physx::PxBoxGeometry geom8(50, 37.5, 9);
		if (physx::PxGeometryQuery::overlap(geom1, trans1, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom2, trans2, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom3, trans3, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom4, trans4, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom5, trans5, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom6, trans6, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom7, trans7, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom8, trans8, groundGeometry, transBase)) {
			return true;
		}
	}
	return false;
}
/**
* @brief execute a wait for a certain number of time steps
* @param Counter number of time steps to wait
* @return true if process completed false otherwise
*/
bool DistributedIKBehavior::ExecuteWait(int Counter) {
	if (EWCounter == 0) {
		WaitCounter = Counter;
	}
	if (WaitCounter <= 0) {
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
			FString::Printf(TEXT("Done Waiting")));
		EWCounter = 0;
		return true;
	}
	else {
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Waiting")));
		WaitCounter--;
	}
	EWCounter++;
	return false;
}
/**
* @brief fitness for PASO
* @param P PSO particle
* @param st start vector
* @param tar target vector
*/
float DistributedIKBehavior::FitnessPSO(PSOParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(P.getPosition()[0], P.getPosition()[1], P.getPosition()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	vector<ModuleNode*> Mods(st.GetVertices().size());
	for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.getPosition());
	ModuleMotorVector mvsFinal = ModuleMotorVector(P.getPosition()[3 * SelectedEndEffector + 0],
		P.getPosition()[3 * SelectedEndEffector + 1],
		P.getPosition()[3 * SelectedEndEffector + 2]);


	FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();

	FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, GetEndEffectorDockFace())*
		Ts[SelectedEndEffector] * FullBaseTransform;

	FTransform FullTargetTransform = FTransform(FVector(TarVec[0], TarVec[1], TarVec[2]));
	FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
	return DiffPos.Size();
}






/**
* @brief get the transforms of modules for joint angles
* @param Mods modules
* @param JAngles joint angles
* @return transform of modules in tree
*/
vector<FTransform> DistributedIKBehavior::GetTransformsOfModulesForJointAngles(std::vector<ModuleNode*> Mods,
	std::vector<float> JAngles) {
	vector<FTransform> Transforms(Mods.size());
	vector<ModuleMotorVector> MVS(Mods.size());
	std::queue<ModuleNode*> SearchQueue;
	SearchQueue.push(Mods[0]);
	vector<bool> Discovered(Mods.size());
	for (int i = 0; i<Mods.size(); i++) {
		Discovered[i] = false;
		Transforms[i] = FTransform(FVector(0, 0, 0));
	}
	for (int i = 0; i<Mods.size(); i++) { MVS[i] = ModuleMotorVector(JAngles[3 * i + 0], JAngles[3 * i + 1], JAngles[3 * i + 2]); }

	int CurrentDock = 0;
	bool AmIEngagedToGroundFront = CurrentDockEngagedToGroundStatus[DOCK_0];
	bool AmIEngagedToGroundBack = CurrentDockEngagedToGroundStatus[DOCK_1];
	if (AmIEngagedToGroundFront) {
		Transforms[0] = SuperbotKinematics::computeTransformFromDock(MVS[0], DOCK_0);
	}
	else if (AmIEngagedToGroundBack) {
		Transforms[0] = SuperbotKinematics::computeTransformFromDock(MVS[0], DOCK_1);
	}
	for (int i = 1; i<st.GetVertices().size(); i++) {
		FTransform CurrentTransform = Transforms[0];
		std::vector<int> P = GetPathToRootFromNode(st.GetVertices()[i]);
		std::vector<std::pair<ModuleDockFace, int> > DP = st.GetVertices()[i]->GetDockFacePath();
		for (int j = 1; j<P.size(); j++) {
			ModuleDockFace d1 = DP[2 * j - 2].first;
			ModuleDockFace d2 = DP[2 * j - 1].first;
			FTransform trans1 = SuperbotKinematics::computeTransformToDock(MVS[P[j - 1]], d1);
			FTransform trans2 = SuperbotKinematics::computeTransformFromDock(MVS[P[j]], d2);
			CurrentTransform = trans2*GetCorrectiveDockingTransform(d1, d2)*trans1*CurrentTransform;
			Transforms[i] = CurrentTransform;
		}
	}
	return Transforms;
}
/**
* @brief set joints distributed
* @param JAngles joint angles
*/
void DistributedIKBehavior::SetJointAnglesDistributed(std::vector<float> JAngles) {
	TreeMessage tcm("SetJoints", st.GetVertices().size(), st.GetVertices().size());
	for (int i = 0; i<st.GetVertices().size(); i++) {
		double a0 = JAngles[3 * i + 0];
		double a1 = JAngles[3 * i + 1];
		double a2 = JAngles[3 * i + 2];
		if (i == 0) {
			AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_0, a0));
			AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_1, a1));
			AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_2, a2));
		}
		else {
			ModuleNode* cNode = st.GetVertices()[i];
			tcm.N = cNode;
			vector<float> cAngles(3);
			cAngles[0] = a0;
			cAngles[1] = a1;
			cAngles[2] = a2;
			tcm.CommandAngles = cAngles;
			if (cNode->GetDockFacePath().size() > 2) {
				tcm.Command = "SetJointsI";
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
			}
			else {
				tcm.Command = "SetJoints";
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
			}
		}
	}
}
/**
* @brief initialize kinematic tree
* @param aEE am i end effector?
* @param cTG connected to ground?
*/
void DistributedIKBehavior::InitializeKinematicTree() {
	ModuleNode *rootNode = new ModuleNode(CurrentAngles, 0, FTransform(FVector(0, 0, 0)));
	rootNode->SetDiscoveredLevel(0);
	rootNode->SetDiscoveredDock(-1);
	rootNode->SetDiscoveringNode(NULL);
	rootNode->SetAmIEndEffector(false);
	rootNode->SetConnectedToGround(this->AmIEngagedToGround);
	if (CurrentDockEngagedToGroundStatus[DOCK_0]) {
		rootNode->SetDockFaceConnectedToGround(DOCK_0);
	}
	else if (CurrentDockEngagedToGroundStatus[DOCK_1]) {
		rootNode->SetDockFaceConnectedToGround(DOCK_1);
	}
	ModuleMotorVector RAngles(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]);
	rootNode->SetTransform(SuperbotKinematics::computeTransformFromDock(RAngles, rootNode->GetDockFaceConnectedToGround()));
	ModNodes[rootNode->GetName()] = rootNode;
	st.InitializeTree(rootNode);
	st.AddNodeToBFSQueue(rootNode);
	HasBeenInitialized = true;
	this->CanSendMessage = true;
}
/**
* @brief discover kinematic structure
*/
void DistributedIKBehavior::DiscoverKinematicStructure() {
	ModuleNode *cNode = st.GetQueueFront();
	TreeMessage tm = TreeMessage("StateProbe", st.GetVertices().size(), st.GetVertices().size());
	if (CurrentModel.GetCurrentState().GetIDNumber() == 0 && ShouldPrintDiscovery) {
		cout << "Module Num: 0" << endl;
		cout << cNode->GetName() << endl;
		cout << cNode->GetCurrentDock();
		cout << endl << endl;
	}
	if (st.GetQueueSize() > 0 && cNode->GetCurrentDock() < 6) {
		tm.N = cNode;
		if (cNode->GetDockFacePath().size() > 0) {
			tm.Command = "StateProbeI";
			tm.CurrentPathElement = 0;
			tm.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)cNode->GetDockFacePath()[tm.CurrentPathElement].first, 0));
			if (cNode->GetDiscoveredLevel() < 15) {
				CanSendMessage = false;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>
					(GetTreeActionForDock(cNode->GetDockFacePath()[tm.CurrentPathElement].first), tm));
			}
			else {
				if (cNode) cNode->IncrementCurrentDock();
			}
		}
		else {
			if (CurrentDockEngagedStatus[cNode->GetCurrentDock()]) {
				this->CanSendMessage = false;
				cNode->SetDiscoveredDock(cNode->GetCurrentDock());
				tm.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)cNode->GetCurrentDock(), 0));
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>
					(GetTreeActionForDock((ModuleDockFace)cNode->GetCurrentDock()), tm));
			}
			else {
				CanSendMessage = true;
				if (cNode) cNode->IncrementCurrentDock();
			}
		}
	}

	if (st.GetQueueSize() > 0 && cNode->GetCurrentDock() >= 6) {
		this->CanSendMessage = true;
		FVector p = cNode->GetTransform().GetLocation();
		st.AddCenterOfMassTotal(p);
		st.SetCenterOfMass(st.GetCenterOfMassTotal() / st.GetVertices().size());
		st.PopBFSQueue();
	}
}
/**
* @brief process message
* @param aEE am i end effector?
* @param cTG connected to ground?
* @param messages messages vector
*/
void DistributedIKBehavior::ProcessMessages(vector<TreeMessage> messages) {
	for (int i = 0; i<messages.size(); i++) {
		TreeMessage mes = messages[i];
		if (mes.Command.compare("ReConnectObject") == 0) {
			AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_OBJECT_TO_GROUND, true));
			cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
			if (CurrentDockEngagedStatus[DOCK_1]) {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_OBJECT, false));
			}
			else {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_OBJECT, false));
			}
		}
		else if (mes.Command.compare("ReConnectObjectI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "ReConnectObjectI";
			}
			else {
				mes.Command = "ReConnectObject";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
		else if (mes.Command.compare("ConnectObjectS") == 0) {
			cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
			if (CurrentDockEngagedStatus[DOCK_1]) {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_OBJECT, true));
			}
			else {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_OBJECT, true));
			}
		}
		else if (mes.Command.compare("ConnectObjectSI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "ConnectObjectSI";
			}
			else {
				mes.Command = "ConnectObjectS";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
		else if (mes.Command.compare("DisconnectObject") == 0) {
			cout << "Will Disconnect Effector at Module: " << mes.N->GetName() << endl;
			if (CurrentDockEngagedStatus[DOCK_1]) {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_OBJECT, false));
			}
			else {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_OBJECT, false));
			}
		}
		else if (mes.Command.compare("DisconnectObjectI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "DisconnectObjectI";
			}
			else {
				mes.Command = "DisconnectObject";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
		else if (mes.Command.compare("ConnectObject") == 0) {
			AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_OBJECT_TO_GROUND, false));
			cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
			if (CurrentDockEngagedStatus[DOCK_1]) {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_OBJECT, true));
			}
			else {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_OBJECT, true));
			}
		}
		else if (mes.Command.compare("ConnectObjectI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "ConnectObjectI";
			}
			else {
				mes.Command = "ConnectObject";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
		else if (mes.Command.compare("ConnectEffector") == 0) {
			cout << "Will Connect Effector at Module: " << mes.N->GetName() << endl;
			if (CurrentDockEngagedStatus[DOCK_1]) {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_GROUND, true));
			}
			else {
				AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_GROUND, true));
			}
			HaveFoundObjectAngles = true; /**< have we found object angles with ik */
			HavePlannedObjectPath = true; /**< have we planned an object path */
			HaveExecutedObjectPath = true; /**< have we executed a path to the object */
			HaveExecutedObjectReturnPath = true; /**< have we executed a path to the object */
			HavePlannedObjectReturnPath = true; /**< have we planned a return path from object */
			HaveConnectedObjectToEffector = true; /**< have we connected object to effector */
			HaveFoundSwitchAngles = true; /**< have we found switch angles */
			HavePlannedSwitchPath = true; /**< have we planned switch path */
			HaveExecutedSwitchPath = true; /**< have we executed swtich path */
			HavePlannedSwitchReturnPath = true; /**< have we planned switch return path */
			HaveExecutedSwitchReturnPath = true; /**< have we executed switch return path*/
			HaveExecutedWait1 = true; /**< have we executed wait 1*/
			HaveExecutedWait2 = true; /**< have we executed wait 2*/
			HaveExecutedWait3 = true;/**< have we executed wait 3*/
			HaveExecutedWait4 = true;/**< have we executed wait 4*/
			HaveExecutedWait5 = true;/**< have we executed wait 5*/
			HaveSwitchedHands = true; /**< have we swtiched hands */
			HaveWaited = false; /**< have waited */
			HaveWaitedGround1 = false; /**< have waited connect to ground 1*/
			HaveWaitedGround2 = false; /**< have waited connect to ground 2*/
			HaveWaitedGround3 = false;
			HaveWaitedGround4 = false;
			HaveConnectedToGround = false; /**< have connected to ground */
			HaveFoundAnglesToGround = false; /**< have found angles to ground */
			HavePlannedIKToGround = false; /**< have we planned ik to ground */
			HaveExecutedIKToGround = false; /**< have executed ik to ground */
			HavePlannedIKToGroundReturn = false; /**< have planned ik to ground return */
			HaveExecutedIKToGroundReturn = false; /**< have executed ik to ground return */
		}
		else if (mes.Command.compare("ConnectEffectorI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "ConnectEffectorI";
			}
			else {
				mes.Command = "ConnectEffector";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
		else if (mes.Command.compare("StateProbe") == 0) {
			mes.MV.push_back(ModuleMotorVector(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]));
			mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(), 0));
			mes.CurrentPathElement = mes.DockFacePath.size() - 1;
			mes.DockConnectedStatuses = CurrentDockEngagedStatus;
			mes.Command = "ReturnState";
			mes.AmIEndEffector = this->AmIEndEffector;
			mes.ConnectedToGround = this->AmIEngagedToGround;
			mes.ConnectedToObject = this->AmIConnectedToObject;
			if (mes.N->GetDockFacePath().size() > 0) { mes.Command = "ReturnStateI"; }
			AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()), mes));
		}
		else if (mes.Command.compare("StateProbeI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size()) {
				mes.Command = "StateProbeI";
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
			}
			else {
				mes.Command = "StateProbe";
				d = (ModuleDockFace)mes.N->GetCurrentDock();
			}

			if (CurrentDockEngagedStatus[d] && d != mes.GetReceivingDock().GetDockFace()) {
				mes.MV.push_back(ModuleMotorVector(CurrentAngles[0], CurrentAngles[1], CurrentAngles[2]));
				mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(), 0));
				mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)d, 0));
				if (mes.Command.compare("StateProbe") == 0) {
					mes.N->SetDiscoveredDock(mes.N->GetCurrentDock());
				}
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
			else {
				mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(), 0));
				mes.CurrentPathElement = mes.DockFacePath.size() - 1;
				if (mes.CurrentPathElement > 1) {
					mes.Command = "ReturnStateFI";
				}
				else {
					mes.Command = "ReturnStateF";
				}
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()), mes));
			}
		}
		else if (mes.Command.compare("ReturnStateI") == 0) {
			mes.CurrentPathElement -= 2;
			if (mes.CurrentPathElement <= 1) {
				mes.Command = "ReturnState";
			}
			else {
				mes.Command = "ReturnStateI";
			}
			AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(mes.N->GetDockFacePath()[mes.CurrentPathElement].first), mes));
		}
		else if (mes.Command.compare("ReturnState") == 0) {
			this->CanSendMessage = true;
			std::vector<float> angles = std::vector<float>(3);
			angles[0] = CurrentAngles[0]; angles[1] = CurrentAngles[1]; angles[2] = CurrentAngles[2];
			FTransform CurrentTransform = FTransform(FVector(0, 0, 0));
			ModuleMotorVector mv = ModuleMotorVector(angles[0], angles[1], angles[2]);
			int dockCounter = 0;
			CurrentTransform = st.GetVertices()[0]->GetTransform();
			for (int j = 0; j<mes.MV.size(); j++) {
				ModuleDockFace d1 = mes.DockFacePath[dockCounter++].first;
				ModuleDockFace d2 = mes.DockFacePath[dockCounter++].first;
				FTransform trans1 = SuperbotKinematics::computeTransformToDock(mv, d1);
				angles[0] = mes.MV[j].Motor0Angle; angles[1] = mes.MV[j].Motor1Angle; angles[2] = mes.MV[j].Motor2Angle;
				mv = ModuleMotorVector(angles[0], angles[1], angles[2]);
				FTransform trans2 = SuperbotKinematics::computeTransformFromDock(mv, d2);
				CurrentTransform = trans2*GetCorrectiveDockingTransform(d1, d2)*trans1*CurrentTransform;
				if (!CurrentTransform.IsValid()) {
					cout << "Problem" << endl;
				}
			}
			mes.N->IncrementCurrentDock();
			ModuleNode *n = new ModuleNode(angles, mes.GetNeighborNumID(), CurrentTransform);
			n->SetDiscoveredLevel(mes.DockFacePath.size() / 2);
			n->SetDockFacePath(mes.DockFacePath);
			n->SetDiscoveredDock(mes.N->GetDiscoveredDock());
			n->SetDiscoveringNode(mes.N);
			n->SetDockEngagedStatuses(mes.DockConnectedStatuses);
			n->SetJointAngles(angles);
			n->SetAmIEndEffector(mes.AmIEndEffector);
			n->SetConnectedToGround(mes.ConnectedToGround);
			n->SetAmIConnectedToObject(mes.ConnectedToObject);
			st.AddEdge(mes.N->GetName(), n->GetName(), mes.DockFacePath[mes.DockFacePath.size() - 2].first, mes.DockFacePath[mes.DockFacePath.size() - 1].first);
			st.AddNodeToBFSQueue(n);
			st.AddVertex(n);
			ModNodes[mes.GetNeighborNumID()] = n;
		}
		else if (mes.Command.compare("ReturnStateF") == 0) {
			this->CanSendMessage = true;
			mes.N->IncrementCurrentDock();
		}
		else if (mes.Command.compare("ReturnStateFI") == 0) {
			mes.CurrentPathElement -= 2;
			ModuleDockFace d = (ModuleDockFace)mes.DockFacePath[mes.CurrentPathElement].first;
			if (mes.CurrentPathElement <= 1) {
				mes.Command = "ReturnStateF";
			}
			else {
				mes.Command = "ReturnStateFI";
			}
			AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
		}
		else if (mes.Command.compare("Reset") == 0) {
			this->ShouldSetTreeDirty = true;
			//cout<<"Received Reset"<<endl;
			TreeMessage tm = TreeMessage("Reset", st.GetVertices().size(), 0);
			for (int j = 0; j<6; j++) {
				if (CurrentDockEngagedStatus[j] && j != mes.GetReceivingDock().GetDockFace()) {
					AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)j), tm));
				}
			}
		}
		else if (mes.Command.compare("SetJoints") == 0) {
			AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_0, mes.CommandAngles[0]));
			AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_1, mes.CommandAngles[1]));
			AddAngleAction(std::pair<ModuleAction, float>(ModuleAction::SET_MOTOR_2, mes.CommandAngles[2]));
		}
		else if (mes.Command.compare("SetJointsI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "SetJointsI";
			}
			else {
				mes.Command = "SetJoints";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
	}
}
/**
* @brief update the current joint angles
*/
void DistributedIKBehavior::UpdateCurrentAngles() {
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
void DistributedIKBehavior::UpdateDockEngagedStatus() {
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
void DistributedIKBehavior::UpdateDockEngagedToGroundStatus() {
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
void DistributedIKBehavior::UpdateDockEngagedToObjectStatus() {
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
void DistributedIKBehavior::UpdateDockDiffs() {
	int diffTotalDocks = 0;
	for (int i = 0; i<6; i++) {
		diffTotalDocks += abs(CDockDiffs[i]);
	}
	int diffTotalDocksToGround = 0;
	for (int i = 0; i<6; i++) {
		diffTotalDocksToGround += abs(CDockToGroundDiffs[i]);
	}
	int diffTotalDocksToObject = 0;
	for (int i = 0; i<6; i++) {
		diffTotalDocksToObject += abs(CDockToObjectDiffs[i]);
	}

	if (diffTotalDocksToGround > 0) {
		cout << "Change of Base: " << this->CurrentModel.GetCurrentState().GetIDNumber() << endl;
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Blue, FString::Printf(TEXT("Base Changed: %d"),
			this->CurrentModel.GetCurrentState().GetIDNumber()));
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
		TreeMessage tm = TreeMessage("Reset", st.GetVertices().size(), 0);
		for (int j = 0; j<6; j++) {
			if (CurrentDockEngagedStatus[j]) {
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)j), tm));
			}
		}
		this->ShouldSetTreeDirty = true;

	}
}
/**
* @brief update engaged to ground
*/
void DistributedIKBehavior::UpdateEngagedToGround() {
	AmIEngagedToGround = (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1]);
	if (AmIEngagedToGround) {
		if (CurrentDockEngagedToGroundStatus[0]) {
			GDock = DOCK_0;
		}
		else if (CurrentDockEngagedToGroundStatus[1]) {
			GDock = DOCK_1;
		}

		for (int i = 0; i < st.GetVertices().size(); i++) {
			ModuleNode *smn = st.GetVertices()[i];
			if (smn->GetConnectedToGround()) {
				GroundModule = smn->GetName();
			}
		}
		/*if (SModule) {
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
		ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		CurrentX = FullBaseTransform.GetLocation().X;
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
		}*/
	}
}
/**
* @brief update whether or not I am end effector
*/
void DistributedIKBehavior::UpdateEndEffectorStatus() {
	int numDocksConnected = 0;
	for (int i = 0; i<6; i++) {
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
void DistributedIKBehavior::UpdateConnectedToObject() {
	AmIConnectedToObject = (CurrentDockEngagedToObjectStatus[0] || CurrentDockEngagedToObjectStatus[1]);
}
/**
* @brief get kinematics action for dock face
* @param d dock face
* @return Superbot action
*/
ModuleAction DistributedIKBehavior::GetKinematicsActionForDock(ModuleDockFace d) {
	if (d == DOCK_0) {
		return SEND_KINEMATICS_MESSAGE_FRONT_DOCK;
	}
	else if (d == DOCK_1) {
		return SEND_KINEMATICS_MESSAGE_BACK_DOCK;
	}
	else if (d == DOCK_2) {
		return SEND_KINEMATICS_MESSAGE_LEFT_DOCK;
	}
	else if (d == DOCK_3) {
		return SEND_KINEMATICS_MESSAGE_RIGHT_DOCK;
	}
	else if (d == DOCK_4) {
		return SEND_KINEMATICS_MESSAGE_UP_DOCK;
	}
	else if (d == DOCK_5) {
		return SEND_KINEMATICS_MESSAGE_DOWN_DOCK;
	}
	return SEND_KINEMATICS_MESSAGE_FRONT_DOCK;
}
/**
* @brief get kinematics action for dock face
* @param d dock face
* @return Superbot action
*/
ModuleAction DistributedIKBehavior::GetTreeActionForDock(ModuleDockFace d) {
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
* @brief get path to root from node
* @param n superbot module node
* @return path
*/
std::vector<int> DistributedIKBehavior::GetPathToRootFromNode(ModuleNode* n) {
	std::vector<int> path;
	ModuleNode* CNode = n;
	path.push_back(n->GetName());
	while (CNode->GetDiscoveringNode()) {
		CNode = CNode->GetDiscoveringNode();
		path.push_back(CNode->GetName());
	}
	std::reverse(path.begin(), path.end());
	return path;
}
/**
* @brief get corrective docking transform
* @param d1 dock 1
* @param d2 dock 2
* @return corrective trnasform
*/
FTransform DistributedIKBehavior::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
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
* @brief get superbot module tree
*/
ModuleTree DistributedIKBehavior::GetSuperBotTree() {
	return this->st;
}
/**
* @brief get the selected end effector
*/
ModuleDockFace DistributedIKBehavior::GetEndEffectorDockFace() {
	return EEDock;
}
/**
* @brief get the selected end effector
*/
int DistributedIKBehavior::GetSelectedEndEffector() {
	return SelectedEndEffector;
}
/**
* @brief get the selected end effector
*/
int DistributedIKBehavior::GetGroundModule() {
	return this->GroundModule;
}
/**
* @brief get the selected end effector
*/
ModuleDockFace DistributedIKBehavior::GetGroundDockFace() {
	return this->GDock;
}
/**
* @brief get am i end effector
* @return am I an end effector
*/
bool DistributedIKBehavior::GetAmIEndEffector() {
	return this->AmIEndEffector;
}
/**
* @brief get am i connected to ground
* @return am I connected to ground
*/
bool DistributedIKBehavior::GetAmIConnectedToGround() {
	return this->AmIEngagedToGround;
}
/**
* @brief should reinitialize program ?
* @return whether or not we need to re init program
*/
bool DistributedIKBehavior::ShouldReInit() {
	return false;
}




/**
* @brief init program
*/
void DistributedIKBehavior::Init() {
	ObjectExtents = FVector(50.0, 50.0, 50.0);
	this->NeighborAngles = std::vector<std::vector<float> >(6);
	for (int i = 0; i<6; i++) {
		this->NeighborAngles[i] = std::vector<float>(3);
	}
	for (int i = 0; i<6; i++) {
		for (int j = 0; j<3; j++) {
			this->NeighborAngles[i][j] = -1000;
		}
	}
	HasReturned[0] = true;
	HasReturned[1] = true;
	HasReturned[2] = true;
	HasReturned[3] = true;
	HasReturned[4] = true;
	HasReturned[5] = true;

	this->CurrentAngles = std::vector<float>(3);
	this->CurrentDockEngagedStatus = std::vector<bool>(6);
	this->CurrentDockEngagedToGroundStatus = std::vector<bool>(6);
	this->CurrentDockEngagedToObjectStatus = std::vector<bool>(6);
	for (int i = 0; i<6; i++) {
		this->CurrentDockEngagedStatus[i] = false;
		this->CurrentDockEngagedToGroundStatus[i] = false;
		this->CurrentDockEngagedToObjectStatus[i] = false;
	}
	this->CAngleDiffs = std::vector<float>(3);
	this->CDockDiffs = std::vector<int>(6);
	this->CDockToGroundDiffs = std::vector<int>(6);
	this->CDockToObjectDiffs = std::vector<int>(6);
	for (int i = 0; i<6; i++) {
		this->CDockDiffs[i] = 0;
		this->CDockToGroundDiffs[i] = 0;
		this->CDockToObjectDiffs[i] = 0;
	}
	this->CAngleDiffs[0] = 0.0;
	this->CAngleDiffs[1] = 0.0;
	this->CAngleDiffs[2] = 0.0;
}


/**
* @brief step function of behavior
* @param jointVals superbot sensor values
* @param desiredVals desired sensor values
* @return action values
*/
void DistributedIKBehavior::Tick(ModuleModel model) {
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

					   //Initiate kinematic tree if we are attached  to the ground and have not initiatlized it already
	if (!HasBeenInitialized && (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1])) {
		InitializeKinematicTree();
	}

	ProcessMessages(tms); /** Process any messages this module has received */

	if (CanSendMessage && (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1])) {
		if (st.GetQueueSize() > 0) {
			//Discover the kinematic structure of the tree
			DiscoverKinematicStructure();
		}
		else if (ShouldSetTreeDirty) {
			//Tree must be rebuilt and re-initialized
			st.ResetCenterOfMassTotal();
			this->ShouldSetTreeDirty = false;
			this->CanSendMessage = true;
			for (int i = 0; i < st.GetVertices().size(); i++) {
				ModuleNode *smn = st.GetVertices()[i];
				if (smn) delete smn;
			}
			InitializeKinematicTree();
		}
		else {
			if (true) {
				TarVec = std::vector<float>{ TarRef->GetTransform().GetLocation().X, TarRef->GetTransform().GetLocation().Y, TarRef->GetTransform().GetLocation().Z };

				PSOParticleSwarm PS = PSOParticleSwarm(20, 20, 3 * st.GetVertices().size());
				std::vector<std::pair<float, float> > posInit(3 * st.GetVertices().size());
				std::vector<std::pair<float, float> > posRun(3 * st.GetVertices().size());
				std::vector<std::pair<float, float> > velInit(3 * st.GetVertices().size());
				std::vector<std::pair<float, float> > velRun(3 * st.GetVertices().size());
				std::vector<float> startVec(3 * st.GetVertices().size());
				int EE = -1;
				for (int i = 0; i < st.GetVertices().size(); i++) {
					if (st.GetVertices()[i]->GetAmIEndEffector()) EE = i;
					startVec[3 * i + 0] = st.GetVertices()[i]->GetJointAngles()[0];
					startVec[3 * i + 1] = st.GetVertices()[i]->GetJointAngles()[1];
					startVec[3 * i + 2] = st.GetVertices()[i]->GetJointAngles()[2];
					if (i == CurrentModule) {
						posInit[3 * i + 0] = std::pair<float, float>(fmax(startVec[3*i + 0] -10 -10*i, -90), fmin(startVec[3*i + 0] + 10 + 10*i, 90));
						posInit[3 * i + 1] = std::pair<float, float>(fmax(startVec[3 * i + 1] - 10 -10*i, -90), fmin(startVec[3 * i + 1] + 10 + 10*i, 90));
						posInit[3 * i + 2] = std::pair<float, float>(fmax(startVec[3 * i + 2] - 10 - 10*i, -90), fmin(startVec[3 * i + 2] + 10 + 10*i, 90));
						posRun[3 * i + 0] = std::pair<float, float>(fmax(startVec[3 * i + 0] - 10 - 10*i, -90), fmin(startVec[3 * i + 0] + 10 + 10*i, 90));
						posRun[3 * i + 1] = std::pair<float, float>(fmax(startVec[3 * i + 1] - 10 - 10*i, -90), fmin(startVec[3 * i + 1] + 10 + 10*i, 90));
						posRun[3 * i + 2] = std::pair<float, float>(fmax(startVec[3 * i + 2] - 10 -10*i, -90), fmin(startVec[3 * i + 2] + 10 + 10 * i, 90));
						velInit[3 * i + 0] = posInit[3 * i + 0];
						velInit[3 * i + 1] = posInit[3 * i + 1];
						velInit[3 * i + 2] = posInit[3 * i + 2];
						velRun[3 * i + 0] = velInit[3 * i + 0];
						velRun[3 * i + 1] = velInit[3 * i + 1];
						velRun[3 * i + 2] = velInit[3* i + 2];
					}
					else {
						posInit[3 * i + 0] = std::pair<float, float>(startVec[3 * i + 0] - 0.001, startVec[3 * i + 0] + 0.001);
						posInit[3 * i + 1] = std::pair<float, float>(startVec[3 * i + 1] - 0.001, startVec[3 * i + 1] + 0.001);
						posInit[3 * i + 2] = std::pair<float, float>(startVec[3 * i + 2] - 0.001, startVec[3 * i + 2] + 0.001);
						posRun[3 * i + 0] = std::pair<float, float>(startVec[3 * i + 0] - 0.001, startVec[3 * i + 0] + 0.001);
						posRun[3 * i + 1] = std::pair<float, float>(startVec[3 * i + 1] - 0.001, startVec[3 * i + 1] + 0.001);
						posRun[3 * i + 2] = std::pair<float, float>(startVec[3 * i + 2] - 0.001, startVec[3 * i + 2] + 0.001);
						velInit[3 * i + 0] = std::pair<float, float>(startVec[3 * i + 0] - 0.001, startVec[3 * i + 0] + 0.001);
						velInit[3 * i + 1] = std::pair<float, float>(startVec[3 * i + 1] - 0.001, startVec[3 * i + 1] + 0.001);
						velInit[3 * i + 2] = std::pair<float, float>(startVec[3 * i + 2] - 0.001, startVec[3 * i + 2] + 0.001);
						velRun[3 * i + 0] = std::pair<float, float>(startVec[3 * i + 0] - 0.001, startVec[3 * i + 0] + 0.001);
						velRun[3 * i + 1] = std::pair<float, float>(startVec[3 * i + 1] - 0.001, startVec[3 * i + 1] + 0.001);
						velRun[3 * i + 2] = std::pair<float, float>(startVec[3 * i + 2] - 0.001, startVec[3 * i + 2] + 0.001);
					}
				}
				ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[EE]->GetDockFacePath()[st.GetVertices()[EE]->GetDockFacePath().size() - 1].first;
				if (LastDockFace == DOCK_0) {
					EEDock = DOCK_1;
				}
				else {
					EEDock = DOCK_0;
				}
				SelectedEndEffector = EE;
				PS.setCollisionDetector(std::bind(&DistributedIKBehavior::CollisionFunction, this, std::placeholders::_1));
				PS.initializeSwarm(posInit, velInit, posRun, velRun, 3.0, MODE_CONSTRICTION, std::bind(&DistributedIKBehavior::FitnessPSO, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
					startVec, TarVec);
				PSOParticle P = PS.optimize();
				for (int i = 0; i < st.GetVertices().size(); i++) {
					if (i == CurrentModule) {
						startVec[3 * i + 0] = PS.getGlobalBestParticle().getPosition()[3*i + 0];
						startVec[3 * i + 1] = PS.getGlobalBestParticle().getPosition()[3*i + 1];
						startVec[3 * i + 2] = PS.getGlobalBestParticle().getPosition()[3*i + 2];
					} else {
						startVec[3 * i + 0] = st.GetVertices()[i]->GetJointAngles()[0];
						startVec[3 * i + 1] = st.GetVertices()[i]->GetJointAngles()[1];
						startVec[3 * i + 2] = st.GetVertices()[i]->GetJointAngles()[2];
					}
				}
				SetJointAnglesDistributed(startVec);
				GEngine->AddOnScreenDebugMessage(Key1, 5., FColor::Green, FString::Printf(TEXT("Move Module: %d"), CurrentModule));
				CurrentModule++;
				if (CurrentModule >= st.GetVertices().size()) {
					CurrentModule = 1;
				}
			}
		}
		this->ProgramCounter++;
	}
}
