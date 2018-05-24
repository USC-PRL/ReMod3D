// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ReconfDemoQ2.h"
///TODO: Add object to collision detection mechanism
/**
* @brief constructor
*/
ReconfDemoQ2Behavior::ReconfDemoQ2Behavior() {
	Init();
	this->Name = "ReconfQ2";
	Seed = std::chrono::system_clock::now().time_since_epoch().count();
	Generator = std::mt19937(Seed);
}
/**
* @brief constructor
* @param W world
* @param NameOfModule name of module
*/
ReconfDemoQ2Behavior::ReconfDemoQ2Behavior(UWorld* W, std::string NameOfModule) {
	Init();
	this->Name = "ReconfQ2";
	Seed = std::chrono::system_clock::now().time_since_epoch().count();
	Generator = std::mt19937(Seed);
	this->World = W;
	this->ModuleName = NameOfModule;
	TActorIterator< AStaticMeshActor > ActorIt = TActorIterator< AStaticMeshActor >(World);
	TActorIterator< AManipulatorObjectActor > MActorIt = TActorIterator< AManipulatorObjectActor >(World);
	while (ActorIt) {
		if (std::string(TCHAR_TO_UTF8(*(*ActorIt)->GetName())).compare("Floor") == 0) {
			Floor = *ActorIt;
			break;
		}
		++ActorIt;
	}
	ManipOb = *MActorIt;
	TActorIterator< ASuperBotModule > SuperBotIt = TActorIterator< ASuperBotModule >(World);
	while (SuperBotIt) {
		if ((*SuperBotIt)->GetName().compare(ModuleName) == 0) {
			SModule = *SuperBotIt;
			break;
		}
		++SuperBotIt;
	}
}
/**
* @brief destructor
*/
ReconfDemoQ2Behavior::~ReconfDemoQ2Behavior() {}
///Special transforms relating module frames and world frame objects
/**
* @brief get module base to ground transform
* @return module base to ground transform
*/
FTransform ReconfDemoQ2Behavior::GetModuleBaseToGroundTransform() {
	return ModuleBaseToGroundTransform;
}
/**
* @brief get module base to object transform
* @return module base to object transform
*/
FTransform ReconfDemoQ2Behavior::GetModuleBaseToObjectTransform() {
	return ModuleBaseToObjectTransform;
}
/**
* @brief Get master inner transform of module associated with this program
* @return master inner transform
*/
FTransform ReconfDemoQ2Behavior::GetMasterInnerTransformForBaseModule() {
	TActorIterator< ASuperBotModule > SuperbotIt = TActorIterator< ASuperBotModule >(World);
	while (SuperbotIt) {
		string str = (*SuperbotIt)->GetName();
		if (str.compare(this->ModuleName) == 0) {
			return (*SuperbotIt)->GetMasterInnerMesh()->GetComponentTransform();
		}
	}
	return FTransform(FVector(-1, -1, -1));
}





///Dynamic connections to objects
/**
* @brief set joints distributed
* @param JAngles joint angles
*/
void ReconfDemoQ2Behavior::ConnectNewEffector() {
	GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Blue, FString("Switching Ground Module"));
	if (GDock == DOCK_1) {
		AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_GROUND, false));
	}
	else if (GDock == DOCK_0) {
		AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_GROUND, false));
	}
	cout << "Selected End Effector: " << SelectedEndEffector << endl;
	TreeMessage tcm("ConnectEffector", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode = st.GetVertices()[SelectedEndEffector];
	tcm.N = cNode;
	if (cNode->GetDockFacePath().size() > 2) {
		tcm.Command = "ConnectEffectorI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
	}
	else {
		tcm.Command = "ConnectEffector";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
	}
}
/**
* @brief connect object
*/
void ReconfDemoQ2Behavior::ConnectObject() {
	cout << "Selected End Effector: " << SelectedEndEffector << endl;
	GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Blue, FString("Connecting"));
	TreeMessage tcm("ConnectObject", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode = st.GetVertices()[SelectedEndEffector];
	tcm.N = cNode;
	if (cNode->GetDockFacePath().size() > 2) {
		tcm.Command = "ConnectObjectI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
	}
	else {
		tcm.Command = "ConnectObject";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
	}
}
/**
* @brief reconnect object to ground
*/
void ReconfDemoQ2Behavior::ReconnectObjectToGround() {
	cout << "Selected End Effector: " << SelectedEndEffector << endl;
	GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Blue, FString("ReConnecting to ground"));
	TreeMessage tcm("ReConnectObject", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode = st.GetVertices()[SelectedEndEffector];
	tcm.N = cNode;
	if (cNode->GetDockFacePath().size() > 2) {
		tcm.Command = "ReConnectObjectI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
	}
	else {
		tcm.Command = "ReConnectObject";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first), tcm));
	}
}
/**
* @brief perform the actual connection and disconnection of docks to switch hands
*/
void ReconfDemoQ2Behavior::SwitchObject() {
	GEngine->AddOnScreenDebugMessage(ObjectChangeKey, 5.f, FColor::Blue, FString("Switching Hands"));
	vector<ModuleNode*> Mods(st.GetVertices().size());
	vector<int> EndEffectors;
	for (int i = 0; i<st.GetVertices().size(); i++) {
		Mods[i] = st.GetVertices()[i];
		if (Mods[i]->GetAmIEndEffector() || Mods[i]->GetAmIConnectedToObject()) {
			EndEffectors.push_back(i);
		}
	}

	int EndEffector1 = EndEffectors[0];
	int EndEffector2 = EndEffectors[1];
	ModuleDockFace LastDockFace1 = (ModuleDockFace)Mods[EndEffector1]->GetDockFacePath()[Mods[EndEffector1]->GetDockFacePath().size() - 1].first;
	ModuleDockFace LastDockFace2 = (ModuleDockFace)Mods[EndEffector2]->GetDockFacePath()[Mods[EndEffector2]->GetDockFacePath().size() - 1].first;
	ModuleDockFace EEDock1;
	ModuleDockFace EEDock2;
	if (LastDockFace1 == DOCK_0) {
		EEDock1 = DOCK_1;
	}
	else {
		EEDock1 = DOCK_0;
	}
	if (LastDockFace2 == DOCK_0) {
		EEDock2 = DOCK_1;
	}
	else {
		EEDock2 = DOCK_0;
	}
	int EEWithOb = -1;
	int EENoOb = -1;
	if (st.GetVertices()[EndEffector1]->GetAmIConnectedToObject()) {
		EEWithOb = EndEffector1;
		EENoOb = EndEffector2;
	}
	else {
		EEWithOb = EndEffector2;
		EENoOb = EndEffector1;
	}
	TreeMessage tcm1("DisconnectObject", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode1 = st.GetVertices()[EEWithOb];
	tcm1.N = cNode1;
	TreeMessage tcm2("ConnectObjectS", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode2 = st.GetVertices()[EENoOb];
	tcm2.N = cNode2;
	if (cNode1->GetDockFacePath().size() > 2) {
		tcm1.Command = "DisconnectObjectI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode1->GetDockFacePath()[0].first), tcm1));
	}
	else {
		tcm1.Command = "DisconnectObject";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode1->GetDockFacePath()[0].first), tcm1));
	}

	if (cNode2->GetDockFacePath().size() > 2) {
		tcm2.Command = "ConnectObjectSI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode2->GetDockFacePath()[0].first), tcm2));
	}
	else {
		tcm2.Command = "ConnectObjectS";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode2->GetDockFacePath()[0].first), tcm2));
	}
}
/**
* @brief reconfigure manipulator snake
*/
void ReconfDemoQ2Behavior::ReconfigureManipulatorSnakeToTree() {
	GEngine->AddOnScreenDebugMessage(ObjectChangeKey, 5.f, FColor::Blue, FString("Reconfiguring Manipulator"));
	vector<ModuleNode*> Mods(st.GetVertices().size());
	for (int i = 0; i < st.GetVertices().size(); i++) {
		Mods[i] = st.GetVertices()[i];
	}
	int EndEffector1 = SelectedEndEffector;
	int EndEffector2 = 2;
	ModuleDockFace LastDockFace1 = (ModuleDockFace)Mods[EndEffector1]->GetDockFacePath()[Mods[EndEffector1]->GetDockFacePath().size() - 1].first;
	ModuleDockFace EEDock1;
	ModuleDockFace EEDock2;
	if (LastDockFace1 == DOCK_0) {
		EEDock1 = DOCK_1;
	}
	else {
		EEDock1 = DOCK_0;
	}
	EEDock2 = DOCK_3;
	TreeMessage tcm1("ConnectToReconfigure", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode1 = st.GetVertices()[EndEffector1];
	tcm1.N = cNode1;
	tcm1.SM1 = cNode1->GetModuleReference();
	tcm1.D1 = EEDock1;
	tcm1.D2 = EEDock2;
	TreeMessage tcm2("DisconnectToReconfigure", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode2 = st.GetVertices()[4];
	tcm2.N = cNode2;
	tcm1.SM2 = st.GetVertices()[2]->GetModuleReference();
	tcm2.SM1 = st.GetVertices()[4]->GetModuleReference();
	tcm2.SM2 = st.GetVertices()[3]->GetModuleReference();
	tcm2.D1 = DOCK_0;
	tcm2.D2 = DOCK_1;

	if (cNode2->GetDockFacePath().size() > 2) {
		tcm2.Command = "DisconnectToReconfigureI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode2->GetDockFacePath()[0].first), tcm2));
	}
	else {
		tcm2.Command = "DisconnectToReconfigure";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode2->GetDockFacePath()[0].first), tcm2));
	}

	if (cNode1->GetDockFacePath().size() > 2) {
		tcm1.Command = "ConnectToReconfigureI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode1->GetDockFacePath()[0].first), tcm1));
	}
	else {
		tcm1.Command = "ConnectToReconfigure";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode1->GetDockFacePath()[0].first), tcm1));
	}

}
/**
* @brief reconfigure manipulator tree
*/
void ReconfDemoQ2Behavior::ReconfigureManipulatorTreeToSnake() {
	GEngine->AddOnScreenDebugMessage(ObjectChangeKey, 5.f, FColor::Blue, FString("Reconfiguring Manipulator"));
	vector<ModuleNode*> Mods(st.GetVertices().size());
	vector<int> EndEffectors;
	for (int i = 0; i<st.GetVertices().size(); i++) {
		Mods[i] = st.GetVertices()[i];
		if (Mods[i]->GetAmIEndEffector()) {
			EndEffectors.push_back(i);
		}
	}

	int EndEffector1 = EndEffectors[0];
	int EndEffector2 = EndEffectors[1];
	ModuleDockFace LastDockFace1 = (ModuleDockFace)Mods[EndEffector1]->GetDockFacePath()[Mods[EndEffector1]->GetDockFacePath().size() - 1].first;
	ModuleDockFace LastDockFace2 = (ModuleDockFace)Mods[EndEffector2]->GetDockFacePath()[Mods[EndEffector2]->GetDockFacePath().size() - 1].first;
	ModuleDockFace EEDock1;
	ModuleDockFace EEDock2;
	if (LastDockFace1 == DOCK_0) {
		EEDock1 = DOCK_1;
	}
	else {
		EEDock1 = DOCK_0;
	}
	if (LastDockFace2 == DOCK_0) {
		EEDock2 = DOCK_1;
	}
	else {
		EEDock2 = DOCK_0;
	}
	TreeMessage tcm1("ConnectToReconfigure", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode1 = st.GetVertices()[EndEffector1];
	tcm1.N = cNode1;
	tcm1.SM1 = cNode1->GetModuleReference();
	tcm1.D1 = EEDock1;
	tcm1.D2 = EEDock2;
	TreeMessage tcm2("DisconnectToReconfigure", st.GetVertices().size(), st.GetVertices().size());
	ModuleNode* cNode2 = st.GetVertices()[EndEffector2];
	tcm2.N = cNode2;
	tcm1.SM2 = cNode2->GetModuleReference();
	tcm2.SM1 = cNode1->GetModuleReference();
	tcm2.SM2 = cNode2->GetModuleReference();
	tcm2.D1 = EEDock1;
	tcm2.D2 = EEDock2;
	std::vector<int> P1 = GetPathToRootFromNode(st.GetVertices()[EndEffector1]);
	std::vector<int> P2 = GetPathToRootFromNode(st.GetVertices()[EndEffector2]);
	std::vector<std::pair<ModuleDockFace, int> > DP1 = st.GetVertices()[EndEffector1]->GetDockFacePath();
	std::vector<std::pair<ModuleDockFace, int> > DP2 = st.GetVertices()[EndEffector2]->GetDockFacePath();

	for (int i = 1; i < P1.size(); i++) {
		if (DP1[2 * i - 1].first == DOCK_2 && DP1[2 * i].first == DOCK_1) {
			tcm2.N = st.GetVertices()[P1[i - 1]];
			tcm2.SM1 = st.GetVertices()[P1[i - 1]]->GetModuleReference();
			tcm2.SM2 = st.GetVertices()[P1[i]]->GetModuleReference();
			tcm2.D1 = DOCK_2;
			tcm2.D2 = DOCK_1;
		}
	}
	for (int i = 1; i < P2.size(); i++) {
		if (DP2[2 * i - 2].first == DOCK_2 && DP2[2 * i - 1].first == DOCK_1) {
			tcm2.N = st.GetVertices()[P2[i - 1]];
			tcm2.SM1 = st.GetVertices()[P2[i - 1]]->GetModuleReference();
			tcm2.SM2 = st.GetVertices()[P2[i]]->GetModuleReference();
			tcm2.D1 = DOCK_2;
			tcm2.D2 = DOCK_1;
		}
	}

	if (cNode2->GetDockFacePath().size() > 2) {
		tcm2.Command = "DisconnectToReconfigureI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode2->GetDockFacePath()[0].first), tcm2));
	}
	else {
		tcm2.Command = "DisconnectToReconfigure";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode2->GetDockFacePath()[0].first), tcm2));
	}

	if (cNode1->GetDockFacePath().size() > 2) {
		tcm1.Command = "ConnectToReconfigureI";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode1->GetDockFacePath()[0].first), tcm1));
	}
	else {
		tcm1.Command = "ConnectToReconfigure";
		AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode1->GetDockFacePath()[0].first), tcm1));
	}

}




///Collision detection
/**
* @brief collision function
* @param point point to check
* @return collision (true) or not (false)
*/
bool ReconfDemoQ2Behavior::CollisionFunction(std::vector<float> point) {
	return IsInCollisionWithGroundDetailed(point) || IsInSelfCollisionDetailed(point);
}
/**
* @brief state valid
* @param point point to check
* @return true if state valid false otherwise
*/
bool ReconfDemoQ2Behavior::StateValid(std::vector<float> point) {
	return !CollisionFunction(point);
}
/**
* @brief detect self collision
* @param point point to check
* @return is position in self collision
*/
bool ReconfDemoQ2Behavior::IsInSelfCollision(std::vector<float> point) {
	vector<ModuleNode*> Mods(st.GetVertices().size());
	for (int i = 0; i<st.GetVertices().size(); i++) {
		Mods[i] = st.GetVertices()[i];
	}
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);
	for (int i = 0; i<Ts.size(); i++) {
		for (int j = i + 1; j<Ts.size(); j++) {
			FVector DiffVec = Ts[i].GetLocation() - Ts[j].GetLocation();
			if (DiffVec.Size() < 150.0) return true;
		}
	}
	return false;
}
/**
* @brief detect self collision
* @param point point to check
* @return is position in self collision
*/
bool ReconfDemoQ2Behavior::IsInSelfCollisionDetailed(std::vector<float> point) {
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
	bool isObjectConnected = false;
	int objectTs = -1;
	for (int i = 0; i < st.GetVertices().size(); i++) {
		if (st.GetVertices()[i]->GetAmIConnectedToObject()) {
			isObjectConnected = true;
			objectTs = i;
		}
	}
	FTransform obTrans;
	if (isObjectConnected) {
		ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[objectTs]->GetDockFacePath()[st.GetVertices()[objectTs]->GetDockFacePath().size() - 1].first;
		ModuleDockFace EEDockFace;
		if (LastDockFace == DOCK_0) {
			EEDockFace = DOCK_1;
		}
		else {
			EEDockFace = DOCK_0;
		}
		ModuleMotorVector currJoints(point[3 * objectTs + 0], point[3 * objectTs + 1], point[3 * objectTs + 2]);
		if (EEDockFace == DOCK_0) {
			obTrans = FTransform(FVector(ObjectExtents.X / 2.0, 0, 0))*
				SuperbotKinematics::computeTransformToDock(currJoints, DOCK_0)*
				Ts[objectTs] * LocalBaseTransform;
		}
		else {
			obTrans = FTransform(FVector(-ObjectExtents.X / 2.0, 0, 0))*
				SuperbotKinematics::computeTransformToDock(currJoints, DOCK_1)*
				Ts[objectTs] * LocalBaseTransform;
		}
	}
	else {
		obTrans = FTransform(FVector(-ObjectExtents.X / 2.0, 0, 0))*ModuleBaseToObjectTransform*ActualBaseTransform;
	}
	physx::PxTransform transObject = U2PTransform(obTrans);
	PxBoxGeometry objGeom(ObjectExtents.X / 2.0, ObjectExtents.Y / 2.0, ObjectExtents.Z / 2.0);
	for (int i = 0; i<Ts.size(); i++) {
		for (int j = i + 1; j < Ts.size(); j++) {

			FTransform MInnerTrans1 = FTransform(FVector(30.0, 0.0, 0))*Ts[i] * LocalBaseTransform;
			FTransform SInnerTrans1 = FTransform(FVector(-30.0, 0.0, 0))*Ts[i] * LocalBaseTransform;
			SInnerTrans1 = FTransform(FQuat(FVector(1, 0, 0), (M_PI / 180.0)*point[3 * i + 1]))*SInnerTrans1;
			ModuleMotorVector currJoints1(point[3 * i + 0], point[3 * i + 1], point[3 * i + 2]);
			FTransform MOuterTrans1 = SuperbotKinematics::computeTransformToDock(currJoints1, DOCK_0)*
				Ts[i] * LocalBaseTransform;
			FTransform SOuterTrans1 = SuperbotKinematics::computeTransformToDock(currJoints1, DOCK_1)*
				Ts[i] * LocalBaseTransform;
			FTransform MOuterLeftTrans1 = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterTrans1;
			FTransform MOuterRightTrans1 = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterTrans1;
			FTransform SOuterLeftTrans1 = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterTrans1;
			FTransform SOuterRightTrans1 = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterTrans1;
			MOuterTrans1 = FTransform(FVector(-10, 0, 0))*MOuterTrans1;
			SOuterTrans1 = FTransform(FVector(10, 0, 0))*SOuterTrans1;

			FTransform MInnerTrans2 = FTransform(FVector(30.0, 0.0, 0))*Ts[j] * LocalBaseTransform;
			FTransform SInnerTrans2 = FTransform(FVector(-30.0, 0.0, 0))*Ts[j] * LocalBaseTransform;
			SInnerTrans2 = FTransform(FQuat(FVector(1, 0, 0), (M_PI / 180.0)*point[3 * j + 1]))*SInnerTrans2;
			ModuleMotorVector currJoints2(point[3 * j + 0], point[3 * j + 1], point[3 * j + 2]);
			FTransform MOuterTrans2 = SuperbotKinematics::computeTransformToDock(currJoints2, DOCK_0)*
				Ts[j] * LocalBaseTransform;
			FTransform SOuterTrans2 = SuperbotKinematics::computeTransformToDock(currJoints2, DOCK_1)*
				Ts[j] * LocalBaseTransform;
			FTransform MOuterLeftTrans2 = FTransform(FVector(-45.0, 0, 37.5 + 6.0))*MOuterTrans2;
			FTransform MOuterRightTrans2 = FTransform(FVector(-45.0, 0, -37.5 - 6.0))*MOuterTrans2;
			FTransform SOuterLeftTrans2 = FTransform(FVector(45.0, 0, 37.5 + 6.0))*SOuterTrans2;
			FTransform SOuterRightTrans2 = FTransform(FVector(45.0, 0, -37.5 - 6.0))*SOuterTrans2;
			MOuterTrans2 = FTransform(FVector(-10, 0, 0))*MOuterTrans2;
			SOuterTrans2 = FTransform(FVector(10, 0, 0))*SOuterTrans2;


			physx::PxTransform trans11 = U2PTransform(MInnerTrans1);
			physx::PxBoxGeometry geom11(25, 30, 30);
			physx::PxTransform trans21 = U2PTransform(SInnerTrans1);
			physx::PxBoxGeometry geom21(25, 30, 30);
			physx::PxTransform trans31 = U2PTransform(MOuterTrans1);
			physx::PxBoxGeometry geom31(2, 30, 30);
			physx::PxTransform trans41 = U2PTransform(SOuterTrans1);
			physx::PxBoxGeometry geom41(2, 30, 30);
			physx::PxTransform trans51 = U2PTransform(MOuterLeftTrans1);
			physx::PxBoxGeometry geom51(40, 30, 4);
			physx::PxTransform trans61 = U2PTransform(MOuterRightTrans1);
			physx::PxBoxGeometry geom61(40, 30, 4);
			physx::PxTransform trans71 = U2PTransform(SOuterLeftTrans1);
			physx::PxBoxGeometry geom71(40, 30, 4);
			physx::PxTransform trans81 = U2PTransform(SOuterRightTrans1);
			physx::PxBoxGeometry geom81(40, 30, 4);

			std::vector<physx::PxBoxGeometry> boxGeoms1{ geom11, geom21, geom31, geom41, geom51, geom61, geom71, geom81 };
			std::vector<physx::PxTransform> boxTrans1{ trans11, trans21, trans31, trans41, trans51, trans61, trans71, trans81 };


			physx::PxTransform trans12 = U2PTransform(MInnerTrans2);
			physx::PxBoxGeometry geom12(25, 30, 30);
			physx::PxTransform trans22 = U2PTransform(SInnerTrans2);
			physx::PxBoxGeometry geom22(30, 30, 30);
			physx::PxTransform trans32 = U2PTransform(MOuterTrans2);
			physx::PxBoxGeometry geom32(2, 30, 30);
			physx::PxTransform trans42 = U2PTransform(SOuterTrans2);
			physx::PxBoxGeometry geom42(2, 30, 30);
			physx::PxTransform trans52 = U2PTransform(MOuterLeftTrans2);
			physx::PxBoxGeometry geom52(40, 30, 4);
			physx::PxTransform trans62 = U2PTransform(MOuterRightTrans2);
			physx::PxBoxGeometry geom62(40, 30, 4);
			physx::PxTransform trans72 = U2PTransform(SOuterLeftTrans2);
			physx::PxBoxGeometry geom72(40, 30, 4);
			physx::PxTransform trans82 = U2PTransform(SOuterRightTrans2);
			physx::PxBoxGeometry geom82(40, 30, 4);

			std::vector<physx::PxBoxGeometry> boxGeoms2{ geom12, geom22, geom32, geom42, geom52, geom62, geom72, geom82 };
			std::vector<physx::PxTransform> boxTrans2{ trans12, trans22, trans32, trans42, trans52, trans62, trans72, trans82 };



			if (physx::PxGeometryQuery::overlap(geom11, trans11, geom12, trans12) ||
				physx::PxGeometryQuery::overlap(geom21, trans21, geom22, trans22) ||
				physx::PxGeometryQuery::overlap(geom31, trans31, geom32, trans32) ||
				physx::PxGeometryQuery::overlap(geom41, trans41, geom42, trans42) ||
				physx::PxGeometryQuery::overlap(geom51, trans51, geom52, trans52) ||
				physx::PxGeometryQuery::overlap(geom61, trans61, geom62, trans62) ||
				physx::PxGeometryQuery::overlap(geom71, trans71, geom72, trans72) ||
				physx::PxGeometryQuery::overlap(geom81, trans81, geom82, trans82)) {
				return true;
			}


		}
	}
	for (int i = 0; i<Ts.size(); i++) {
		for (int j = i + 1; j<Ts.size(); j++) {
			FVector DiffVec = Ts[i].GetLocation() - Ts[j].GetLocation();
			//if (DiffVec.Size() < 120.0) return true;
		}
	}
	return false;
}
/**
* @brief detect ground collision
* @param point point to check
* @return is position in collision with ground
*/
bool ReconfDemoQ2Behavior::IsInCollisionWithGround(std::vector<float> point) {
	vector<ModuleNode*> Mods(st.GetVertices().size());
	ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
		st.GetVertices()[GroundModule]->GetJointAngles()[1],
		st.GetVertices()[GroundModule]->GetJointAngles()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);

	vector<ModuleMotorVector> mvsFinals;
	vector<ModuleDockFace> mvsDocks;
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
	physx::PxTransform transGround;
	physx::PxBoxGeometry groundGeometry;
	if (GDock == DOCK_0) {
		BaseTransform = FTransform(FVector(50, 0, 0))*BaseTransform;
	}
	else {
		BaseTransform = FTransform(FVector(-50, 0, 0))*BaseTransform;
	}
	physx::PxTransform transBase = U2PTransform(FTransform(FVector(-50, 0, 0))*ActualGroundTransform/*BaseTransform*/);
	groundGeometry = physx::PxBoxGeometry(25, 1000, 1000);
	for (int i = 0; i<Ts.size(); i++) {
		physx::PxTransform transTs = U2PTransform(Ts[i]);
		physx::PxBoxGeometry geomTs(40, 40, 40);
		if (physx::PxGeometryQuery::overlap(geomTs, transTs, groundGeometry, transBase)) {
			return true;
		}
	}
	BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	int EECount = 0;
	for (int i = 0; i<Mods.size(); i++) {
		if (Mods[i]->GetAmIEndEffector()) {
			FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinals[EECount], mvsDocks[EECount])*
				Ts[i] * BaseTransform;
			EECount++;
			if (mvsDocks[EECount] == DOCK_0) {
				FinalFKActorTrans = FTransform(FVector(-17, 0, 0))*FinalFKActorTrans;
			}
			else {
				FinalFKActorTrans = FTransform(FVector(17, 0, 0))*FinalFKActorTrans;
			}
			physx::PxTransform transTs = U2PTransform(FinalFKActorTrans);
			physx::PxBoxGeometry geomTs = PxBoxGeometry(8, 60, 60);
			if (physx::PxGeometryQuery::overlap(geomTs, transTs, groundGeometry, transBase)) {
				return true;
			}
		}
	}
	return false;
}
/**
* @brief detect ground collision
* @param point point to check
* @return is position in collision with ground
*/
bool ReconfDemoQ2Behavior::IsInCollisionWithGroundDetailed(std::vector<float> point) {
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
	FTransform GroundFix = FTransform(FVector(-105, 0, 0));
	if (GDock == DOCK_0) {
		//FTransform GroundFix = FTransform(FVector(-105, 0, 0));
	}
	physx::PxTransform transBase = U2PTransform(GroundFix*AGroundTransform);
	groundGeometry = physx::PxBoxGeometry(100, 1000, 1000);
	bool isObjectConnected = false;
	int objectTs = -1;
	for (int i = 0; i < st.GetVertices().size(); i++) {
		if (st.GetVertices()[i]->GetAmIConnectedToObject()) {
			isObjectConnected = true;
			objectTs = i;
		}
	}
	FTransform obTrans;
	if (isObjectConnected) {
		ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[objectTs]->GetDockFacePath()[st.GetVertices()[objectTs]->GetDockFacePath().size() - 1].first;
		ModuleDockFace EEDockFace;
		if (LastDockFace == DOCK_0) {
			EEDockFace = DOCK_1;
		}
		else {
			EEDockFace = DOCK_0;
		}
		ModuleMotorVector currJoints(point[3 * objectTs + 0], point[3 * objectTs + 1], point[3 * objectTs + 2]);
		if (EEDockFace == DOCK_0) {
			obTrans = FTransform(FVector(ObjectExtents.X / 2.0, 0, 0))*
				SuperbotKinematics::computeTransformToDock(currJoints, DOCK_0)*
				Ts[objectTs] * LocalBaseTransform;
		}
		else {
			obTrans = FTransform(FVector(-ObjectExtents.X / 2.0, 0, 0))*
				SuperbotKinematics::computeTransformToDock(currJoints, DOCK_1)*
				Ts[objectTs] * LocalBaseTransform;
		}
	}
	else {
		obTrans = FTransform(FVector(-ObjectExtents.X / 2.0, 0, 0))*ModuleBaseToObjectTransform*ActualBaseTransform;
	}
	physx::PxTransform transObject = U2PTransform(obTrans);
	PxBoxGeometry objGeom(ObjectExtents.X / 2.0, ObjectExtents.Y / 2.0, ObjectExtents.Z / 2.0);
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
		physx::PxBoxGeometry geom1(25, 30, 30);
		physx::PxTransform trans2 = U2PTransform(SInnerTrans);
		physx::PxBoxGeometry geom2(25, 30, 30);
		physx::PxTransform trans3 = U2PTransform(MOuterTrans);
		physx::PxBoxGeometry geom3(4, 30, 30);
		physx::PxTransform trans4 = U2PTransform(SOuterTrans);
		physx::PxBoxGeometry geom4(4, 30, 30);
		physx::PxTransform trans5 = U2PTransform(MOuterLeftTrans);
		physx::PxBoxGeometry geom5(40, 30, 6);
		physx::PxTransform trans6 = U2PTransform(MOuterRightTrans);
		physx::PxBoxGeometry geom6(40, 30,  6);
		physx::PxTransform trans7 = U2PTransform(SOuterLeftTrans);
		physx::PxBoxGeometry geom7(40, 30, 6);
		physx::PxTransform trans8 = U2PTransform(SOuterRightTrans);
		physx::PxBoxGeometry geom8(40, 30, 6);
		if (physx::PxGeometryQuery::overlap(geom1, trans1, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom2, trans2, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom3, trans3, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom4, trans4, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom5, trans5, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom6, trans6, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom7, trans7, groundGeometry, transBase) ||
			physx::PxGeometryQuery::overlap(geom8, trans8, groundGeometry, transBase)/* ||
			physx::PxGeometryQuery::overlap(geom1, trans1, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(geom2, trans2, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(geom3, trans3, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(geom4, trans4, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(geom5, trans5, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(geom6, trans6, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(geom7, trans7, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(geom8, trans8, objGeom, transObject) ||
			physx::PxGeometryQuery::overlap(objGeom, transObject, groundGeometry, transBase)*/) {
			return true;
		}
	}
	return false;
}




///Path planning functionality
/**
* @brief plan path from current angles to 0 angles (default)
* @return true if planning completed, false otherwise
*/
bool ReconfDemoQ2Behavior::PlanPathCurrentAnglesTo0Angles() {
	if (PPCounter == 0) {
		Path.clear();
		HaveInitiatedPP = false;
		HaveCompletedPP = false;
	}
	if (HaveInitiatedPP && !HaveCompletedPP) {
		HaveCompletedPP = RRTWorker->IsFinished();
		GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Planning Path To 0. Num Nodes: %d"), RRTWorker->GetGraphSize()));
		if (HaveCompletedPP) {
			vector<float> zeros(st.GetVertices().size() * 3);
			for (int i = 0; i < zeros.size(); i++) {
				zeros[i] = 0.0;
			}
			Path.push_back(zeros);
			GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Red,
				FString::Printf(TEXT("Done Planning")));
			RRTWorker->Stop();
			RRTWorker->Shutdown();
			PPCounter = 0;
			return true;
		}
	}
	else {
		HaveInitiatedPP = true;
		std::vector<std::pair<float, float> > run(st.GetVertices().size() * 3);
		std::vector<std::pair<float, float> > vel(st.GetVertices().size() * 3);
		std::vector<float> goal(st.GetVertices().size() * 3);
		std::vector<float> start(st.GetVertices().size() * 3);
		for (int i = 0; i < vel.size(); i++) {
			run[i] = std::pair<float, float>(-90, 90);
			vel[i] = std::pair<float, float>(-90, 90);
			goal[i] = 0.0;
		}
		for (int i = 0; i<st.GetVertices().size(); i++) {
			start[3 * i + 0] = st.GetVertices()[i]->GetJointAngles()[0];
			start[3 * i + 1] = st.GetVertices()[i]->GetJointAngles()[1];
			start[3 * i + 2] = st.GetVertices()[i]->GetJointAngles()[2];
		}
		CurrentPathElement = 0;
		float FitVal;
		vector<ModuleNode*> Mods(st.GetVertices().size());
		for (int i = 0; i < st.GetVertices().size(); i++) {
			Mods[i] = st.GetVertices()[i];
		}
		//BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
		/*PASOWorker = FPASOWorker::PASOInit(50, 50, st.GetVertices().size() * 3, 100, run, vel, 5.0,
			std::bind(&ReconfDemoQ2Behavior::FitnessPSO, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
			std::bind(&ReconfDemoQ2Behavior::StateValid, this, std::placeholders::_1),
			std::bind(&ReconfDemoQ2Behavior::Distance, this, std::placeholders::_1,
				std::placeholders::_2),
			start, goal, Path, &FitVal);*/
		GEngine->AddOnScreenDebugMessage(ValidKey, 5.0, FColor::Green, FString::Printf(TEXT("Valid: Start (%d), Goal (%d)"), StateValid(start), StateValid(goal)));
		RRTWorker = FRRTWorker::RRTInit(5000, st.GetVertices().size() * 3, 100, run, 20.0,
			std::bind(&ReconfDemoQ2Behavior::StateValid, this, std::placeholders::_1),
			std::bind(&ReconfDemoQ2Behavior::Distance, this, std::placeholders::_1,
				std::placeholders::_2),
			start, goal, Path, &FitVal);
	}
	PPCounter++;
	return false;
}
/**
* @brief find optimal goals for IK procedure
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::FindGoalAnglesWithIK() {
	if (IKCounter == 0) {
		HaveInitiatedIK = false;
		HaveCompletedIK = false;
	}

	if (HaveInitiatedIK && !HaveCompletedIK) {
		HaveCompletedIK = PSOWorker->IsFinished();
		float IKError = 1000.0;
		if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
			IKError = 1000.0;
		}
		else {
			IKError = PSOWorker->GetCurrentUpperBound();
		}
		GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
			FString::Printf(TEXT("IK Current Error: %f"), IKError));
		GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
		if (HaveCompletedIK) {
			GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("IK Finished")));
			PSOWorker->Stop();
			PSOWorker->Shutdown();
			IKCounter = 0;
			return true;
		}
	}
	else {
		std::vector<int> PossibleEndEffectors;
		for (int i = 1; i < st.GetVertices().size(); i++) {
			ModuleNode *smn = st.GetVertices()[i];
			if (smn->GetAmIEndEffector() && !smn->GetAmIConnectedToObject()) {
				PossibleEndEffectors.push_back(i);
			}
		}
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
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
			st.GetVertices()[GroundModule]->GetJointAngles()[1],
			st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		if (PossibleEndEffectors.size() > 1) {
			std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
			int RandEffector = posRand(Generator);
			cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
			SelectedEndEffector = PossibleEndEffectors[RandEffector];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else if (PossibleEndEffectors.size() == 1) {
			SelectedEndEffector = PossibleEndEffectors[0];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else {
			SelectedEndEffector = -1;
		}
		TActorIterator<ADirectionActor> DirectionActorIt = TActorIterator<ADirectionActor>(this->World);
		bool DirectionSet = false;
		if (DirectionActorIt) {
			TargetRandVector = (*DirectionActorIt)->GetDirection();
			TargetYaw = (*DirectionActorIt)->GetYaw();
			DirectionSet = true;
		}
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
			ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		CurrentX = FullBaseTransform.GetLocation().X;
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
		FTransform GroundTransform = Floor->GetTransform();
		GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
		FTransform ManipulatorObjectTransform;
		if (ManipOb) {
			ManipulatorObjectTransform = ManipOb->GetTransform();
			ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
			ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
			ModuleBaseToObjectTransform = FTransform(FVector(0, 0, ObjectExtents.Z / 2.0))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
		}
		FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
		BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
		FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
		ModuleBaseToGroundTransform = BaseToGround;
		FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundTransform = InvV*BaseToGround;
		ActualGroundTransform = BaseToGround*LocalBaseTransform;

		if (SelectedEndEffector != -1) {
			std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
			std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
			for (int i = 0; i < st.GetVertices().size() * 3; i++)
			{
				posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
			}
			SolutionPos = vector<float>(st.GetVertices().size() * 3);
			PSOWorker = FBBPSOWorker::BBPSOInit(20, 50, st.GetVertices().size() * 3, posB, velB, 3.0,
				std::bind(&ReconfDemoQ2Behavior::Fitness, this,
					std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
				std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
				SolutionPos, &SolutionFitness);
			HaveInitiatedIK = true;
		}
		else {
			PS = NULL;
		}
	}
	IKCounter++;
	return false;
}
/**
* @brief find optimal goal angles for switching hands
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::FindGoalAnglesForSwitch() {
	if (SwitchIKCounter == 0) {
		HaveInitiatedIK = false;
		HaveCompletedIK = false;
	}

	if (HaveInitiatedIK && !HaveCompletedIK) {
		HaveCompletedIK = PSOWorker->IsFinished();
		float IKError = 1000.0;
		if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
			IKError = 1000.0;
		}
		else {
			IKError = PSOWorker->GetCurrentUpperBound();
		}
		GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
			FString::Printf(TEXT("IK To Switch Current Error: %f"), IKError));
		GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
		if (HaveCompletedIK) {
			GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("IK Finished")));
			PSOWorker->Stop();
			PSOWorker->Shutdown();
			SwitchIKCounter = 0;
			return true;
		}
	}
	else {
		std::vector<int> PossibleEndEffectors;
		for (int i = 1; i < st.GetVertices().size(); i++) {
			ModuleNode *smn = st.GetVertices()[i];
			if (smn->GetAmIEndEffector()) {
				PossibleEndEffectors.push_back(i);
			}
		}
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
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
			st.GetVertices()[GroundModule]->GetJointAngles()[1],
			st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		if (PossibleEndEffectors.size() > 1) {
			std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
			int RandEffector = posRand(Generator);
			cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
			SelectedEndEffector = PossibleEndEffectors[RandEffector];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else if (PossibleEndEffectors.size() == 1) {
			SelectedEndEffector = PossibleEndEffectors[0];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else {
			SelectedEndEffector = -1;
		}
		TActorIterator<ADirectionActor> DirectionActorIt = TActorIterator<ADirectionActor>(this->World);
		bool DirectionSet = false;
		if (DirectionActorIt) {
			TargetRandVector = (*DirectionActorIt)->GetDirection();
			TargetYaw = (*DirectionActorIt)->GetYaw();
			DirectionSet = true;
		}
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
			ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();

		FTransform GroundTransform = Floor->GetTransform();
		GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
		FTransform ManipulatorObjectTransform;
		if (ManipOb) {
			ManipulatorObjectTransform = ManipOb->GetTransform();
			ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
			ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
			ModuleBaseToObjectTransform = FTransform(FVector(0, 0, ObjectExtents.Z / 2.0))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
		}
		FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
		BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
		FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
		ModuleBaseToGroundTransform = BaseToGround;
		FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundTransform = InvV*BaseToGround;
		ActualGroundTransform = BaseToGround*LocalBaseTransform;

		if (SelectedEndEffector != -1) {
			std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
			std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
			for (int i = 0; i < st.GetVertices().size() * 3; i++)
			{
				posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
			}
			SolutionPos = vector<float>(st.GetVertices().size() * 3);
			PSOWorker = FBBPSOWorker::BBPSOInit(500, 1000, st.GetVertices().size() * 3, posB, velB, 3.0,
				std::bind(&ReconfDemoQ2Behavior::FitnessSwitch, this,
					std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
				std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
				SolutionPos, &SolutionFitness);
			HaveInitiatedIK = true;
		}
		else {
			PS = NULL;
		}
	}
	SwitchIKCounter++;
	return false;
}
/**
* @brief find optimal goal angles for picking up object
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::FindGoalAnglesForObject() {
	if (ObjectIKCounter == 0) {
		HaveInitiatedIK = false;
		HaveCompletedIK = false;
	}

	if (HaveInitiatedIK && !HaveCompletedIK) {
		HaveCompletedIK = PSOWorker->IsFinished();
		float IKError = 1000.0;
		if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
			IKError = 1000.0;
		}
		else {
			IKError = PSOWorker->GetCurrentUpperBound();
		}
		GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
			FString::Printf(TEXT("IK To Object Current Error: %f"), IKError));
		GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
		if (HaveCompletedIK) {
			GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("IK Finished")));
			PSOWorker->Stop();
			PSOWorker->Shutdown();
			ObjectIKCounter = 0;
			return true;
		}
	}
	else {
		std::vector<int> PossibleEndEffectors;
		for (int i = 1; i < st.GetVertices().size(); i++) {
			ModuleNode *smn = st.GetVertices()[i];
			if (smn->GetAmIEndEffector()) {
				PossibleEndEffectors.push_back(i);
			}
		}
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
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
			st.GetVertices()[GroundModule]->GetJointAngles()[1],
			st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		if (PossibleEndEffectors.size() > 1) {
			std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
			int RandEffector = posRand(Generator);
			cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
			SelectedEndEffector = PossibleEndEffectors[RandEffector];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else if (PossibleEndEffectors.size() == 1) {
			SelectedEndEffector = PossibleEndEffectors[0];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else {
			SelectedEndEffector = -1;
		}
		TActorIterator<ADirectionActor> DirectionActorIt = TActorIterator<ADirectionActor>(this->World);
		bool DirectionSet = false;
		if (DirectionActorIt) {
			TargetRandVector = (*DirectionActorIt)->GetDirection();
			TargetYaw = (*DirectionActorIt)->GetYaw();
			DirectionSet = true;
		}
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
			ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		CurrentX = FullBaseTransform.GetLocation().X;
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
		FTransform GroundTransform = Floor->GetTransform();
		GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
		FTransform ManipulatorObjectTransform;
		if (ManipOb) {
			ManipulatorObjectTransform = ManipOb->GetTransform();
			ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
			ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
			ModuleBaseToObjectTransform = FTransform(FVector(0, 0, ObjectExtents.Z / 2.0))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
		}
		FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
		BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
		FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
		ModuleBaseToGroundTransform = BaseToGround;
		FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundTransform = InvV*BaseToGround;
		ActualGroundTransform = BaseToGround*LocalBaseTransform;

		if (SelectedEndEffector != -1) {
			std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
			std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
			for (int i = 0; i < st.GetVertices().size() * 3; i++)
			{
				posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
			}
			SolutionPos = vector<float>(st.GetVertices().size() * 3);
			PSOWorker = FBBPSOWorker::BBPSOInit(20, 50, st.GetVertices().size() * 3, posB, velB, 3.0,
				std::bind(&ReconfDemoQ2Behavior::FitnessObject, this,
					std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
				std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
				SolutionPos, &SolutionFitness);
			HaveInitiatedIK = true;
		}
		else {
			PS = NULL;
		}
	}
	ObjectIKCounter++;
	return false;
}
/**
* @brief find optimal goal angles for picking up object
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::FindGoalAnglesForObjectSetDown() {
	if (ObjectIKCounter == 0) {
		HaveInitiatedIK = false;
		HaveCompletedIK = false;
	}

	if (HaveInitiatedIK && !HaveCompletedIK) {
		HaveCompletedIK = PSOWorker->IsFinished();
		float IKError = 1000.0;
		if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
			IKError = 1000.0;
		}
		else {
			IKError = PSOWorker->GetCurrentUpperBound();
		}
		GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
			FString::Printf(TEXT("IK To Object Set Down Current Error: %f"), IKError));
		GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
		if (HaveCompletedIK) {
			GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("IK Finished")));
			PSOWorker->Stop();
			PSOWorker->Shutdown();
			ObjectIKCounter = 0;
			return true;
		}
	}
	else {
		std::vector<int> PossibleEndEffectors;
		for (int i = 1; i < st.GetVertices().size(); i++) {
			ModuleNode *smn = st.GetVertices()[i];
			if (smn->GetAmIEndEffector() && smn->GetAmIConnectedToObject()) {
				PossibleEndEffectors.push_back(i);
			}
		}
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
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
			st.GetVertices()[GroundModule]->GetJointAngles()[1],
			st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		if (PossibleEndEffectors.size() > 1) {
			std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
			int RandEffector = posRand(Generator);
			cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
			SelectedEndEffector = PossibleEndEffectors[RandEffector];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else if (PossibleEndEffectors.size() == 1) {
			SelectedEndEffector = PossibleEndEffectors[0];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else {
			SelectedEndEffector = -1;
		}
		TActorIterator<ADirectionActor> DirectionActorIt = TActorIterator<ADirectionActor>(this->World);
		bool DirectionSet = false;
		if (DirectionActorIt) {
			TargetRandVector = (*DirectionActorIt)->GetDirection();
			TargetYaw = (*DirectionActorIt)->GetYaw();
			DirectionSet = true;
		}
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
			ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		CurrentX = FullBaseTransform.GetLocation().X;
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
		FTransform GroundTransform = Floor->GetTransform();
		GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
		FTransform ManipulatorObjectTransform;
		if (ManipOb) {
			ManipulatorObjectTransform = ManipOb->GetTransform();
			ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
			ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
			ModuleBaseToObjectTransform = FTransform(FVector(0, 0, ObjectExtents.Z / 2.0))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
		}
		FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
		BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
		FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
		ModuleBaseToGroundTransform = BaseToGround;
		FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundTransform = InvV*BaseToGround;
		ActualGroundTransform = BaseToGround*LocalBaseTransform;

		if (SelectedEndEffector != -1) {
			std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
			std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
			for (int i = 0; i < st.GetVertices().size() * 3; i++)
			{
				posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
			}
			SolutionPos = vector<float>(st.GetVertices().size() * 3);
			PSOWorker = FBBPSOWorker::BBPSOInit(20, 50, st.GetVertices().size() * 3, posB, velB, 3.0,
				std::bind(&ReconfDemoQ2Behavior::FitnessObjectSetDown, this,
					std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
				std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
				SolutionPos, &SolutionFitness);
			HaveInitiatedIK = true;
		}
		else {
			PS = NULL;
		}
	}
	ObjectIKCounter++;
	return false;
}
/**
* @brief find optimal goal angles for reconfiguration
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::FindGoalAnglesForReconfigureToTree() {
	if (ReconfCounter2 == 0) {
		HaveInitiatedIK = false;
		HaveCompletedIK = false;
	}

	if (HaveInitiatedIK && !HaveCompletedIK) {
		HaveCompletedIK = PSOWorker->IsFinished();
		float IKError = 1000.0;
		if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
			IKError = 1000.0;
		}
		else {
			IKError = PSOWorker->GetCurrentUpperBound();
		}
		GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
			FString::Printf(TEXT("IK To Reconfigure to Tree Current Error: %f"), IKError));
		GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
		if (HaveCompletedIK) {
			GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("IK Finished")));
			PSOWorker->Stop();
			PSOWorker->Shutdown();
			ReconfCounter2 = 0;
			return true;
		}
	}
	else {
		std::vector<int> PossibleEndEffectors;
		for (int i = 1; i < st.GetVertices().size(); i++) {
			ModuleNode *smn = st.GetVertices()[i];
			if (smn->GetAmIEndEffector()) {
				PossibleEndEffectors.push_back(i);
			}
		}
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
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
			st.GetVertices()[GroundModule]->GetJointAngles()[1],
			st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		if (PossibleEndEffectors.size() > 1) {
			std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
			int RandEffector = posRand(Generator);
			cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
			SelectedEndEffector = PossibleEndEffectors[RandEffector];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else if (PossibleEndEffectors.size() == 1) {
			SelectedEndEffector = PossibleEndEffectors[0];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else {
			SelectedEndEffector = -1;
		}
		TActorIterator<ADirectionActor> DirectionActorIt = TActorIterator<ADirectionActor>(this->World);
		bool DirectionSet = false;
		if (DirectionActorIt) {
			TargetRandVector = (*DirectionActorIt)->GetDirection();
			TargetYaw = (*DirectionActorIt)->GetYaw();
			DirectionSet = true;
		}
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
			ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		CurrentX = FullBaseTransform.GetLocation().X;
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
		FTransform GroundTransform = Floor->GetTransform();
		GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
		FTransform ManipulatorObjectTransform;
		if (ManipOb) {
			ManipulatorObjectTransform = ManipOb->GetTransform();
			ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
			ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
			ModuleBaseToObjectTransform = FTransform(FVector(0, 0, ObjectExtents.Z / 2.0))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
		}
		FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
		BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
		FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
		ModuleBaseToGroundTransform = BaseToGround;
		FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundTransform = InvV*BaseToGround;
		ActualGroundTransform = BaseToGround*LocalBaseTransform;

		if (SelectedEndEffector != -1) {
			std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
			std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
			for (int i = 0; i < st.GetVertices().size() * 3; i++)
			{
				posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
			}
			SolutionPos = vector<float>(st.GetVertices().size() * 3);
			PSOWorker = FBBPSOWorker::BBPSOInit(30, 50, st.GetVertices().size() * 3, posB, velB, 3.0,
				std::bind(&ReconfDemoQ2Behavior::FitnessReconfigure2, this,
					std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
				std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
				SolutionPos, &SolutionFitness);
			HaveInitiatedIK = true;
		}
		else {
			PS = NULL;
		}
	}
	ReconfCounter2++;
	return false;
}
/**
* @brief find optimal goal angles for reconfiguration
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::FindGoalAnglesForReconfigureToSnake() {
	if (ReconfCounter == 0) {
		HaveInitiatedIK = false;
		HaveCompletedIK = false;
	}

	if (HaveInitiatedIK && !HaveCompletedIK) {
		HaveCompletedIK = PSOWorker->IsFinished();
		float IKError = 1000.0;
		if (PSOWorker->GetCurrentUpperBound() > 1000 || PSOWorker->GetCurrentUpperBound() < -1000) {
			IKError = 1000.0;
		}
		else {
			IKError = PSOWorker->GetCurrentUpperBound();
		}
		GEngine->AddOnScreenDebugMessage(IKErrorKey, 5.f, FColor::Red,
			FString::Printf(TEXT("IK To Object Set Down Current Error: %f"), IKError));
		GEngine->AddOnScreenDebugMessage(IKPartitionsKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
		if (HaveCompletedIK) {
			GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("IK Finished")));
			PSOWorker->Stop();
			PSOWorker->Shutdown();
			ReconfCounter = 0;
			return true;
		}
	}
	else {
		std::vector<int> PossibleEndEffectors;
		for (int i = 1; i < st.GetVertices().size(); i++) {
			ModuleNode *smn = st.GetVertices()[i];
			if (smn->GetAmIEndEffector()) {
				PossibleEndEffectors.push_back(i);
			}
		}
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
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
			st.GetVertices()[GroundModule]->GetJointAngles()[1],
			st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		if (PossibleEndEffectors.size() > 1) {
			std::uniform_int_distribution<> posRand(0, PossibleEndEffectors.size() - 1);
			int RandEffector = posRand(Generator);
			cout << "Chose end effector " << PossibleEndEffectors[RandEffector] << endl;
			SelectedEndEffector = PossibleEndEffectors[RandEffector];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else if (PossibleEndEffectors.size() == 1) {
			SelectedEndEffector = PossibleEndEffectors[0];
			ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
			if (LastDockFace == DOCK_0) {
				EEDock = DOCK_1;
			}
			else {
				EEDock = DOCK_0;
			}
		}
		else {
			SelectedEndEffector = -1;
		}
		TActorIterator<ADirectionActor> DirectionActorIt = TActorIterator<ADirectionActor>(this->World);
		bool DirectionSet = false;
		if (DirectionActorIt) {
			TargetRandVector = (*DirectionActorIt)->GetDirection();
			TargetYaw = (*DirectionActorIt)->GetYaw();
			DirectionSet = true;
		}
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
			ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		CurrentX = FullBaseTransform.GetLocation().X;
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
		FTransform GroundTransform = Floor->GetTransform();
		GroundTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
		FTransform ManipulatorObjectTransform;
		if (ManipOb) {
			ManipulatorObjectTransform = ManipOb->GetTransform();
			ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
			ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
			ModuleBaseToObjectTransform = FTransform(FVector(0, 0, ObjectExtents.Z / 2.0))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
		}
		FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
		BaseToGround = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*BaseToGround;
		FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
		ModuleBaseToGroundTransform = BaseToGround;
		FTransform InvV = FTransform(FVector(0, ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
			ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
		ModuleBaseToGroundTransform = InvV*BaseToGround;
		ActualGroundTransform = BaseToGround*LocalBaseTransform;

		if (SelectedEndEffector != -1) {
			std::vector<std::pair<float, float> > posB(st.GetVertices().size() * 3);
			std::vector<std::pair<float, float> > velB(st.GetVertices().size() * 3);
			for (int i = 0; i < st.GetVertices().size() * 3; i++)
			{
				posB[i] = std::pair<float, float>(-90, 90); velB[i] = std::pair<float, float>(-90, 90);
			}
			SolutionPos = vector<float>(st.GetVertices().size() * 3);
			PSOWorker = FBBPSOWorker::BBPSOInit(50, 50, st.GetVertices().size() * 3, posB, velB, 5.0,
				std::bind(&ReconfDemoQ2Behavior::FitnessReconfigure, this,
					std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
				std::vector<float> {0, 200, 400, 100}, std::vector<float> {0, 200, 400, 100},
				SolutionPos, &SolutionFitness);
			HaveInitiatedIK = true;
		}
		else {
			PS = NULL;
		}
	}
	ReconfCounter++;
	return false;
}
/**
* @brief plan path from current angles to goal angles
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::PlanPathCurrentAnglesToGoalAngles() {
	if (PPCounter == 0) {
		Path.clear();
		HaveInitiatedPP = false;
		HaveCompletedPP = false;
	}
	if (HaveInitiatedPP && !HaveCompletedPP) {
		GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Red,
			FString::Printf(TEXT("Planning Path To 0. Num Nodes: %d"), RRTWorker->GetGraphSize()));
		HaveCompletedPP = RRTWorker->IsFinished();
		if (HaveCompletedPP) {
			GEngine->AddOnScreenDebugMessage(PPDoneKey, 5.f, FColor::Green,
				FString::Printf(TEXT("PP Finished")));
			Path.push_back(SolutionPos);
			RRTWorker->Stop();
			RRTWorker->Shutdown();
			PPCounter = 0;
			return true;
		}
	}
	else {
		HaveInitiatedPP = true;
		std::vector<std::pair<float, float> > run(st.GetVertices().size() * 3);
		std::vector<std::pair<float, float> > vel(st.GetVertices().size() * 3);
		std::vector<float> goal(st.GetVertices().size() * 3);
		std::vector<float> start(st.GetVertices().size() * 3);
		for (int i = 0; i < vel.size(); i++) {
			run[i] = std::pair<float, float>(-90, 90);
			vel[i] = std::pair<float, float>(-90, 90);
			goal[i] = SolutionPos[i];
		}
		for (int i = 0; i < st.GetVertices().size(); i++) {
			start[3 * i + 0] = 0;
			start[3 * i + 1] = 0;
			start[3 * i + 2] = 0;
		}
		CurrentPathElement = 0;
		float FitVal;
		vector<ModuleNode*> Mods(st.GetVertices().size());
		for (int i = 0; i < st.GetVertices().size(); i++) {
			Mods[i] = st.GetVertices()[i];
		}
		BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
		/*PASOWorker = FPASOWorker::PASOInit(50, 50, st.GetVertices().size() * 3, 100, run, vel, 5.0,
			std::bind(&ReconfDemoQ2Behavior::FitnessPSO, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
			std::bind(&ReconfDemoQ2Behavior::StateValid, this, std::placeholders::_1),
			std::bind(&ReconfDemoQ2Behavior::Distance, this, std::placeholders::_1,
				std::placeholders::_2),
			start, goal, Path, &FitVal);*/
		GEngine->AddOnScreenDebugMessage(ValidKey, 5.0, FColor::Green, FString::Printf(TEXT("Valid: Start (%d), Goal (%d)"), StateValid(start), StateValid(goal)));
		RRTWorker = FRRTWorker::RRTInit(5000, st.GetVertices().size() * 3, 100, run, 20.0,
			std::bind(&ReconfDemoQ2Behavior::StateValid, this, std::placeholders::_1),
			std::bind(&ReconfDemoQ2Behavior::Distance, this, std::placeholders::_1,
				std::placeholders::_2),
			start, goal, Path, &FitVal);
	}
	PPCounter++;
	return false;
}
/**
* @brief execute a wait for a certain number of time steps
* @param Counter number of time steps to wait
* @return true if process completed false otherwise
*/
bool ReconfDemoQ2Behavior::ExecuteWait(int Counter) {
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
* @brief execute planned path
* @return true if process completed, false otherwise
*/
bool ReconfDemoQ2Behavior::ExecutePath() {
	if (PECounter == 0) {
		CurrentPathElement = 0;
		WaitCounter = 0;
		HaveSetJointAngles = false;
	}
	if (!HaveSetJointAngles && WaitCounter <= 0) {
		SetJointAnglesDistributed(Path[CurrentPathElement]);
		WaitCounter = 1;
		GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Blue,
			FString::Printf(TEXT("Remaining Path Size: %d"), Path.size() - CurrentPathElement));
		CurrentPathElement++;
		if (CurrentPathElement >= Path.size()) {
			GEngine->AddOnScreenDebugMessage(PPProgressKey, 5.f, FColor::Green,
				FString::Printf(TEXT("Execution Finished")));
			HaveSetJointAngles = true;
			PECounter = 0;
			WaitCounter = 0;
			return true;
		}
	}
	else {
		WaitCounter--;
	}
	PECounter++;
	return false;
}
/**
* @brief compute distance between point1 and point2
* @param point1 point number 1
* @param point2 point number 2
* @return euclidean distance between point1 and point2
*/
float ReconfDemoQ2Behavior::Distance(std::vector<float> point1, std::vector<float> point2) {
	float distance = 0.0;
	for (int i = 0; i<point1.size(); i++) {
		distance += (point1[i] - point2[i])*(point1[i] - point2[i]);
	}
	return sqrtf(distance);
}
/**
* @brief fitness for PASO
* @param P PSO particle
* @param st start vector
* @param tar target vector
*/
float ReconfDemoQ2Behavior::FitnessPSO(PSOParticle P, std::vector<float> start, std::vector<float> target) {
	float DistanceError = Distance(P.getPosition(), target);
	int CollisionVal = CollisionFunction(P.getPosition());
	return DistanceError + 1000 * CollisionVal;
}






///Inverse kinematics functionality
/**
* @brief get best transforms found by IK process
* @return best transforms
*/
std::vector<FTransform> ReconfDemoQ2Behavior::GetBestTransforms() {
	return BestTransformsFound;
}
/**
* @brief get best (solution) position
* @return best (solution) position
*/
std::vector<float> ReconfDemoQ2Behavior::GetSolutionPos() {
	return SolutionPos;
}
/**
* @brief get the transforms of modules for joint angles
* @param Mods modules
* @param JAngles joint angles
* @return transform of modules in tree
*/
vector<FTransform> ReconfDemoQ2Behavior::GetTransformsOfModulesForJointAngles(std::vector<ModuleNode*> Mods,
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
* @brief fitness function for IK
* @param P particle
* @param tar target
* @return fitness value
*/
float ReconfDemoQ2Behavior::Fitness(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	vector<ModuleNode*> Mods(st.GetVertices().size());
	for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
	ModuleMotorVector mvsFinal = ModuleMotorVector(P.GetPosition()[3 * SelectedEndEffector + 0],
		P.GetPosition()[3 * SelectedEndEffector + 1],
		P.GetPosition()[3 * SelectedEndEffector + 2]);
	FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, GetEndEffectorDockFace())*
		Ts[SelectedEndEffector] * BaseTransform;

	FTransform FullTargetTransform;
	FullTargetTransform = ModuleBaseToGroundTransform*BaseTransform;
	if (GDock == DOCK_1 || GDock == DOCK_0) {
		FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI))*FullTargetTransform;
	}
	FullTargetTransform = FTransform(FVector(0, 0, 350))*FTransform(FRotator(0, 0, TargetYaw))*FullTargetTransform;
	if (GDock == DOCK_1 || GDock == DOCK_0) {
		FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI))*FullTargetTransform;
	}
	if (EEDock == DOCK_0) {
		FullTargetTransform = FTransform(FVector(-10, 0, 0))*FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FullTargetTransform;
	}
	else {
		FullTargetTransform = FTransform(FVector(10, 0, 0))*FullTargetTransform;
	}
	FRotator DiffRot = FRotator(FullTargetTransform.GetRotation()) - FRotator(FinalFKActorTrans.GetRotation());
	FVector OrientVec = FVector(/*DiffRot.Roll*/0, DiffRot.Pitch, DiffRot.Yaw);
	FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
	FVector DiffVec2D(0, DiffPos.Y, DiffPos.Z);
	return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
		100 * IsInCollisionWithGroundDetailed(P.GetPosition());

}
/**
* @brief fitness function for IK
* @param P particle
* @param tar target
* @return fitness value
*/
float ReconfDemoQ2Behavior::FitnessObject(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	vector<ModuleNode*> Mods(st.GetVertices().size());
	for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
	ModuleMotorVector mvsFinal = ModuleMotorVector(P.GetPosition()[3 * SelectedEndEffector + 0],
		P.GetPosition()[3 * SelectedEndEffector + 1],
		P.GetPosition()[3 * SelectedEndEffector + 2]);
	FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, GetEndEffectorDockFace())*
		Ts[SelectedEndEffector] * BaseTransform;

	FTransform FullTargetTransform;
	FullTargetTransform = ModuleBaseToObjectTransform*BaseTransform;
	if (EEDock == DOCK_0) {
		FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FullTargetTransform;
	}
	FRotator DiffRot = FRotator(FullTargetTransform.GetRotation()) - FRotator(FinalFKActorTrans.GetRotation());
	FVector OrientVec = FVector(0, DiffRot.Pitch, DiffRot.Yaw);
	FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
	FVector DiffVec2D(0, DiffPos.Y, DiffPos.Z);
	return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
		100 * IsInCollisionWithGroundDetailed(P.GetPosition());

}
/**
* @brief fitness function for IK to object set down
* @param P particle
* @param tar target
* @return fitness value
*/
float ReconfDemoQ2Behavior::FitnessObjectSetDown(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	vector<ModuleNode*> Mods(st.GetVertices().size());
	for (int i = 0; i<st.GetVertices().size(); i++) { Mods[i] = st.GetVertices()[i]; }
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
	ModuleMotorVector mvsFinal = ModuleMotorVector(P.GetPosition()[3 * SelectedEndEffector + 0],
		P.GetPosition()[3 * SelectedEndEffector + 1],
		P.GetPosition()[3 * SelectedEndEffector + 2]);
	FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal, GetEndEffectorDockFace())*
		Ts[SelectedEndEffector] * BaseTransform;

	FTransform FullTargetTransform;
	FullTargetTransform = ModuleBaseToGroundTransform*BaseTransform;
	if (GDock == DOCK_1 || GDock == DOCK_0) {
		FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI))*FullTargetTransform;
	}
	FullTargetTransform = FTransform(FVector(0, 0, 350))*FTransform(FRotator(0, 0, 90))*FullTargetTransform;
	if (GDock == DOCK_1 || GDock == DOCK_0) {
		FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI))*FullTargetTransform;
	}
	if (EEDock == DOCK_0) {
		FullTargetTransform = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FullTargetTransform;
	}

	if (EEDock == DOCK_0) {
		FullTargetTransform = FTransform(FVector(-ObjectExtents.X / 6.0, 0, 0))*FullTargetTransform;
		FinalFKActorTrans = FTransform(FVector(ObjectExtents.X, 0, 0))*FinalFKActorTrans;
	}
	else {
		FullTargetTransform = FTransform(FVector(ObjectExtents.X / 6.0, 0, 0))*FullTargetTransform;
		FinalFKActorTrans = FTransform(FVector(-ObjectExtents.X, 0, 0))*FinalFKActorTrans;
	}
	FRotator DiffRot = FRotator(FullTargetTransform.GetRotation()) - FRotator(FinalFKActorTrans.GetRotation());
	FVector OrientVec = FVector(0, DiffRot.Pitch, DiffRot.Yaw);
	FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
	FVector DiffVec2D(0, DiffPos.Y, DiffPos.Z);
	return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
		100 * IsInCollisionWithGroundDetailed(P.GetPosition());

}
/***
* @brief fitness function for multi-branch IK switch
* @param P particle
* @param tar target
* @return fitness value
*/
float ReconfDemoQ2Behavior::FitnessSwitch(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	vector<ModuleNode*> Mods(st.GetVertices().size());
	vector<int> EndEffectors;
	for (int i = 0; i<st.GetVertices().size(); i++) {
		Mods[i] = st.GetVertices()[i];
		if (Mods[i]->GetAmIEndEffector() || Mods[i]->GetAmIConnectedToObject()) {
			EndEffectors.push_back(i);
		}
	}

	if (EndEffectors.size() != 2) { return 100000; }

	int EndEffector1 = EndEffectors[0];
	int EndEffector2 = EndEffectors[1];
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
	ModuleMotorVector mvsFinal1 = ModuleMotorVector(P.GetPosition()[3 * EndEffector1 + 0],
		P.GetPosition()[3 * EndEffector1 + 1],
		P.GetPosition()[3 * EndEffector1 + 2]);
	ModuleMotorVector mvsFinal2 = ModuleMotorVector(P.GetPosition()[3 * EndEffector2 + 0],
		P.GetPosition()[3 * EndEffector2 + 1],
		P.GetPosition()[3 * EndEffector2 + 2]);

	ModuleDockFace LastDockFace1 = (ModuleDockFace)Mods[EndEffector1]->GetDockFacePath()[Mods[EndEffector1]->GetDockFacePath().size() - 1].first;
	ModuleDockFace LastDockFace2 = (ModuleDockFace)Mods[EndEffector2]->GetDockFacePath()[Mods[EndEffector2]->GetDockFacePath().size() - 1].first;
	ModuleDockFace EEDock1;
	ModuleDockFace EEDock2;
	if (LastDockFace1 == DOCK_0) {
		EEDock1 = DOCK_1;
	}
	else {
		EEDock1 = DOCK_0;
	}
	if (LastDockFace2 == DOCK_0) {
		EEDock2 = DOCK_1;
	}
	else {
		EEDock2 = DOCK_0;
	}
	FTransform FinalFKActorTrans1 = SuperbotKinematics::computeTransformToDock(mvsFinal1, EEDock1)*
		Ts[EndEffector1] * BaseTransform;
	FTransform FinalFKActorTrans2 = SuperbotKinematics::computeTransformToDock(mvsFinal2, EEDock2)*
		Ts[EndEffector2] * BaseTransform;
	if (Mods[EndEffector1]->GetAmIConnectedToObject()) {
		if (EEDock1 == DOCK_0) {
			FinalFKActorTrans1 = FTransform(FVector(ObjectExtents.X, 0.0, 0.0))*FinalFKActorTrans1;
		}
		else {
			FinalFKActorTrans1 = FTransform(FVector(-ObjectExtents.X, 0.0, 0.0))*FinalFKActorTrans1;
		}
	}
	if (Mods[EndEffector2]->GetAmIConnectedToObject()) {
		if (EEDock2 == DOCK_0) {
			FinalFKActorTrans2 = FTransform(FVector(ObjectExtents.X, 0.0, 0.0))*FinalFKActorTrans2;
		}
		else {
			FinalFKActorTrans2 = FTransform(FVector(-ObjectExtents.X, 0.0, 0.0))*FinalFKActorTrans2;
		}
	}

	if ((EEDock1 == DOCK_0 && EEDock2 == DOCK_0) ||
		(EEDock1 == DOCK_1 && EEDock2 == DOCK_1)) {
		FinalFKActorTrans1 = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FinalFKActorTrans1;
	}
	else if ((EEDock1 == DOCK_0 && EEDock2 == DOCK_1) ||
		(EEDock1 == DOCK_1 && EEDock2 == DOCK_0)) {

	}
	FRotator DiffRot = FRotator(FinalFKActorTrans1.GetRotation()) - FRotator(FinalFKActorTrans2.GetRotation());
	FVector OrientVec = FVector(0, DiffRot.Pitch, DiffRot.Yaw);
	float Neg = 0.0;
	if (GDock == DOCK_1) {
		if (FinalFKActorTrans1.GetLocation().X < 100 || FinalFKActorTrans2.GetLocation().X < 100) {
			//Neg = 100;
		}
	}
	else {

	}
	FVector DiffPos = FinalFKActorTrans1.GetLocation() - FinalFKActorTrans2.GetLocation();
	return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
		100 * IsInCollisionWithGroundDetailed(P.GetPosition()) + Neg;

}
/***
* @brief fitness function for reconfiguration
* @param P particle
* @param tar target
* @return fitness value
*/
float ReconfDemoQ2Behavior::FitnessReconfigure(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	vector<ModuleNode*> Mods(st.GetVertices().size());
	vector<int> EndEffectors;
	for (int i = 0; i<st.GetVertices().size(); i++) {
		Mods[i] = st.GetVertices()[i];
		if (Mods[i]->GetAmIEndEffector() || Mods[i]->GetAmIConnectedToObject()) {
			EndEffectors.push_back(i);
		}
	}

	if (EndEffectors.size() != 2) { return 100000; }

	int EndEffector1 = EndEffectors[0];
	int EndEffector2 = EndEffectors[1];
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
	ModuleMotorVector mvsFinal1 = ModuleMotorVector(P.GetPosition()[3 * EndEffector1 + 0],
		P.GetPosition()[3 * EndEffector1 + 1],
		P.GetPosition()[3 * EndEffector1 + 2]);
	ModuleMotorVector mvsFinal2 = ModuleMotorVector(P.GetPosition()[3 * EndEffector2 + 0],
		P.GetPosition()[3 * EndEffector2 + 1],
		P.GetPosition()[3 * EndEffector2 + 2]);

	ModuleDockFace LastDockFace1 = (ModuleDockFace)Mods[EndEffector1]->GetDockFacePath()[Mods[EndEffector1]->GetDockFacePath().size() - 1].first;
	ModuleDockFace LastDockFace2 = (ModuleDockFace)Mods[EndEffector2]->GetDockFacePath()[Mods[EndEffector2]->GetDockFacePath().size() - 1].first;
	ModuleDockFace EEDock1;
	ModuleDockFace EEDock2;
	if (LastDockFace1 == DOCK_0) {
		EEDock1 = DOCK_1;
	}
	else {
		EEDock1 = DOCK_0;
	}
	if (LastDockFace2 == DOCK_0) {
		EEDock2 = DOCK_1;
	}
	else {
		EEDock2 = DOCK_0;
	}
	FTransform FinalFKActorTrans1 = SuperbotKinematics::computeTransformToDock(mvsFinal1, EEDock1)*
		Ts[EndEffector1] * BaseTransform;
	FTransform FinalFKActorTrans2 = SuperbotKinematics::computeTransformToDock(mvsFinal2, EEDock2)*
		Ts[EndEffector2] * BaseTransform;

	if ((EEDock1 == DOCK_0 && EEDock2 == DOCK_0) ||
		(EEDock1 == DOCK_1 && EEDock2 == DOCK_1)) {
		FinalFKActorTrans1 = FTransform(FQuat(FVector(0, 1, 0), M_PI), FVector(0, 0, 0))*FinalFKActorTrans1;
		//FinalFKActorTrans1 = FTransform(FQuat(FVector(1, 0, 0), M_PI), FVector(0, 0, 0))*FinalFKActorTrans1;
	}

	FRotator DiffRot = FRotator(FinalFKActorTrans1.GetRotation()) - FRotator(FinalFKActorTrans2.GetRotation());
	FVector OrientVec = FVector(DiffRot.Roll, DiffRot.Pitch, DiffRot.Yaw);
	FVector DiffPos = FinalFKActorTrans1.GetLocation() - FinalFKActorTrans2.GetLocation();
	return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
		100 * IsInCollisionWithGroundDetailed(P.GetPosition());
}
/***
* @brief fitness function for reconfiguration
* @param P particle
* @param tar target
* @return fitness value
*/
float ReconfDemoQ2Behavior::FitnessReconfigure2(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
	ModuleMotorVector mvsGround(P.GetPosition()[0], P.GetPosition()[1], P.GetPosition()[2]);
	FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock);
	vector<ModuleNode*> Mods(st.GetVertices().size());
	vector<int> EndEffectors;
	for (int i = 0; i<st.GetVertices().size(); i++) {
		Mods[i] = st.GetVertices()[i];
		if (Mods[i]->GetAmIEndEffector() || Mods[i]->GetAmIConnectedToObject()) {
			EndEffectors.push_back(i);
		}
	}

	if (EndEffectors.size() != 1) { return 100000; }

	int EndEffector1 = SelectedEndEffector;
	int EndEffector2 = 2;
	vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
	ModuleMotorVector mvsFinal1 = ModuleMotorVector(P.GetPosition()[3 * EndEffector1 + 0],
		P.GetPosition()[3 * EndEffector1 + 1],
		P.GetPosition()[3 * EndEffector1 + 2]);
	ModuleMotorVector mvsFinal2 = ModuleMotorVector(P.GetPosition()[3 * EndEffector2 + 0],
		P.GetPosition()[3 * EndEffector2 + 1],
		P.GetPosition()[3 * EndEffector2 + 2]);

	ModuleDockFace LastDockFace1 = (ModuleDockFace)Mods[EndEffector1]->GetDockFacePath()[Mods[EndEffector1]->GetDockFacePath().size() - 1].first;
	ModuleDockFace LastDockFace2 = (ModuleDockFace)Mods[EndEffector2]->GetDockFacePath()[Mods[EndEffector2]->GetDockFacePath().size() - 1].first;
	ModuleDockFace EEDock1;
	ModuleDockFace EEDock2;
	if (LastDockFace1 == DOCK_0) {
		EEDock1 = DOCK_1;
	}
	else {
		EEDock1 = DOCK_0;
	}
	EEDock2 = DOCK_3;
	FTransform FinalFKActorTrans1 = SuperbotKinematics::computeTransformToDock(mvsFinal1, EEDock1)*
		Ts[EndEffector1] * BaseTransform;
	FTransform FinalFKActorTrans2 = SuperbotKinematics::computeTransformToDock(mvsFinal2, EEDock2)*
		Ts[EndEffector2] * BaseTransform;
		
	FinalFKActorTrans1 = FTransform(FQuat(FVector(0, 1, 0), M_PI_2))*FinalFKActorTrans1;
	FinalFKActorTrans1 = FTransform(FQuat(FVector(0, 1, 0), M_PI))*FinalFKActorTrans1;

	FRotator DiffRot = FRotator(FinalFKActorTrans1.GetRotation()) - FRotator(FinalFKActorTrans2.GetRotation());
	FVector OrientVec = FVector(DiffRot.Roll, DiffRot.Pitch, DiffRot.Yaw);
	FVector DiffPos = FinalFKActorTrans1.GetLocation() - FinalFKActorTrans2.GetLocation();
	return DiffPos.Size() + OrientVec.Size() + 100 * IsInSelfCollisionDetailed(P.GetPosition()) +
		100 * IsInCollisionWithGroundDetailed(P.GetPosition());
}
/**
* @brief get target transform
* @return target transform
*/
FTransform ReconfDemoQ2Behavior::GetTargetTransform() {
	return this->TargetTransform;
}




///Kinematic discovery
/**
* @brief set joints distributed
* @param JAngles joint angles
*/
void ReconfDemoQ2Behavior::SetJointAnglesDistributed(std::vector<float> JAngles) {
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
void ReconfDemoQ2Behavior::InitializeKinematicTree() {
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
void ReconfDemoQ2Behavior::DiscoverKinematicStructure() {
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
void ReconfDemoQ2Behavior::ProcessMessages(vector<TreeMessage> messages) {
	for (int i = 0; i<messages.size(); i++) {
		TreeMessage mes = messages[i];
		if (mes.Command.compare("ConnectToReconfigure") == 0) {
			GEngine->AddOnScreenDebugMessage(DisconnectKey, 5.f, FColor::Red, FString("Connecting Module"));
			std::pair<ModuleConnectionPair, bool> p(ModuleConnectionPair((ASuperBotModule*)mes.SM1, (ASuperBotModule*)mes.SM2, mes.D1, mes.D2), true);
			AddConnectionAction(std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> >(CONNECT_MODULES, p));
		}
		else if (mes.Command.compare("ConnectToReconfigureI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "ConnectToReconfigureI";
			}
			else {
				mes.Command = "ConnectToReconfigure";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
		else if (mes.Command.compare("DisconnectToReconfigure") == 0) {
			GEngine->AddOnScreenDebugMessage(DisconnectKey, 5.f, FColor::Red, FString("Disconnecting Module"));
			std::pair<ModuleConnectionPair, bool> p(ModuleConnectionPair((ASuperBotModule*)mes.SM1, (ASuperBotModule*)mes.SM2, mes.D1, mes.D2), false);
			AddConnectionAction(std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> >(CONNECT_MODULES, p));
		}
		else if (mes.Command.compare("DisconnectToReconfigureI") == 0) {
			mes.CurrentPathElement += 2;
			ModuleDockFace d;
			if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
				mes.Command = "DisconnectToReconfigureI";
			}
			else {
				mes.Command = "DisconnectToReconfigure";
			}
			if (mes.N->GetDockFacePath().size() > 0) {
				d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
				AddTreeMessageAction(std::pair<ModuleAction, TreeMessage>(GetTreeActionForDock(d), mes));
			}
		}
		else if (mes.Command.compare("ReConnectObject") == 0) {
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
			HaveFoundAnglesForReconfigure = true;
			HavePlannedToReconfigureAngles = true;
			HaveExecutedReconfigureAngles = true;
			HaveWaitedReconfigure1 = true;
			HaveWaitedReconfigure2 = true;
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
			mes.ModuleRef = SModule;
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
			n->SetModuleReference(mes.ModuleRef);
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
void ReconfDemoQ2Behavior::UpdateCurrentAngles() {
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
void ReconfDemoQ2Behavior::UpdateDockEngagedStatus() {
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
void ReconfDemoQ2Behavior::UpdateDockEngagedToGroundStatus() {
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
void ReconfDemoQ2Behavior::UpdateDockEngagedToObjectStatus() {
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
void ReconfDemoQ2Behavior::UpdateDockDiffs() {
	int diffTotalDocks = 0;
	for (int i = 0; i<6; i++) {
		diffTotalDocks += abs(CDockDiffs[i]);
	}
	if (diffTotalDocks > 0) {
		GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Blue, FString("Reconfiguration Occurred"));
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
		if (diffTotalDocksToGround > 0 || diffTotalDocksToObject > 0 || diffTotalDocks > 0) {
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
void ReconfDemoQ2Behavior::UpdateEngagedToGround() {
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
void ReconfDemoQ2Behavior::UpdateEndEffectorStatus() {
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
void ReconfDemoQ2Behavior::UpdateConnectedToObject() {
	AmIConnectedToObject = (CurrentDockEngagedToObjectStatus[0] || CurrentDockEngagedToObjectStatus[1]);
}
/**
* @brief update object pose
*/
void ReconfDemoQ2Behavior::UpdateObjectPose() {
	if (GroundModule != -1 && SModule) {
		ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
			st.GetVertices()[GroundModule]->GetJointAngles()[1],
			st.GetVertices()[GroundModule]->GetJointAngles()[2]);
		FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround, GDock)*
			ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
		CurrentX = FullBaseTransform.GetLocation().X;
		//GEngine->AddOnScreenDebugMessage(IKDoneKey, 5.f, FColor::Red, FString::Printf(TEXT("Current X: %f"), CurrentX));
		FTransform ManipulatorObjectTransform;
		if (ManipOb) {
			ManipulatorObjectTransform = ManipOb->GetTransform();
			ManipulatorObjectTransform.SetScale3D(FVector(1.0, 1.0, 1.0));
			ModuleBaseToObjectTransform = ManipulatorObjectTransform*FullBaseTransform.Inverse();
			ModuleBaseToObjectTransform = FTransform(FVector(0, 0, ObjectExtents.Z / 2.0))*ModuleBaseToObjectTransform;
			ModuleBaseToObjectTransform = FTransform(FQuat(FVector(0, 1, 0), -M_PI_2))*ModuleBaseToObjectTransform;
		}
	}
}
/**
* @brief get kinematics action for dock face
* @param d dock face
* @return Superbot action
*/
ModuleAction ReconfDemoQ2Behavior::GetKinematicsActionForDock(ModuleDockFace d) {
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
ModuleAction ReconfDemoQ2Behavior::GetTreeActionForDock(ModuleDockFace d) {
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
std::vector<int> ReconfDemoQ2Behavior::GetPathToRootFromNode(ModuleNode* n) {
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
FTransform ReconfDemoQ2Behavior::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
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
ModuleTree ReconfDemoQ2Behavior::GetSuperBotTree() {
	return this->st;
}
/**
* @brief get the selected end effector
*/
ModuleDockFace ReconfDemoQ2Behavior::GetEndEffectorDockFace() {
	return EEDock;
}
/**
* @brief get the selected end effector
*/
int ReconfDemoQ2Behavior::GetSelectedEndEffector() {
	return SelectedEndEffector;
}
/**
* @brief get the selected end effector
*/
int ReconfDemoQ2Behavior::GetGroundModule() {
	return this->GroundModule;
}
/**
* @brief get the selected end effector
*/
ModuleDockFace ReconfDemoQ2Behavior::GetGroundDockFace() {
	return this->GDock;
}
/**
* @brief get am i end effector
* @return am I an end effector
*/
bool ReconfDemoQ2Behavior::GetAmIEndEffector() {
	return this->AmIEndEffector;
}
/**
* @brief get am i connected to ground
* @return am I connected to ground
*/
bool ReconfDemoQ2Behavior::GetAmIConnectedToGround() {
	return this->AmIEngagedToGround;
}
/**
* @brief should reinitialize program ?
* @return whether or not we need to re init program
*/
bool ReconfDemoQ2Behavior::ShouldReInit() {
	return false;
}




/**
* @brief init program
*/
void ReconfDemoQ2Behavior::Init() {
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
void ReconfDemoQ2Behavior::Tick(ModuleModel model) {
	ClearAllActions(); /** clear all the actions from the queue*/
	this->CurrentModel = model;
	UpdateCurrentAngles(); /** update current joint angles of this module */
	UpdateDockEngagedStatus(); /** update dock engaged statuses for each dock of this module */
	UpdateDockEngagedToGroundStatus(); /** update dock engaged statuses for each dock of this module */
	UpdateDockEngagedToObjectStatus(); /** update dock engaged statuses for object */
	UpdateEngagedToGround(); /** update engaged to ground */
	UpdateEndEffectorStatus(); /** update end effector status */
	UpdateConnectedToObject(); /** update connected to object */
	UpdateObjectPose(); /**< update object pose */
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
			bool CToOb = false;
			for (int i = 0; i < st.GetVertices().size(); i++) {
				if (st.GetVertices()[i]->GetAmIConnectedToObject()) {
					CToOb = true;
				}
			}
			if (!HaveFoundAnglesForReconfigure) HaveFoundAnglesForReconfigure = FindGoalAnglesForReconfigureToSnake();
			else if (!HavePlannedToReconfigureAngles) HavePlannedToReconfigureAngles = PlanPathCurrentAnglesToGoalAngles();
			else if (!HaveExecutedReconfigureAngles) HaveExecutedReconfigureAngles = ExecutePath();
			else if (!HaveWaitedReconfigure1 || !HaveWaitedReconfigure2) {
				if (!HaveWaitedReconfigure1) HaveWaitedReconfigure1 = ExecuteWait(500);
				else if (HaveWaitedReconfigure1 && !HaveReconfigured) {
					ReconfigureManipulatorTreeToSnake();
					HaveReconfigured = true;
				}
				else if (!HaveWaitedReconfigure2 && HaveReconfigured) HaveWaitedReconfigure2 = ExecuteWait(500);
			}
			else if (CurrentX < 0) {
				GEngine->AddOnScreenDebugMessage(CurrentXKey, 4.f, FColor::Yellow, FString::Printf(TEXT("Ready to walk. Current X %f"), CurrentX));
				if (!HaveWaited) HaveWaited = ExecuteWait(500);
				else if (!HavePlannedIKToGroundReturn) HavePlannedIKToGroundReturn = PlanPathCurrentAnglesTo0Angles();
				else if (!HaveExecutedIKToGroundReturn) HaveExecutedIKToGroundReturn = ExecutePath();
				else if (!HaveWaitedGround3) HaveWaitedGround3 = ExecuteWait(500);
				else if (!HaveFoundAnglesToGround) HaveFoundAnglesToGround = FindGoalAnglesWithIK();
				else if (!HavePlannedIKToGround) HavePlannedIKToGround = PlanPathCurrentAnglesToGoalAngles();
				else if (!HaveExecutedIKToGround) HaveExecutedIKToGround = ExecutePath();
				else if (!HaveWaitedGround4) HaveWaitedGround4 = ExecuteWait(500);
				else if (!HaveWaitedGround1 || !HaveWaitedGround2) {
					if (!HaveWaitedGround1) HaveWaitedGround1 = ExecuteWait(500);
					else if (HaveWaitedGround1 && !HaveConnectedToGround) {
						ConnectNewEffector();
						HaveConnectedToGround = true;
					}
				}
			}
			else if (!HaveWaitedBeforeReconfigure2) HaveWaitedBeforeReconfigure2 = ExecuteWait(500);
			else if (!HavePlannedTo0AfterRe1) HavePlannedTo0AfterRe1 = PlanPathCurrentAnglesTo0Angles();
			else if (!HaveExecutedTo0AfterRe1) HaveExecutedTo0AfterRe1 = ExecutePath();
			else if (!HaveWaitedBeforeRe2) HaveWaitedBeforeRe2 = ExecuteWait(500);
			else if (!HaveFoundAnglesForReconfigure2) HaveFoundAnglesForReconfigure2 = FindGoalAnglesForReconfigureToTree();
			else if (!HavePlannedToReconfigureAngles2) HavePlannedToReconfigureAngles2 = PlanPathCurrentAnglesToGoalAngles();
			else if (!HaveExecutedReconfigureAngles2) HaveExecutedReconfigureAngles2 = ExecutePath();
			else if (!HaveWaitedReconfigure12 || !HaveWaitedReconfigure22) {
				if (!HaveWaitedReconfigure12) HaveWaitedReconfigure12 = ExecuteWait(500);
				else if (HaveWaitedReconfigure12 && !HaveReconfigured2) {
					ReconfigureManipulatorSnakeToTree();
					HaveReconfigured2 = true;
				}
				else if (!HaveWaitedReconfigure22) {
					HaveWaitedReconfigure22 = ExecuteWait(500);
					GEngine->AddOnScreenDebugMessage(CurrentXKey, 5.f, FColor::Yellow, FString("Final Wait."));
				}
			}
			else if (!FinalPlanTo0) {
				GEngine->AddOnScreenDebugMessage(CurrentXKey, 5.f, FColor::Yellow, FString("Final Plan to 0."));
				FinalPlanTo0 = PlanPathCurrentAnglesTo0Angles();
			}
			else if (!FinalExecuteTo0) FinalExecuteTo0 = ExecutePath();
			else if (!FinalPostGrabWait) FinalPostGrabWait = ExecuteWait(500);
			else if (!FinalGrabFindAngles) FinalGrabFindAngles = FindGoalAnglesForObject();
			else if (!FinalGrabPlan) FinalGrabPlan = PlanPathCurrentAnglesToGoalAngles();
			else if (!FinalGrabExecute) FinalGrabExecute = ExecutePath();
			else if (!FinalPostGrabWait1 || !FinalPostGrabWait2) {
				if (!FinalPostGrabWait1) FinalPostGrabWait1 = ExecuteWait(500);
				else if (FinalPostGrabWait1 && !FinalHavePicked) {
					ConnectObject();
					FinalHavePicked = true;
				}
				else if (!FinalPostGrabWait2 && FinalHavePicked) FinalPostGrabWait2 = ExecuteWait(500);

			}
			else if (!FinalPostGrabPlanTo0) FinalPostGrabPlanTo0 = PlanPathCurrentAnglesTo0Angles();
			else if (!FinalPostGrabExecute) FinalPostGrabExecute = ExecutePath();
		}

	}
	this->ProgramCounter++;
}
