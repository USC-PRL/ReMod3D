 
#include "SuperBotModule.h"
/**
 * @brief constructor
 */
ASuperBotModule::ASuperBotModule(){InitModule();}
/**
 * @brief superbot dock setter
 * @param sd superbot dock
 */
void ASuperBotModule::SetDocks(std::vector<ModuleDock> sd) {this->Docks = sd;}
/**
 * @brief get superbot docks
 * @return superbot dock vector
 */
std::vector<ModuleDock> ASuperBotModule::GetDocks() {return this->Docks;}
/**
* @brief get number of connectors
* @return number of connectors in module
*/
int ASuperBotModule::GetNumConnectors() {
	return this->NumConnectors;
}
/**
 * @brief superbot dock setter
 * @param sd superbot dock
 */
void ASuperBotModule::SetLinks(std::vector<UStaticMeshComponent*> sl) {this->Links = sl;}
/**
 * @brief get superbot docks
 * @return superbot dock vector
 */
std::vector<UStaticMeshComponent*> ASuperBotModule::GetLinks() {return this->Links;}
/**
 * @brief superbot dock setter
 * @param sd superbot dock
 */
void ASuperBotModule::SetJoints(std::vector<UPhysicsConstraintComponent*> sj) {this->Joints = sj;}
/**
 * @brief get superbot docks
 * @return superbot dock vector
 */
std::vector<UPhysicsConstraintComponent*> ASuperBotModule::GetJoints() {return this->Joints;}
/**
 * @brief get dock for name
 * @param name string name
 * @return superbot dock
 */
ModuleDockFace ASuperBotModule::GetDockFaceForName(std::string dname) {
    if (dname.compare("FrontDock") == 0) {
        return DOCK_0;
    } else if (dname.compare("BackDock") == 0) {
        return DOCK_1;
    } else if (dname.compare("LeftDock") == 0) {
        return DOCK_2;
    } else if (dname.compare("RightDock") == 0) {
        return DOCK_3;
    } else if (dname.compare("UpDock") == 0) {
        return DOCK_4;
    } else if (dname.compare("DownDock") == 0) {
        return DOCK_5;
    } else {
        return DOCK_6;
    }
}
/**
 * @brief set dock engaged status
 * @param d dock face
 * @param e engaged status
 */
void ASuperBotModule::SetDockEngaged(ModuleDockFace d, bool e) {Docks[d].SetDockEngaged(e);}
/**
 * @brief set dock enabled status
 * @param d dock face
 * @param e enabled status
 */
void ASuperBotModule::SetDockEnabled(ModuleDockFace d, bool e) {Docks[d].SetDockEnabled(e);}
/**
 * @brief send message on dock face
 * @param d dock face
 * @param m message
 */
void ASuperBotModule::SendMessageOnDockFace(ModuleDockFace d, std::string m) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		if (mode) mode->sendMessageToDock(this, Docks[d], m);
	}
}
/**
 * @brief send kinematics message on dock face
 * @param d dock face
 * @param m kinematics messages
 */
void ASuperBotModule::SendKinematicsMessageOnDockFace(ModuleDockFace d, KinematicsMessage m) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		if (mode) mode->sendKinematicsMessageToDock(this, Docks[d], m);
	}
}
/**
 * @brief get all messages
 */
vector<Message> ASuperBotModule::GetMessages() {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		if (!mode) return vector<Message>();
		return mode->getMessages(this->IDNumber);
	}
	return vector<Message>();
}
/**
 * @brief get all kinematics messages
 */
vector<KinematicsMessage> ASuperBotModule::GetKinematicsMessages() {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		if (!mode) return vector<KinematicsMessage>();
		return mode->getKinematicsMessages(this->IDNumber);
	}
	return vector<KinematicsMessage>();
}
/**
 * @brief get dock enabled status
 * @param d dock face
 */
bool ASuperBotModule::GetDockEnabledStatus(ModuleDockFace d) {return Docks[d].GetDockEnabled();}
/**
 * @brief get dock enabled status
 * @return dock faces
 */
vector<bool> ASuperBotModule::GetDockEnabledStatuses() {
    vector<bool> ds(6);
    for (int i=0; i<6; i++) {
        ds[i] = Docks[i].GetDockEnabled();
    }
    return ds;
}
/**
 * @brief get dock engaged status
 * @return dock engaged status
 */
bool ASuperBotModule::GetDockEngagedStatus(ModuleDockFace d) {return Docks[d].GetDockEngaged();}
/**
 * @brief get dock enabled status
 * @return dock faces
 */
vector<bool> ASuperBotModule::GetDockEngagedStatuses() {
    vector<bool> ds(6);
    for (int i=0; i<6; i++) {
        ds[i] = Docks[i].GetDockEngaged();
    }
    return ds;
}
/**
 * @brief get dock enabled to ground statuses
 */
vector<bool> ASuperBotModule::GetDockEnabledToGroundStatuses() {
    vector<bool> ds(6);
    for (int i=0; i<6;i++) {
        ds[i] = Docks[i].GetDockEnabledToGround();
    }
    return ds;
}
/**
 * @brief get dock engaged to ground statuses
 */
vector<bool> ASuperBotModule::GetDockEngagedToGroundStatuses() {
    vector<bool> ds(6);
    for (int i=0; i<6;i++) {
        ds[i] = Docks[i].GetDockEngagedToGround();
    }
    return ds;
}
/**
 * @brief get dock enabled to ground status
 * @param dock face d
 * @return get dock enabled to ground
 */
bool ASuperBotModule::GetDockEnabledToGround(ModuleDockFace d) {return Docks[d].GetDockEnabledToGround();}
/**
 * @brief get dock engaged to ground status
 * @param dock face d
 * @return get dock engaged to ground
 */
bool ASuperBotModule::GetDockEngagedToGround(ModuleDockFace d) {return Docks[d].GetDockEngagedToGround();}
/**
 * @brief set dock enabled to ground status
 * @param dock face d
 * @param de dock enabled
 */
void ASuperBotModule::SetDockEnabledToGround(ModuleDockFace d, bool de) {Docks[d].SetDockEnabledToGround(de);}
/**
 * @brief set dock engaged to ground status
 * @param dock face d
 * @param de dock engaged
 */
void ASuperBotModule::SetDockEngagedToGround(ModuleDockFace d, bool de) {
    Docks[d].SetDockEngagedToGround(de);
    if (GroundDockConstraints[d] && !de) {
       //GroundDockConstraints[d]->Destroy();
    } else if (GroundDockConstraints[d] && !de) {
        //AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
        //mode->DockModuleToGround(this, d);
    }

}

/**
* @brief set module color
* @param c color to set
*/
void ASuperBotModule::SetModuleColor(SuperBotColor C) {
	MasterInner->SetMaterial(0, BlueMaterial);
	SlaveInner->SetMaterial(0, BlueMaterial);
	MasterOuter->SetMaterial(0, BlueMaterial);
	SlaveOuter->SetMaterial(0, BlueMaterial);
	FrontDock->SetMaterial(0, BlueMaterial);
	BackDock->SetMaterial(0, BlueMaterial);
	LeftDock->SetMaterial(0, BlueMaterial);
	RightDock->SetMaterial(0, BlueMaterial);
	UpDock->SetMaterial(0, BlueMaterial);
	DownDock->SetMaterial(0, BlueMaterial);
}

/**
 * @brief set id number
 * @param Id number
 */
void ASuperBotModule::SetIDNumber(int ID) {this->IDNumber = ID;}
/**
 * @brief get id number
 * @return Id number
 */
int ASuperBotModule::GetIDNumber() {return this->IDNumber;}
/**
 * @brief send ranged message
 * @param m message
 */
void ASuperBotModule::SendRangedMessage(std::string m) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		mode->sendRangedMessage(this, 1000.0, m);
	}
}
/**
 * @brief get all ranged messages
 */
vector<RangedMessage> ASuperBotModule::GetRangedMessages() {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		return mode->getRangedMessages(this->IDNumber);
	}
	return vector<RangedMessage>();
}
/**
 * @brief get all tree messages
 */
vector<TreeMessage> ASuperBotModule::GetTreeMessages() {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		return mode->getTreeMessages(this->IDNumber);
	}
	return vector<TreeMessage>();
}
/**
 * @brief send tree message on dock face
 * @param d dock face
 * @param m tree messages
 */
void ASuperBotModule::SendTreeMessageOnDockFace(ModuleDockFace d, TreeMessage m) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		mode->sendTreeMessageToDock(this, Docks[d], m);
	}
}
/**
 * @brief initialize module
 */
void ASuperBotModule::InitModule() {
	PrimaryActorTick.bCanEverTick = true;
	this->Type = SUPERBOT;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> innerMesh(TEXT("/Game/SuperBotMeshes/InnerCube.InnerCube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		pipeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		cubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	CubeMesh = cubeMesh.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		outerMesh(TEXT("/Game/SuperBotMeshes/SuperBotOutside.SuperBotOutside"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		SMaterial(TEXT("/Game/SuperBotMaterials/SlaveMaterial.SlaveMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		MMaterial(TEXT("/Game/SuperBotMaterials/MasterMaterial.MasterMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		OMaterial(TEXT("/Game/SuperBotMaterials/OuterMaterial.OuterMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		RMaterial(TEXT("/Game/SuperBotMaterials/RedMaterial.RedMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		BMaterial(TEXT("/Game/SuperBotMaterials/BlueMaterial.BlueMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		GMaterial(TEXT("/Game/SuperBotMaterials/GreenMaterial.GreenMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial>
		BTMaterial(TEXT("/Game/SuperBotMaterials/BlueTrans.BlueTrans"));

	BlueMaterial = NULL;
	if (BMaterial.Object != NULL) { BlueMaterial = (UMaterial*)BMaterial.Object; }
	UMaterial* GreenMaterial = NULL;
	if (GMaterial.Object != NULL) { GreenMaterial = (UMaterial*)GMaterial.Object; }
	UMaterial* RedMaterial = NULL;
	if (RMaterial.Object != NULL) { RedMaterial = (UMaterial*)RMaterial.Object; }
	UMaterial* SlaveMaterial = NULL;
	if (SMaterial.Object != NULL) { SlaveMaterial = (UMaterial*)SMaterial.Object; }
	UMaterial* MasterMaterial = NULL;
	if (MMaterial.Object != NULL) { MasterMaterial = (UMaterial*)MMaterial.Object; }
	UMaterial* OuterMaterial = NULL;
	if (OMaterial.Object != NULL) { OuterMaterial = (UMaterial*)OMaterial.Object; }
	BlueTransMaterial = NULL;
	if (BTMaterial.Object != NULL) { BlueTransMaterial = (UMaterial*)BTMaterial.Object; }

	cout << "Behavior: " << BehaviorType.GetValue() << endl;

	std::string rootString = "SharedRoot";
	std::string masterInnerString = "InnerMesh0";
	std::string slaveInnerString = "InnerMesh1";
	std::string masterOuterString = "OuterMesh0";
	std::string slaveOuterString = "OuterMesh1";
	std::string innerJointString = "InnerJoint";
	std::string masterJointString = "MasterJoint";
	std::string slaveJointString = "SlaveJoint";
	std::string frontDockString = "FrontDock";
	std::string backDockString = "BackDock";

	MasterInner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InnerMesh0"));
	SlaveInner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InnerMesh1"));
	MasterOuter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OuterMesh0"));
	SlaveOuter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OuterMesh1"));
	InnerJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("InnerJoint"));
	MasterJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("MasterJoint"));
	SlaveJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("SlaveJoint"));
	FrontDock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontDock"));
	BackDock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackDock"));
	LeftDock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDock"));
	RightDock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDock"));
	UpDock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpDock"));
	DownDock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DownDock"));
	RootComponent = InnerJoint;
	RootComponent->SetActive(true);
	RootComponent->SetRelativeRotation(FRotator(-90, 0, 90));
	RootComponent->SetMobility(EComponentMobility::Movable);
	MasterInner->SetStaticMesh(innerMesh.Object);
	MasterOuter->SetStaticMesh(outerMesh.Object);
	SlaveInner->SetStaticMesh(innerMesh.Object);
	SlaveOuter->SetStaticMesh(outerMesh.Object);
	FrontDock->SetStaticMesh(cubeMesh.Object);
	BackDock->SetStaticMesh(cubeMesh.Object);
	LeftDock->SetStaticMesh(cubeMesh.Object);
	RightDock->SetStaticMesh(cubeMesh.Object);
	UpDock->SetStaticMesh(cubeMesh.Object);
	DownDock->SetStaticMesh(cubeMesh.Object);

	FrontDock->SetWorldScale3D(FVector(0.12, 0.34, 0.34));
	BackDock->SetWorldScale3D(FVector(0.12, 0.34, 0.34));
	LeftDock->SetWorldScale3D(FVector(0.12, 0.34, 0.34));
	RightDock->SetWorldScale3D(FVector(0.12, 0.34, 0.34));
	UpDock->SetWorldScale3D(FVector(0.12, 0.34, 0.34));
	DownDock->SetWorldScale3D(FVector(0.12, 0.34, 0.34));

	MasterInner->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	MasterOuter->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	SlaveInner->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	SlaveOuter->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	FrontDock->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	BackDock->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	LeftDock->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RightDock->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	UpDock->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	DownDock->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);


	MasterInner->SetMaterial(0, GreenMaterial);
	SlaveInner->SetMaterial(0, RedMaterial);
	MasterOuter->SetMaterial(0, OuterMaterial);
	SlaveOuter->SetMaterial(0, OuterMaterial);
	FrontDock->SetMaterial(0, OuterMaterial);
	BackDock->SetMaterial(0, OuterMaterial);
	LeftDock->SetMaterial(0, OuterMaterial);
	RightDock->SetMaterial(0, OuterMaterial);
	UpDock->SetMaterial(0, OuterMaterial);
	DownDock->SetMaterial(0, OuterMaterial);

	MasterInner->SetSimulatePhysics(true);
	MasterOuter->SetSimulatePhysics(true);
	SlaveInner->SetSimulatePhysics(true);
	SlaveOuter->SetSimulatePhysics(true);
	FrontDock->SetSimulatePhysics(true);
	BackDock->SetSimulatePhysics(true);
	LeftDock->SetSimulatePhysics(true);
	RightDock->SetSimulatePhysics(true);
	UpDock->SetSimulatePhysics(true);
	DownDock->SetSimulatePhysics(true);

	MasterInner->BodyInstance.bEnableGravity = true;
	MasterOuter->BodyInstance.bEnableGravity = true;
	SlaveInner->BodyInstance.bEnableGravity = true;
	SlaveOuter->BodyInstance.bEnableGravity = true;
	FrontDock->BodyInstance.bEnableGravity = true;
	BackDock->BodyInstance.bEnableGravity = true;
	LeftDock->BodyInstance.bEnableGravity = true;
	RightDock->BodyInstance.bEnableGravity = true;
	UpDock->BodyInstance.bEnableGravity = true;
	DownDock->BodyInstance.bEnableGravity = true;

	SlaveInner->BodyInstance.MaxAngularVelocity = 400.0f;
	MasterInner->BodyInstance.MaxAngularVelocity = 400.0f;
	SlaveOuter->BodyInstance.MaxAngularVelocity = 400.0f;
	MasterOuter->BodyInstance.MaxAngularVelocity = 400.0f;
	FrontDock->BodyInstance.MaxAngularVelocity = 400.0f;
	BackDock->BodyInstance.MaxAngularVelocity = 400.0f;
	LeftDock->BodyInstance.MaxAngularVelocity = 400.0f;
	RightDock->BodyInstance.MaxAngularVelocity = 400.0f;
	UpDock->BodyInstance.MaxAngularVelocity = 400.0f;
	DownDock->BodyInstance.MaxAngularVelocity = 400.0f;

	MasterOuter->AttachTo(InnerJoint);
	SlaveOuter->AttachTo(InnerJoint);
	MasterInner->AttachTo(InnerJoint);
	SlaveInner->AttachTo(InnerJoint);
	MasterJoint->AttachTo(MasterInner);
	SlaveJoint->AttachTo(SlaveInner);
	FrontDock->AttachTo(MasterOuter);
	BackDock->AttachTo(SlaveOuter);
	LeftDock->AttachTo(MasterOuter);
	RightDock->AttachTo(MasterOuter);
	UpDock->AttachTo(SlaveOuter);
	DownDock->AttachTo(SlaveOuter);

	MasterJoint->SetRelativeLocation(FVector(36.0 + 7.0 - 26.5, 0, 0));
	MasterJoint->SetRelativeRotation(FRotator(0, 0, 0));
	SlaveJoint->SetRelativeRotation(FRotator(0.0, 0.0, 0.0));
	SlaveJoint->SetRelativeLocation(FVector(36 + 7 - 26.5, 0, 0));
	InnerJoint->SetRelativeLocation(FVector(0, 0, 0.0));
	InnerJoint->SetRelativeRotation(FRotator(90, 0, 0.0));
	MasterInner->SetRelativeRotation(FRotator(0, 0, 90));
	MasterOuter->SetRelativeRotation(FRotator(0, 90, 90));
	SlaveOuter->SetRelativeLocation(FVector(-36 - 7, 0, 0));
	SlaveOuter->SetRelativeRotation(FRotator(0, 90, -90));
	MasterOuter->SetRelativeLocation(FVector(36.0 + 7.0, 0, 0));
	MasterInner->SetRelativeLocation(FVector(26.5, 0, 0));
	SlaveInner->SetRelativeRotation(FRotator(0, 180, 90));
	SlaveInner->SetRelativeLocation(FVector(-26.5, 0, 0));
	FrontDock->SetRelativeRotation(FRotator(90, 0, 0));
	FrontDock->SetRelativeLocation(FVector(17, 0, -34.0 - 12));
	BackDock->SetRelativeRotation(FRotator(90, 0, 0));
	BackDock->SetRelativeLocation(FVector(17, 0, -34.0 - 12));
	LeftDock->SetRelativeRotation(FRotator(0, 0, 0));
	LeftDock->SetRelativeLocation(FVector(-40 - 6, 0, -34.0 - 6 + 8));
	RightDock->SetRelativeRotation(FRotator(0, 0, 0));
	RightDock->SetRelativeLocation(FVector(40 + 6, 0, -34.0 - 6 + 8));
	UpDock->SetRelativeRotation(FRotator(0, 0, 0));
	UpDock->SetRelativeLocation(FVector(-40 - 6, 0, -34.0 - 6 + 8));
	DownDock->SetRelativeRotation(FRotator(0, 0, 0));
	DownDock->SetRelativeLocation(FVector(40 + 6, 0, -34.0 - 6 + 8));


	InnerJoint->SetConstrainedComponents(MasterInner, FName("InnerMesh0"), SlaveInner, FName("InnerMesh1"));
	SlaveJoint->SetConstrainedComponents(SlaveInner, FName("InnerMesh1"), SlaveOuter, FName("OuterMesh1"));
	MasterJoint->SetConstrainedComponents(MasterInner, FName("InnerMesh0"), MasterOuter, FName("OuterMesh0"));

	InnerJoint->SetDisableCollision(true);
	MasterJoint->SetDisableCollision(true);
	SlaveJoint->SetDisableCollision(true);
	InnerJoint->bAutoActivate = true;
	MasterJoint->bAutoActivate = true;
	SlaveJoint->bAutoActivate = true;


    InnerJoint->SetAngularOrientationDrive(false, true);
    InnerJoint->SetAngularVelocityDrive(false, true);
    InnerJoint->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	InnerJoint->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	InnerJoint->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	InnerJoint->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	InnerJoint->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0);
	InnerJoint->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	InnerJoint->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
    InnerJoint->SetAngularDriveParams(200000.0, 10000.0, 0.0);

	//InnerJoint->ConstraintInstance.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	//InnerJoint->ConstraintInstance.ProjectionAngularTolerance = 0.0001;
	//InnerJoint->ConstraintInstance.ProjectionLinearTolerance = 0.0001;

    MasterJoint->SetAngularOrientationDrive(true, false);
    MasterJoint->SetAngularVelocityDrive(true, false);
    MasterJoint->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	//MasterJoint->ConstraintInstance.ProjectionAngularTolerance = 0.0001;
	//MasterJoint->ConstraintInstance.ProjectionLinearTolerance = 0.0001;
	MasterJoint->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MasterJoint->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MasterJoint->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MasterJoint->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	MasterJoint->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Free, 0);
	MasterJoint->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
    MasterJoint->SetAngularDriveParams(200000.0, 10000.0, 0.0);

    
    SlaveJoint->SetAngularOrientationDrive(true, false);
    SlaveJoint->SetAngularVelocityDrive(true, false);
    SlaveJoint->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	SlaveJoint->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	SlaveJoint->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	SlaveJoint->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	SlaveJoint->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	SlaveJoint->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Free, 0);
	SlaveJoint->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
    SlaveJoint->SetAngularDriveParams(200000.0, 10000.0, 0.0);
	InnerJoint->SetAngularOrientationTarget(FRotator(0, 0, 0));
	MasterJoint->SetAngularOrientationTarget(FRotator(0, 0, 0));
	SlaveJoint->SetAngularOrientationTarget(FRotator(0, 0, 0));

	SlaveInner->BodyInstance.PositionSolverIterationCount = 255;
	SlaveInner->BodyInstance.VelocitySolverIterationCount = 255;
	MasterInner->BodyInstance.PositionSolverIterationCount = 255;
	MasterInner->BodyInstance.VelocitySolverIterationCount = 255;
	SlaveOuter->BodyInstance.PositionSolverIterationCount = 255;
	SlaveOuter->BodyInstance.VelocitySolverIterationCount = 255;
	MasterOuter->BodyInstance.PositionSolverIterationCount = 255;
	MasterOuter->BodyInstance.VelocitySolverIterationCount = 255;
	FrontDock->BodyInstance.PositionSolverIterationCount = 255;
	FrontDock->BodyInstance.VelocitySolverIterationCount = 255;
	BackDock->BodyInstance.PositionSolverIterationCount = 255;
	BackDock->BodyInstance.VelocitySolverIterationCount = 255;
	LeftDock->BodyInstance.PositionSolverIterationCount = 255;
	LeftDock->BodyInstance.VelocitySolverIterationCount = 255;
	RightDock->BodyInstance.PositionSolverIterationCount = 255;
	RightDock->BodyInstance.VelocitySolverIterationCount = 255;
	UpDock->BodyInstance.PositionSolverIterationCount = 255;
	UpDock->BodyInstance.VelocitySolverIterationCount = 255;
	DownDock->BodyInstance.PositionSolverIterationCount = 255;
	DownDock->BodyInstance.VelocitySolverIterationCount = 255;

	SlaveInner->BodyInstance.bOverrideMass = true;
	SlaveInner->BodyInstance.SetMassOverride(0.233 / 2.0);
	MasterInner->BodyInstance.bOverrideMass = true;
	MasterInner->BodyInstance.SetMassOverride(0.233 / 2.0);
	SlaveOuter->BodyInstance.bOverrideMass = true;
	SlaveOuter->BodyInstance.SetMassOverride(0.126 / 2.0);
	MasterOuter->BodyInstance.bOverrideMass = true;
	MasterOuter->BodyInstance.SetMassOverride(0.126 / 2.0);
	FrontDock->BodyInstance.bOverrideMass = true;
	FrontDock->BodyInstance.SetMassOverride(0.25 / 2.0);
	BackDock->BodyInstance.bOverrideMass = true;
	BackDock->BodyInstance.SetMassOverride(0.25 / 2.0);
	LeftDock->BodyInstance.bOverrideMass = true;
	LeftDock->BodyInstance.SetMassOverride(0.25 / 2.0);
	RightDock->BodyInstance.bOverrideMass = true;
	RightDock->BodyInstance.SetMassOverride(0.25 / 2.0);
	UpDock->BodyInstance.bOverrideMass = true;
	UpDock->BodyInstance.SetMassOverride(0.25 / 2.0);
	DownDock->BodyInstance.bOverrideMass = true;
	DownDock->BodyInstance.SetMassOverride(0.25 / 2.0);
	MasterInner->SetMobility(EComponentMobility::Movable);
	MasterOuter->SetMobility(EComponentMobility::Movable);
	SlaveInner->SetMobility(EComponentMobility::Movable);
	SlaveOuter->SetMobility(EComponentMobility::Movable);
	FrontDock->SetMobility(EComponentMobility::Movable);
	BackDock->SetMobility(EComponentMobility::Movable);
	LeftDock->SetMobility(EComponentMobility::Movable);
	LeftDock->SetMobility(EComponentMobility::Movable);
	RightDock->SetMobility(EComponentMobility::Movable);
	RightDock->SetMobility(EComponentMobility::Movable);
	curJoints.Motor0Angle = 0;
	curJoints.Motor1Angle = 0;
	curJoints.Motor2Angle = 0;
	SetJointAngles(ModuleMotorVector(0, 0, 0));
	std::stringstream ss;
	ss << "SuperBot";
	ss << numSuperBotMods;
	this->name = ss.str();
	numSuperBotMods++;
	this->Links.push_back(MasterOuter);
	this->Links.push_back(MasterInner);
	this->Links.push_back(SlaveInner);
	this->Links.push_back(SlaveOuter);
	this->Joints.push_back(MasterJoint);
	this->Joints.push_back(InnerJoint);
	this->Joints.push_back(SlaveJoint);
	ModuleDock FDock = ModuleDock(DOCK_0, MasterOuter, this);
	ModuleDock BDock = ModuleDock(DOCK_1, SlaveOuter, this);
	ModuleDock LDock = ModuleDock(DOCK_2, MasterOuter, this);
	ModuleDock RDock = ModuleDock(DOCK_3, MasterOuter, this);
	ModuleDock UDock = ModuleDock(DOCK_4, SlaveOuter, this);
	ModuleDock DDock = ModuleDock(DOCK_5, SlaveOuter, this);
	this->Docks.push_back(FDock);
	this->Docks.push_back(BDock);
	this->Docks.push_back(LDock);
	this->Docks.push_back(RDock);
	this->Docks.push_back(UDock);
	this->Docks.push_back(DDock);
	this->GroundDockConstraints = std::vector<APhysicsConstraintActor*>(this->Docks.size());
	this->ObjectDockConstraints = std::vector<APhysicsConstraintActor*>(this->Docks.size());
	for (int i = 0; i < this->GroundDockConstraints.size(); i++) {
		GroundDockConstraints[i] = NULL;
		ObjectDockConstraints[i] = NULL;
	}
	this->Actuators[JOINT_0] = (ModuleActuator*)(new Joint0Actuator());
	this->Actuators[JOINT_1] = (ModuleActuator*)(new  Joint1Actuator());
	this->Actuators[JOINT_2] = (ModuleActuator*)(new Joint2Actuator());
	this->Actuators[DOCKS_ENABLED] = (ModuleActuator*)(new DockEnabledActuator());
	this->Actuators[DOCKS_ENGAGED] = (ModuleActuator*)(new DockEngagedActuator());
	this->Actuators[DOCKS_ENGAGED_TO_GROUND] = (ModuleActuator*)(new DockEngagedToGroundActuator());
	this->Actuators[DOCKS_ENGAGED_TO_OBJECT] = (ModuleActuator*)(new DockEngagedToObjectActuator());
	this->Actuators[MESSAGE] = (ModuleActuator*)(new ModuleMessageActuator());
	this->Sensors[JOINT_0] = (ModuleSensor*)(new Joint0Sensor());
	this->Sensors[JOINT_1] = (ModuleSensor*)(new Joint1Sensor());
	this->Sensors[JOINT_2] = (ModuleSensor*)(new Joint2Sensor());
	this->Sensors[POSITION_ORIENTATION] = (ModuleSensor*)(new PoseSensor());
	this->Sensors[DOCKS_ENABLED] = (ModuleSensor*)(new DockEnabledSensor());
	this->Sensors[DOCKS_ENGAGED] = (ModuleSensor*)(new DockEngagedSensor());
	this->Sensors[DOCKS_ENGAGED_TO_GROUND] = (ModuleSensor*)(new DockEngagedToGroundSensor());
	this->Sensors[DOCKS_ENGAGED_TO_OBJECT] = (ModuleSensor*)(new DockEngagedToObjectSensor());
	ModuleLink Mouter(this->GetName(), "MasterOuter", MasterOuter);
	ModuleLink Minner(this->GetName(), "MasterInner", MasterInner);
	ModuleLink Sinner(this->GetName(), "SlaveInner", SlaveInner);
	ModuleLink Souter(this->GetName(), "SlaveOuter", SlaveOuter);
	this->Connectors[DOCK_0] = ModuleConnector(Mouter, DOCK_0, "DOCK_0");
	this->Connectors[DOCK_1] = ModuleConnector(Souter, DOCK_1, "DOCK_1");
	this->Connectors[DOCK_2] = ModuleConnector(Mouter, DOCK_2, "DOCK_2");
	this->Connectors[DOCK_3] = ModuleConnector(Mouter, DOCK_3, "DOCK_3");
	this->Connectors[DOCK_4] = ModuleConnector(Souter, DOCK_4, "DOCK_4");
	this->Connectors[DOCK_5] = ModuleConnector(Souter, DOCK_5, "DOCK_5");
	this->ModuleLinks[M_OUTER] = Mouter;
	this->ModuleLinks[M_INNER] = Minner;
	this->ModuleLinks[S_INNER] = Sinner;
	this->ModuleLinks[S_OUTER] = Souter;
}
/**
 * @brief add impulse to module
 * @param vec
 */
void ASuperBotModule::AddImpulseToModule(FVector vec) {
    MasterInner->AddImpulse(vec);
    SlaveInner->AddImpulse(vec);
    MasterOuter->AddImpulse(vec);
    SlaveOuter->AddImpulse(vec);
}
/**
 * @brief add impulse to module
 * @param vec
 */
void ASuperBotModule::AddAngularImpulseToModule(FVector vec) {
    MasterInner->AddAngularImpulse(vec);
    SlaveInner->AddAngularImpulse(vec);
    MasterOuter->AddAngularImpulse(vec);
    SlaveOuter->AddAngularImpulse(vec);
}
/**
 * @brief attach dock to component
 * @param sc scene component
 */
void ASuperBotModule::AttachDockToComponent(ModuleDockFace d, USceneComponent *sc) {
    Docks[d].GetDockComponent()->AttachTo(sc,"",EAttachLocation::SnapToTarget,true);
}
/**
 * @brief get dock component
 * @param d dock face
 */
UStaticMeshComponent* ASuperBotModule::GetDockComponent(ModuleDockFace d) {
return Docks[d].GetDockComponent();
}
/**
 * @brief set transform
 * @param trans
 */
void ASuperBotModule::SetTransform(FTransform trans) {
	RootComponent->SetWorldTransform(trans);
}
/**
 * @brief begin play of game (simulation)
 */
void ASuperBotModule::BeginPlay()
{
	Super::BeginPlay();
	MasterOuter->AttachToComponent(InnerJoint, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	SlaveOuter->AttachToComponent(InnerJoint, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	MasterInner->AttachToComponent(InnerJoint, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	SlaveInner->AttachToComponent(InnerJoint, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	MasterJoint->AttachToComponent(MasterInner, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	SlaveJoint->AttachToComponent(SlaveInner, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	FrontDock->AttachToComponent(MasterOuter, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	BackDock->AttachToComponent(SlaveOuter, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	LeftDock->AttachToComponent(MasterOuter, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	RightDock->AttachToComponent(MasterOuter, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	UpDock->AttachToComponent(SlaveOuter, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	DownDock->AttachToComponent(SlaveOuter, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
}
/**
 * @brief perform current actions
 */
void ASuperBotModule::PerformActions() {
	vector<std::pair<ModuleAction, float> > aActions = ModuleBehavior->GetAngleActions();
	vector<std::pair<ModuleAction, bool> > dActions = ModuleBehavior->GetDockActions();
	vector<std::pair<ModuleAction, int> > delayActions = ModuleBehavior->GetDelayActions();
	vector<std::pair<ModuleAction, std::string> > mActions = ModuleBehavior->GetMessageActions();
	vector<std::pair<ModuleAction, KinematicsMessage> > kActions = ModuleBehavior->GetKinematicsMessageActions();
	vector<std::pair<ModuleAction, TreeMessage> > tActions = ModuleBehavior->GetTreeMessageActions();
	vector<std::pair<ModuleAction, float> > gActions = ModuleBehavior->GetGainChangeActions();
	vector<std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> > > cActions = ModuleBehavior->GetConnectionActions();
	for (int i = 0; i < delayActions.size(); i++) {
		std::pair<ModuleAction, int> delayAction = delayActions[i];
		if (delayAction.first == DELAY_ACTION) {
			AngleWaitCounter += delayAction.second;
		}
	}
	for (int i = 0; i < cActions.size(); i++) {
		std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> > cAction  = cActions[i];
		ModuleConnectionPair cp = cAction.second.first;
		bool engaging = cAction.second.second;
		if (cAction.first == CONNECT_MODULES) {
			if (engaging) {
				if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
					AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
					mode->DockTwoModules(cp.GetSM1(), cp.GetSM2(), cp.GetD1(), cp.GetD2());
				}
			} else {
				if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
					AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
					mode->UnDockTwoModules(cp.GetSM1(), cp.GetSM2(), cp.GetD1(), cp.GetD2());
				}
			}
		}
	}
	for (int i = 0; i < gActions.size(); i++) {
		std::pair<ModuleAction, float> gAction = gActions[i];
		if (gAction.first == CHANGE_P_GAIN_MOTOR_0) {
			//MasterJoint->SetAngularDriveParams(gAction.second, MasterJoint->ConstraintInstance.AngularDriveDamping, 800000000.0);
		}
		else if (gAction.first == CHANGE_P_GAIN_MOTOR_1) {
			//InnerJoint->SetAngularDriveParams(gAction.second, InnerJoint->ConstraintInstance.AngularDriveDamping, 800000000.0);
		}
		else if (gAction.first == CHANGE_P_GAIN_MOTOR_2) {
			///SlaveJoint->SetAngularDriveParams(gAction.second, SlaveJoint->ConstraintInstance.AngularDriveDamping, 800000000.0);
		}
		else if (gAction.first == CHANGE_D_GAIN_MOTOR_0) {
			///MasterJoint->SetAngularDriveParams(MasterJoint->ConstraintInstance.AngularDriveSpring, gAction.second, 800000000.0);
		}
		else if (gAction.first == CHANGE_D_GAIN_MOTOR_1) {
			///InnerJoint->SetAngularDriveParams(InnerJoint->ConstraintInstance.AngularDriveSpring, gAction.second, 800000000.0);
		}
		else if (gAction.first == CHANGE_D_GAIN_MOTOR_2) {
			///SlaveJoint->SetAngularDriveParams(SlaveJoint->ConstraintInstance.AngularDriveSpring, gAction.second, 800000000.0);
		}
	}
	for (int i = 0; i < aActions.size(); i++) {
		std::pair<ModuleAction, float> aAction = aActions[i];
		if (aAction.first == SET_MOTOR_0) {
			SetJointAngles(ModuleMotorVector(aAction.second, desJoints.Motor1Angle, desJoints.Motor2Angle));
		}
		else if (aAction.first == SET_MOTOR_1) {
			SetJointAngles(ModuleMotorVector(desJoints.Motor0Angle, aAction.second, desJoints.Motor2Angle));
		}
		else if (aAction.first == SET_MOTOR_2) {
			SetJointAngles(ModuleMotorVector(desJoints.Motor0Angle, desJoints.Motor1Angle, aAction.second));
		}
	}
	for (int i = 0; i < dActions.size(); i++) {
		std::pair<ModuleAction, bool> dAction = dActions[i];
		if (dAction.first == SET_FRONT_DOCK_ENABLED) {
			SetDockEnabled(DOCK_0, dAction.second);
		} else if (dAction.first == SET_BACK_DOCK_ENABLED) {
			SetDockEnabled(DOCK_1, dAction.second);
		} else if (dAction.first == SET_LEFT_DOCK_ENABLED) {
			SetDockEnabled(DOCK_2, dAction.second);
		} else if (dAction.first == SET_RIGHT_DOCK_ENABLED) {
			SetDockEnabled(DOCK_3, dAction.second);
		} else if (dAction.first == SET_UP_DOCK_ENABLED) {
			SetDockEnabled(DOCK_4, dAction.second);
		} else if (dAction.first == SET_DOWN_DOCK_ENABLED) {
			SetDockEnabled(DOCK_5, dAction.second);
		} else if (dAction.first == SET_FRONT_DOCK_ENGAGED) {
			SetDockEngaged(DOCK_0, dAction.second);
		} else if (dAction.first == SET_BACK_DOCK_ENGAGED) {
			SetDockEngaged(DOCK_1, dAction.second);
		} else if (dAction.first == SET_LEFT_DOCK_ENGAGED) {
			SetDockEngaged(DOCK_2, dAction.second);
		} else if (dAction.first == SET_RIGHT_DOCK_ENGAGED) {
			SetDockEngaged(DOCK_3, dAction.second);
		} else if (dAction.first == SET_UP_DOCK_ENGAGED) {
			SetDockEngaged(DOCK_4, dAction.second);
		} else if (dAction.first == SET_DOWN_DOCK_ENGAGED) {
			SetDockEngaged(DOCK_5, dAction.second);
		} else if (dAction.first == SET_FRONT_DOCK_ENGAGED_TO_GROUND) {
			SetDockEngagedToGround(DOCK_0, dAction.second);
		} else if (dAction.first == SET_BACK_DOCK_ENGAGED_TO_GROUND) {
			SetDockEngagedToGround(DOCK_1, dAction.second);
		} else if (dAction.first == ENGAGE_FRONT_DOCK_TO_GROUND) {
			EngageDockToGround(DOCK_0, dAction.second);
		} else if (dAction.first == ENGAGE_BACK_DOCK_TO_GROUND) {
			EngageDockToGround(DOCK_1, dAction.second);
		} else if (dAction.first == SET_FRONT_DOCK_ENGAGED_TO_OBJECT) {
			SetDockEngagedToObject(DOCK_0, dAction.second);
		} else if (dAction.first == SET_BACK_DOCK_ENGAGED_TO_OBJECT) {
			SetDockEngagedToObject(DOCK_1, dAction.second);
		} else if (dAction.first == ENGAGE_FRONT_DOCK_TO_OBJECT) {
			if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
				AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
				EngageDockToObject(DOCK_0, dAction.second);
			}
		} else if (dAction.first == ENGAGE_BACK_DOCK_TO_OBJECT) {
			if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
				AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
				EngageDockToObject(DOCK_1, dAction.second);
			}
		} else if (dAction.first == ENGAGE_OBJECT_TO_GROUND) {
			if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
				AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
				EngageObjectToGround(dAction.second);
			}
        } else if (dAction.first == ENGAGE_FRONT_DOCK_TO_STACKABLE) {
            EngageDockToStackableObject(DOCK_0, dAction.second);
        } else if (dAction.first == ENGAGE_BACK_DOCK_TO_STACKABLE) {
            EngageDockToStackableObject(DOCK_1, dAction.second);
        } else if (dAction.first == ENGAGE_STACKABLE_OBJECT_TO_GROUND) {
            EngageStackableObjectToGround(dAction.second);
        }
    }
    //cout<< mActions.size() <<endl;
    for (int i=0; i<mActions.size(); i++) {
        std::pair<ModuleAction,std::string> mAction = mActions[i];
        if (mAction.first == SEND_MESSAGE_FRONT_DOCK) {
            SendMessageOnDockFace(DOCK_0, mAction.second);
        } else if (mAction.first == SEND_MESSAGE_BACK_DOCK) {
            SendMessageOnDockFace(DOCK_1, mAction.second);
        } else if (mAction.first == SEND_MESSAGE_LEFT_DOCK) {
            SendMessageOnDockFace(DOCK_2, mAction.second);
        } else if (mAction.first == SEND_MESSAGE_RIGHT_DOCK) {
            SendMessageOnDockFace(DOCK_3, mAction.second);
        } else if (mAction.first == SEND_MESSAGE_UP_DOCK) {
            SendMessageOnDockFace(DOCK_4, mAction.second);
        } else if (mAction.first == SEND_MESSAGE_DOWN_DOCK) {
            SendMessageOnDockFace(DOCK_5, mAction.second);
        } else if (mAction.first == SEND_RANGED_MESSAGE) {
            SendRangedMessage(mAction.second);
        }
    }
    for (int i=0; i<kActions.size(); i++) {
        std::pair<ModuleAction,KinematicsMessage> kAction = kActions[i];
        if (kAction.first == SEND_KINEMATICS_MESSAGE_FRONT_DOCK) {
            SendKinematicsMessageOnDockFace(DOCK_0, kAction.second);
        } else if (kAction.first == SEND_KINEMATICS_MESSAGE_BACK_DOCK) {
            SendKinematicsMessageOnDockFace(DOCK_1, kAction.second);
        } else if (kAction.first == SEND_KINEMATICS_MESSAGE_LEFT_DOCK) {
            SendKinematicsMessageOnDockFace(DOCK_2, kAction.second);
        } else if (kAction.first == SEND_KINEMATICS_MESSAGE_RIGHT_DOCK) {
            SendKinematicsMessageOnDockFace(DOCK_3, kAction.second);
        } else if (kAction.first == SEND_KINEMATICS_MESSAGE_UP_DOCK) {
            SendKinematicsMessageOnDockFace(DOCK_4, kAction.second);
        } else if (kAction.first == SEND_KINEMATICS_MESSAGE_DOWN_DOCK) {
            SendKinematicsMessageOnDockFace(DOCK_5, kAction.second);
        }
    }
    for (int i=0; i<tActions.size(); i++) {
        std::pair<ModuleAction,TreeMessage> tAction = tActions[i];
        if (tAction.first == SEND_TREE_MESSAGE_FRONT_DOCK) {
            SendTreeMessageOnDockFace(DOCK_0, tAction.second);
        } else if (tAction.first == SEND_TREE_MESSAGE_BACK_DOCK) {
            SendTreeMessageOnDockFace(DOCK_1, tAction.second);
        } else if (tAction.first == SEND_TREE_MESSAGE_LEFT_DOCK) {
            SendTreeMessageOnDockFace(DOCK_2, tAction.second);
        } else if (tAction.first == SEND_TREE_MESSAGE_RIGHT_DOCK) {
            SendTreeMessageOnDockFace(DOCK_3, tAction.second);
        } else if (tAction.first == SEND_TREE_MESSAGE_UP_DOCK) {
            SendTreeMessageOnDockFace(DOCK_4, tAction.second);
        } else if (tAction.first == SEND_TREE_MESSAGE_DOWN_DOCK) {
            SendTreeMessageOnDockFace(DOCK_5, tAction.second);
        }
    }
}

/**
 * @brief engage dock to ground
 */
void ASuperBotModule::EngageDockToGround(ModuleDockFace d, bool engaged) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		if (!engaged) {
			this->GroundDockConstraints[d]->GetConstraintComp()->BreakConstraint();
			this->GroundDockConstraints[d]->Destroy();
			Docks[d].SetDockEngagedToGround(false);
		}
		else {
			mode->DockModuleToGround(this, d);
		}
	}
}

/**
* @brief engage dock to object
*/
void ASuperBotModule::EngageObjectToGround(bool engaged) {
	AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
	if (!engaged) {
		mode->GetManipConstraint()->GetConstraintComp()->BreakConstraint();
		mode->GetManipConstraint()->Destroy();
	}
	else {
		this->SetDockEngagedToObject(DOCK_0, false);
		this->SetDockEngagedToObject(DOCK_1, false);
		mode->DockObjectToGround(mode->GetManipObject());
	}
}

/**
 * @brief engage dock to object
 */
void ASuperBotModule::EngageStackableObjectToGround(bool engaged) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		StackToPlaneBehavior* B = (StackToPlaneBehavior*)ModuleBehavior;
		std::pair<AActor*, AActor*> p = B->GetCurrentStackablePair();
		if (!engaged) {
			mode->RemoveStackableConstraint(p.first, p.second);
		}
		else {
			this->SetDockEngagedToObject(DOCK_0, false);
			this->SetDockEngagedToObject(DOCK_1, false);
			mode->DockStackableObjectToGround(B->GetStackableObs()[B->GetCurrentStackableObjectIndex()]);
		}
	}
}

/**
* @brief engage dock to ground
*/
void ASuperBotModule::EngageDockToObject(ModuleDockFace d, bool engaged) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		if (!engaged) {
			this->ObjectDockConstraints[d]->GetConstraintComp()->BreakConstraint();
			this->ObjectDockConstraints[d]->Destroy();
			Docks[d].SetDockEngagedToObject(false);
		}
		else {
			mode->DockModuleToObject(this, d, mode->GetManipObject());
		}
	}
}
/**
 * @brief engage dock to stackable object
 * @param d module dock face
 * @param engaged whether or not we are engaging or disengaging from object
 */
void ASuperBotModule::EngageDockToStackableObject(ModuleDockFace d, bool engaged) {
	if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
		AReBotsModuleGameMode *mode = GetWorld()->GetAuthGameMode<AReBotsModuleGameMode>();
		if (!engaged) {
			this->ObjectDockConstraints[d]->GetConstraintComp()->BreakConstraint();
			this->ObjectDockConstraints[d]->Destroy();
			Docks[d].SetDockEngagedToObject(false);
		}
		else {
			StackToPlaneBehavior* B = NULL;
			if (BehaviorType == B_STACKTOPLANE) {
				B = (StackToPlaneBehavior*)ModuleBehavior;
			}
			mode->DockModuleToStackableObject(this, d, B->GetStackableObs()[B->GetCurrentStackableObjectIndex()]);
		}
	}
}
/**
* @brief get dock enabled to object statuses
*/
vector<bool> ASuperBotModule::GetDockEnabledToObjectStatuses() {
	vector<bool> ds(6);
	for (int i = 0; i<6; i++) {
		ds[i] = Docks[i].GetDockEnabledToObject();
	}
	return ds;
}
/**
* @brief get dock engaged to object statuses
*/
vector<bool> ASuperBotModule::GetDockEngagedToObjectStatuses() {
	vector<bool> ds(6);
	for (int i = 0; i<6; i++) {
		ds[i] = Docks[i].GetDockEngagedToObject();
	}
	return ds;
}
/**
* @brief get dock enabled to object status
* @param dock face d
* @return get dock enabled to object
*/
bool ASuperBotModule::GetDockEnabledToObject(ModuleDockFace d) {
	return Docks[d].GetDockEnabledToObject();
}
/**
* @brief get dock engaged to object status
* @param dock face d
* @return get dock engaged to object
*/
bool ASuperBotModule::GetDockEngagedToObject(ModuleDockFace d) {
	return Docks[d].GetDockEngagedToObject();
}
/**
* @brief set dock enabled to object status
* @param dock face d
* @param de dock enabled
*/
void ASuperBotModule::SetDockEnabledToObject(ModuleDockFace d, bool de) {
	Docks[d].SetDockEnabledToObject(de);
}
/**
* @brief set dock engaged to object status
* @param dock face d
* @param de dock engaged
*/
void ASuperBotModule::SetDockEngagedToObject(ModuleDockFace d, bool de) {
	Docks[d].SetDockEngagedToObject(de);
}
/**
  * @brief set module behavior
  * @param B module behavior
  */
void ASuperBotModule::SetModuleBehavior(RobotModuleBehavior* B) {
    this->ModuleBehavior = B;
	if (!B) { this->BehaviorType = B_NONE; }
}
/**
 * @brief get motor (joint angles)
 * @return superbot joint angles
 */
ModuleMotorVector ASuperBotModule::GetJointAngles() {
    ModuleMotorVector mcv;
    float swingM = MasterJoint->GetCurrentSwing1();
    if (swingM < -26.5 && swingM > -26.7) {
        swingM = 0;
    } else if (swingM <= -26.7) {
        swingM = swingM + 26.6159;
    } else if (swingM > -26.5 && swingM <=0) {
        swingM = 26.6159 + swingM;
    } else if (swingM > 0) {
        swingM = swingM + 26.6159;
    }
    float twistI = InnerJoint->GetCurrentTwist();
    FTransform masterInnerT = MasterInner->GetComponentTransform();
    FTransform slaveInnerT = FTransform(FQuat(FVector(0,1,0),M_PI))*SlaveInner->GetComponentTransform();
    
    FTransform masterInnerTUp = FTransform(FVector(0,30,0))*masterInnerT;
    FTransform slaveInnerTUp = FTransform(FVector(0,30,0))*slaveInnerT;
    
    FTransform locDiff = slaveInnerTUp*masterInnerTUp.Inverse();
    
    bool negRotation = false;
    
    if (locDiff.GetLocation().Z < 0) {
        negRotation = true;
    }
    
    
    slaveInnerT.SetLocation(masterInnerT.GetLocation());
    
    
    FVector rotationAxis = FVector::CrossProduct(slaveInnerT.GetRotation().GetAxisZ(),masterInnerT.GetRotation().GetAxisZ());
    rotationAxis.Normalize();
    float rotationAngle = acos(FVector::DotProduct(slaveInnerT.GetRotation().GetAxisZ(),masterInnerT.GetRotation().GetAxisZ()));
    
    twistI = rotationAngle*(180.0/PI);

    
    if (negRotation) twistI = -twistI;
    
    float swingS = SlaveJoint->GetCurrentSwing1();
    if (swingS < -26.5 && swingS > -26.7) {
        swingS = 0;
    } else if (swingS <= -26.7) {
        swingS = swingS + 26.6159;
    } else if (swingS > -26.5 && swingS <=0) {
        swingS = 26.6159 + swingS;
    } else if (swingS > 0) {
        swingS = swingS + 26.6159;
    }
    
    if (swingS < -180) {
        swingS += 360;
    }
    if (swingM < -180) {
        swingM += 360;
    }
    mcv.Motor0Angle = swingM;
    mcv.Motor1Angle = twistI;
    mcv.Motor2Angle = swingS;
    if (isnan(twistI)) {
        //cout<<"IsNan Detected"<<endl;
        mcv.Motor1Angle = 0.0;
    }
    //cout<<"Current Angles: "<<mcv[0]<<" "<<mcv[1]<<" "<<mcv[2]<<endl;
    return mcv;
}
/**
 * @brief set joint angles
 * @param ja joint angles vector
 */
void ASuperBotModule::SetJointAngles(ModuleMotorVector ja) {
    MasterJoint->SetAngularOrientationTarget(FRotator(0,ja[0],0));
    InnerJoint->SetAngularOrientationTarget(FRotator(0,0,ja[1]));
    SlaveJoint->SetAngularOrientationTarget(FRotator(0,ja[2],0));
    desJoints.Motor0Angle = ja[0];
    desJoints.Motor1Angle = ja[1];
    desJoints.Motor2Angle = ja[2];
}
/**
 * @brief are current joint angles close to desired ones
 * @param tol tolerance
 * @return true if desired and current angles "same", false otherwise.
 */
bool ASuperBotModule::AreCurrentJointAnglesDesired(float tol) {
    if (fabs(curJoints.Motor0Angle - desJoints.Motor0Angle) > tol ||
        fabs(curJoints.Motor1Angle - desJoints.Motor1Angle) > tol ||
        fabs(curJoints.Motor2Angle - desJoints.Motor2Angle) > tol) {
        return false;
    } else {
        return true;
    }
}
/**
 * @brief wake up module
 */
void ASuperBotModule::WakeUpModule() {
    MasterOuter->WakeAllRigidBodies();
    SlaveOuter->WakeAllRigidBodies();
    MasterInner->WakeAllRigidBodies();
    SlaveInner->WakeAllRigidBodies();
}
/**
 * @brief initialize module behavior
 */
void ASuperBotModule::InitializeModuleBehavior() {
    if (BehaviorType == B_TWIST) {
        ModuleBehavior = (RobotModuleBehavior*)new TwistBehavior();
    } else if (BehaviorType == B_CATERPILLAR) {
        ModuleBehavior = (RobotModuleBehavior*)new CaterpillarBehavior(100,20,20,10,2);
    } else if (BehaviorType == B_FK) {
        ModuleBehavior = (RobotModuleBehavior*)new ForwardKinematicsBehavior();
    } else if (BehaviorType == B_FK_IK) {
        ModuleBehavior = (FKIKBehavior*)new FKIKBehavior(GetWorld(), this->GetName());
    } else if (BehaviorType == B_6DDOCK) {
        //ModuleBehavior = new GoToAnglesBehavior(std::vector<float> {45,0,-45});
    } else if (BehaviorType == B_MODMANIPQ) {
		ModuleBehavior = (ModManipQBehavior*)new ModManipQBehavior(GetWorld(), this->GetName());
	} else if (BehaviorType == B_RECONF) {
		ModuleBehavior = (ReconfDemoQBehavior*)new ReconfDemoQBehavior(GetWorld(), this->GetName());
	} else if (BehaviorType == B_RECONF2) {
		ModuleBehavior = (ReconfDemoQ2Behavior*)new ReconfDemoQ2Behavior(GetWorld(), this->GetName());
	} else if (BehaviorType == B_SNAKEIK) {
		ModuleBehavior = (SnakeIKBehavior*)new SnakeIKBehavior(GetWorld(), this->GetName());
	} else if (BehaviorType == B_TREEWALK) {
		ModuleBehavior = (TreeWalkingBehavior*)new TreeWalkingBehavior(GetWorld(), this->GetName());
	} else if (BehaviorType == B_RECONFIK) {
		ModuleBehavior = (ReconfIKBehavior*)new ReconfIKBehavior(GetWorld(), this->GetName());
	} else if (BehaviorType == B_STACKTOPLANE) {
		ModuleBehavior = (StackToPlaneBehavior*)new StackToPlaneBehavior(GetWorld(), this->GetName());
	}
	else if (BehaviorType == B_DIK) {
		ModuleBehavior = (DistributedIKBehavior*)new DistributedIKBehavior(GetWorld(), this->GetName());
	} else if (BehaviorType == B_DIST_KINEMATICS) {
		ModuleBehavior = (DistributedKinematicsBehavior*)new DistributedKinematicsBehavior(GetWorld(), this->GetName());
    } else if (BehaviorType == B_NONE) {
		ModuleBehavior = NULL;
	}
	else if (BehaviorType == B_THAT) {
		ModuleBehavior = (THatDistributed*)new THatDistributed();
	}
}
/**
 * @brief get transform to master inner
 */
FTransform ASuperBotModule::GetRootToMasterInnerTransform() {
    return ASuperBotModule::SuperbotFix*MasterInner->GetComponentTransform()*GetRootComponent()->GetComponentToWorld().Inverse();
}
/**
 * @brief weld dock to component
 * @param d dock
 * @param sc scene component
 */
void ASuperBotModule::WeldDockToComponent(ModuleDockFace d, USceneComponent* sc) {
    Docks[d].GetDockComponent()->WeldTo(sc);
}
/**
 * @brief advance the simulation
 * @param DeltaSeconds fraction of a second by which to advance simulation
 */
void ASuperBotModule::Tick( float DeltaTime )
{
    if (!ModuleBehavior) {
        InitializeModuleBehavior();
    }
    Super::Tick( DeltaTime );
    WakeUpModule();
    ModuleMotorVector mv = GetJointAngles();
    curJoints.Motor0Angle = mv.Motor0Angle;
    curJoints.Motor1Angle = mv.Motor1Angle;
    curJoints.Motor2Angle = mv.Motor2Angle;
    if (ModuleBehavior && AngleWaitCounter <=0 && BehaviorMode) {
        vector<Message> ms = GetMessages();
        vector<RangedMessage> rms = GetRangedMessages();
        vector<KinematicsMessage> kms = GetKinematicsMessages();
        vector<TreeMessage> tms = GetTreeMessages();
        currentState.SetDocksEnabledStatus(GetDockEnabledStatuses());
        currentState.SetDocksEngagedStatus(GetDockEngagedStatuses());
        currentState.SetDocksEnabledToGroundStatus(GetDockEnabledToGroundStatuses());
        currentState.SetDocksEngagedToGroundStatus(GetDockEngagedToGroundStatuses());
		currentState.SetDocksEnabledToObjectStatus(GetDockEnabledToObjectStatuses());
		currentState.SetDocksEngagedToObjectStatus(GetDockEngagedToObjectStatuses());
        currentState.SetJointAngles(curJoints);
        currentState.SetMessages(ms);
        currentState.SetRangedMessages(rms);
        currentState.SetKinematicsMessages(kms);
        currentState.SetTreeMessages(tms);
        currentState.SetIDNumber(this->IDNumber);
        model.SetCurrentState(currentState);
        model.SetDesiredState(desiredState);
        ModuleBehavior->Tick(model);
        PerformActions();
        if (ModuleBehavior->GetName().compare("FK") == 0) {
            ForwardKinematicsBehavior *FKB = (ForwardKinematicsBehavior*)ModuleBehavior;
            if (FKB->GetSuperBotTree().GetVertices().size() > 0 && RenderKGFramesModules) {
                size_t s = RefFramesKG.size();
                for (int i=0; i<s; i++) {
                    RefFramesKG[i]->Destroy();
                }
                RefFramesKG.clear();
                for (int i=0; i<FKB->GetSuperBotTree().GetVertices().size(); i++) {
                    ModuleNode* kn = FKB->GetSuperBotTree().GetVertices()[i];
                    FTransform kt = kn->GetTransform()*SuperbotFix*this->MasterInner->GetComponentTransform();
                    RefFramesKG.push_back(GetWorld()->SpawnActor<AReferenceFrameActor>(kt.GetLocation(),FRotator(kt.GetRotation())));
                }
            } else {
                for (int i=0; i<RefFramesKG.size(); i++) {
                    RefFramesKG[i]->Destroy();
                }
                RefFramesKG.clear();
            }
        } else if (ModuleBehavior->GetName().compare("FKIK") == 0) {
            FKIKBehavior *FKB = (FKIKBehavior*)ModuleBehavior;
            
            if (FKB->GetSuperBotTree().GetVertices().size() > 0 && RenderGroundFrame) {
                int gm = FKB->GetGroundModule();
                if (gm != -1 && FKB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
                    ModuleNode *kn = FKB->GetSuperBotTree().GetVertices()[gm];
                    ModuleMotorVector mvs(FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
                                            FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
                                            FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
                    FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs,FKB->GetGroundDockFace())*SuperbotFix*MasterInner->GetComponentTransform();
                    FTransform ActualGroundTrans = FKB->GetModuleBaseToGroundTransform()*GroundActorTrans;
                    if (!GroundFrame) {
                        GroundFrame = GetWorld()->SpawnActor<AReferenceFrameActor>(ActualGroundTrans.GetLocation(),
                                                  FRotator(ActualGroundTrans.GetRotation()));
                    } else {
                        GroundFrame->SetActorTransform(ActualGroundTrans);
                    }
                }
            }
            if (FKB->GetSuperBotTree().GetVertices().size() > 0 && RenderKGFramesModules) {
                size_t s = RefFramesKG.size();
                for (int i=0; i<s; i++) {
                    if (RefFramesKG[i])RefFramesKG[i]->Destroy();
                }
                RefFramesKG.clear();
                s = FKB->GetSuperBotTree().GetVertices().size();
                for (int i=0; i<s; i++) {
                    ModuleNode* kn = FKB->GetSuperBotTree().GetVertices()[i];
                    FTransform kt = kn->GetTransform()*
                    SuperbotKinematics::computeTransformToDock(GetJointAngles(),DOCK_1)*SuperbotFix*this->MasterInner->GetComponentTransform();
                    RefFramesKG.push_back(GetWorld()->SpawnActor<AReferenceFrameActor>(kt.GetLocation(),FRotator(kt.GetRotation())));
                }
            } else {
                size_t s = RefFramesKG.size();
                for (int i=0; i<s; i++) {
                    if(RefFramesKG[i])RefFramesKG[i]->Destroy();
                }
                RefFramesKG.clear();
            }
            if (FKB->GetSuperBotTree().GetVertices().size() > 0 && RenderFinalFK) {
                if (FinalFKActor) FinalFKActor->Destroy();
                int see = FKB->GetSelectedEndEffector();
                if (see != -1 && FKB->GetSuperBotTree().GetVertices().size() - 1 >= see) {
                    FTransform FinalFKActorTrans = FKB->GetSuperBotTree().GetVertices()[see]->GetTransform()*
                    SuperbotKinematics::computeTransformToDock(GetJointAngles(),DOCK_1)*SuperbotFix*this->MasterInner->GetComponentTransform();
                    ModuleMotorVector mvs(FKB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[0],
                                            FKB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[1],
                                            FKB->GetSuperBotTree().GetVertices()[see]->GetJointAngles()[2]);
                    FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvs,
                                                                                   FKB->GetEndEffectorDockFace())*FinalFKActorTrans;
                    FinalFKActor = GetWorld()->SpawnActor<AReferenceFrameActor>(FinalFKActorTrans.GetLocation(),FRotator(FinalFKActorTrans.GetRotation()));
                }
            } else {
                if (FinalFKActor) FinalFKActor->Destroy();
            }
            if (FKB->GetSuperBotTree().GetVertices().size() > 0 && RenderBaseFrame) {
                if (BaseTransformActor) BaseTransformActor->Destroy();
                int gm = FKB->GetGroundModule();
                if (gm != -1 && FKB->GetSuperBotTree().GetVertices().size() - 1 >= gm) {
                    ModuleMotorVector mvs(FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[0],
                                            FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[1],
                                            FKB->GetSuperBotTree().GetVertices()[gm]->GetJointAngles()[2]);
                    FTransform GroundActorTrans = SuperbotKinematics::computeTransformToDock(mvs,FKB->GetGroundDockFace())*SuperbotFix*this->MasterInner->GetComponentTransform();
                    BaseTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>(GroundActorTrans.GetLocation(),FRotator(GroundActorTrans.GetRotation()));
                }
            } else {
                if (BaseTransformActor) BaseTransformActor->Destroy();
            }
            if (FKB->GetSuperBotTree().GetVertices().size() > 0 && RenderBoundingBoxes) {
                size_t s = BoundingSpheres.size();
                for (int i=0; i<s; i++) {
                    if(BoundingSpheres[i])BoundingSpheres[i]->Destroy();
                }
                BoundingSpheres.clear();
                s = FKB->GetSuperBotTree().GetVertices().size();
                for (int i=0; i<s; i++) {
                    ModuleNode* kn = FKB->GetSuperBotTree().GetVertices()[i];
                    FTransform kt = kn->GetTransform()*
                    SuperbotKinematics::computeTransformToDock(GetJointAngles(),DOCK_1)*SuperbotFix*this->MasterInner->GetComponentTransform();
                    BoundingSpheres.push_back(GetWorld()->SpawnActor<ABoundingSphere>(kt.GetLocation(),FRotator(kt.GetRotation())));
                    if (kn->GetAmIEndEffector()) {
                        BoundingSpheres[BoundingSpheres.size() - 1]->SetColor(OrangeColor);
                    } else if (kn->GetConnectedToGround()) {
                        BoundingSpheres[BoundingSpheres.size() - 1]->SetColor(YellowColor);
                    }
                }
            } else {
                size_t s = BoundingSpheres.size();
                for (int i=0; i<s; i++) {
                    if(BoundingSpheres[i])BoundingSpheres[i]->Destroy();
                }
                BoundingSpheres.clear();
            }
            if (FKB->GetSuperBotTree().GetVertices().size() > 0 && RenderTargetTransform) {
                FTransform BaseT = SuperbotKinematics::computeTransformToDock(GetJointAngles(),DOCK_1)*SuperbotFix*this->MasterInner->GetComponentTransform();
                if (TargetTransformActor == NULL) {
                    TargetTransformActor = GetWorld()->SpawnActor<AReferenceFrameActor>((FKB->GetTargetTransform()*BaseT).GetLocation(),
                                                                                    FRotator((FKB->GetTargetTransform()*BaseT).GetRotation()));
                } else {
                    TargetTransformActor->SetActorTransform((FKB->GetTargetTransform()*BaseT));
                }
            }
        }
        
    } else {
        AngleWaitCounter--;
    }
    if (AutoDocking) {
        if (Docks[DOCK_0].GetDockEnabled() && !Docks[DOCK_0].GetDockEngaged()) {
            if (!DCBFront) {
                DCBFront = GetWorld()->SpawnActor<ADockCollisionActor>(FrontDock->GetComponentTransform().GetLocation(),
                                                                       FRotator(FrontDock->GetComponentTransform().GetRotation()));
                DCBFront->SetModuleAndDockFace(this, DOCK_0);
                DCBFront->SetActorTransform(FTransform(FVector(0,-1,17))*DCBFront->GetTransform());
                if (RenderDockCollisions) {
                    DCBFront->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBFront->GetRootComponent()->bHiddenInGame = true;
                }
                
            } else {
                DCBFront->SetActorLocationAndRotation(FrontDock->GetComponentTransform().GetLocation(), FRotator(FrontDock->GetComponentTransform().GetRotation()));
                DCBFront->SetActorTransform(FTransform(FVector(0,-1,17))*DCBFront->GetTransform());
                if (RenderDockCollisions) {
                    DCBFront->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBFront->GetRootComponent()->bHiddenInGame = true;
                }
            }
        } else {
            if (DCBFront) DCBFront->Destroy();
            DCBFront = NULL;
        }
        
        if (Docks[DOCK_1].GetDockEnabled() && !Docks[DOCK_1].GetDockEngaged()) {
            if (!DCBBack) {
                DCBBack = GetWorld()->SpawnActor<ADockCollisionActor>(BackDock->GetComponentTransform().GetLocation(),
                                                                      FRotator(BackDock->GetComponentTransform().GetRotation()));
                DCBBack->SetModuleAndDockFace(this, DOCK_1);
                DCBBack->SetActorTransform(FTransform(FVector(0,-1,17))*DCBBack->GetTransform());
                if (RenderDockCollisions) {
                    DCBBack->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBBack->GetRootComponent()->bHiddenInGame = true;
                }
            } else {
                DCBBack->SetActorLocationAndRotation(BackDock->GetComponentTransform().GetLocation(), FRotator(BackDock->GetComponentTransform().GetRotation()));
                DCBBack->SetActorTransform(FTransform(FVector(0,-1,17))*DCBBack->GetTransform());
                if (RenderDockCollisions) {
                    DCBBack->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBBack->GetRootComponent()->bHiddenInGame = true;
                }
            }
        } else {
            if (DCBBack) DCBBack->Destroy();
            DCBBack = NULL;
        }
        
        if (Docks[DOCK_2].GetDockEnabled() && !Docks[DOCK_2].GetDockEngaged()) {
            if (!DCBLeft) {
                DCBLeft = GetWorld()->SpawnActor<ADockCollisionActor>(LeftDock->GetComponentTransform().GetLocation(),
                                                                      FRotator(LeftDock->GetComponentTransform().GetRotation()));
                DCBLeft->SetModuleAndDockFace(this, DOCK_2);
                DCBLeft->SetActorTransform(FTransform(FVector(0,-1,17))*DCBLeft->GetTransform());
                if (RenderDockCollisions) {
                    DCBLeft->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBLeft->GetRootComponent()->bHiddenInGame = true;
                }
            } else {
                DCBLeft->SetActorLocationAndRotation(LeftDock->GetComponentTransform().GetLocation(), FRotator(LeftDock->GetComponentTransform().GetRotation()));
                DCBLeft->SetActorTransform(FTransform(FVector(0,-1,17))*DCBLeft->GetTransform());
                if (RenderDockCollisions) {
                    DCBLeft->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBLeft->GetRootComponent()->bHiddenInGame = true;
                }
            }
        } else {
            if (DCBLeft) DCBLeft->Destroy();
            DCBLeft = NULL;
        }
        
        
        if (Docks[DOCK_3].GetDockEnabled() && !Docks[DOCK_3].GetDockEngaged()) {
            if (!DCBRight) {
                DCBRight = GetWorld()->SpawnActor<ADockCollisionActor>(RightDock->GetComponentTransform().GetLocation(),
                                                                       FRotator(RightDock->GetComponentTransform().GetRotation()));
                DCBRight->SetModuleAndDockFace(this, DOCK_3);
                DCBRight->SetActorTransform(FTransform(FVector(0,-1,17))*DCBRight->GetTransform());
                if (RenderDockCollisions) {
                    DCBRight->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBRight->GetRootComponent()->bHiddenInGame = true;
                }
            } else {
                DCBRight->SetActorLocationAndRotation(RightDock->GetComponentTransform().GetLocation(), FRotator(RightDock->GetComponentTransform().GetRotation()));
                DCBRight->SetActorTransform(FTransform(FVector(0,-1,17))*DCBRight->GetTransform());
                if (RenderDockCollisions) {
                    DCBRight->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBRight->GetRootComponent()->bHiddenInGame = true;
                }
            }
        } else {
            if (DCBRight) DCBRight->Destroy();
            DCBRight = NULL;
        }
        
        if (Docks[DOCK_4].GetDockEnabled() && !Docks[DOCK_4].GetDockEngaged()) {
            if (!DCBUp) {
                DCBUp = GetWorld()->SpawnActor<ADockCollisionActor>(UpDock->GetComponentTransform().GetLocation(),
                                                                    FRotator(UpDock->GetComponentTransform().GetRotation()));
                DCBUp->SetModuleAndDockFace(this, DOCK_4);
                DCBUp->SetActorTransform(FTransform(FVector(0,-1,17))*DCBUp->GetTransform());
                if (RenderDockCollisions) {
                    DCBUp->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBUp->GetRootComponent()->bHiddenInGame = true;
                }
            } else {
                DCBUp->SetActorLocationAndRotation(UpDock->GetComponentTransform().GetLocation(), FRotator(UpDock->GetComponentTransform().GetRotation()));
                DCBUp->SetActorTransform(FTransform(FVector(0,-1,17))*DCBUp->GetTransform());
                if (RenderDockCollisions) {
                    DCBUp->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBUp->GetRootComponent()->bHiddenInGame = true;
                }
            }
        } else {
            if (DCBUp) DCBUp->Destroy();
            DCBUp = NULL;
        }
        
        if (Docks[DOCK_5].GetDockEnabled() && !Docks[DOCK_5].GetDockEngaged()) {
            if (!DCBDown) {
                DCBDown = GetWorld()->SpawnActor<ADockCollisionActor>(DownDock->GetComponentTransform().GetLocation(),
                                                                      FRotator(DownDock->GetComponentTransform().GetRotation()));
                DCBDown->SetModuleAndDockFace(this, DOCK_5);
                DCBDown->SetActorTransform(FTransform(FVector(0,-1,17))*DCBDown->GetTransform());
                if (RenderDockCollisions) {
                    DCBDown->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBDown->GetRootComponent()->bHiddenInGame = true;
                }
            } else {
                DCBDown->SetActorLocationAndRotation(DownDock->GetComponentTransform().GetLocation(), FRotator(DownDock->GetComponentTransform().GetRotation()));
                DCBDown->SetActorTransform(FTransform(FVector(0,-1,17))*DCBDown->GetTransform());
                if (RenderDockCollisions) {
                    DCBDown->GetRootComponent()->bHiddenInGame = false;
                } else {
                    DCBDown->GetRootComponent()->bHiddenInGame = true;
                }
            }
        } else {
            if (DCBDown) DCBDown->Destroy();
            DCBDown = NULL;
        }
    }
    
    if (RenderModuleFrame) {
        if (!rFrameModule) {
            FTransform t = RootComponent->GetComponentTransform();
            rFrameModule = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(), FRotator(t.GetRotation()));
        } else {
            FTransform t = RootComponent->GetComponentTransform();
            rFrameModule->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());
        }
    } else {
        if (rFrameModule) {GetWorld()->DestroyActor(rFrameModule);}
        rFrameModule = NULL;
    }
    if (RenderDockFrames) {
        if (!rFrameFrontDock) {
            FTransform tf = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_0);
            FTransform t = tf*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameFrontDock = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(), FRotator(t.GetRotation()));
        } else {
            FTransform tf = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_0);
            FTransform t = tf*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameFrontDock->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());
        }
        if (!rFrameBackDock) {
            FTransform tb = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_1);
            FTransform t = tb*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameBackDock = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(), FRotator(t.GetRotation()));
        } else {
            FTransform tb = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_1);
            FTransform t = tb*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameBackDock->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());
        }
        if (!rFrameLeftDock) {
            FTransform tl = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_2);
            FTransform t = tl*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameLeftDock = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(), FRotator(t.GetRotation()));
        } else {
            FTransform tl = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_2);
            FTransform t = tl*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameLeftDock->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());
        }
        if (!rFrameRightDock) {
            FTransform tr = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_3);
            FTransform t = tr*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameRightDock = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(), FRotator(t.GetRotation()));
        } else {
            FTransform tr = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_3);
            FTransform t = tr*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameRightDock->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());
        }
        if (!rFrameUpDock) {
            FTransform tu = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_4);
            FTransform t = tu*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameUpDock = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(), FRotator(t.GetRotation()));
        } else {
            FTransform tu = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_4);
            FTransform t = tu*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameUpDock->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());
        }
        if (!rFrameDownDock) {
            FTransform td = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_5);
            FTransform t = td*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameDownDock = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(), FRotator(t.GetRotation()));
        } else {
            FTransform td = SuperbotKinematics::computeTransformToDock(GetJointAngles(), DOCK_5);
            FTransform t = td*ASuperBotModule::SuperbotFix*GetMasterInnerMesh()->GetComponentTransform();
            rFrameDownDock->SetActorLocationAndRotation(t.GetLocation(), t.GetRotation());
        }
    } else {
        if (rFrameFrontDock) {GetWorld()->DestroyActor(rFrameFrontDock);}
        if (rFrameBackDock) {GetWorld()->DestroyActor(rFrameBackDock);}
        if (rFrameLeftDock) {GetWorld()->DestroyActor(rFrameLeftDock);}
        if (rFrameRightDock) {GetWorld()->DestroyActor(rFrameRightDock);}
        if (rFrameUpDock) {GetWorld()->DestroyActor(rFrameUpDock);}
        if (rFrameDownDock) {GetWorld()->DestroyActor(rFrameDownDock);}
        rFrameFrontDock = NULL;
        rFrameBackDock = NULL;
        rFrameLeftDock = NULL;
        rFrameRightDock = NULL;
        rFrameUpDock = NULL;
        rFrameDownDock = NULL;
    }
    
}
/**
 * @brief set material for all bodies
 */
void ASuperBotModule::SetMaterialForAllBodies(UMaterialInterface* material) {
    MasterInner->SetMaterial(0, material);
    SlaveInner->SetMaterial(0, material);
    MasterOuter->SetMaterial(0, material);
    SlaveOuter->SetMaterial(0, material);
    FrontDock->SetMaterial(0, material);
    BackDock->SetMaterial(0, material);
    LeftDock->SetMaterial(0, material);
    RightDock->SetMaterial(0, material);
    UpDock->SetMaterial(0, material);
    DownDock->SetMaterial(0, material);
}
/**
 * @brief get module behavior
 * @return module behavior
 */
RobotModuleBehavior* ASuperBotModule::GetModuleBehavior() {
    return this->ModuleBehavior;
}
/**
 * @brief return module name
 * @return name of module
 */
std::string ASuperBotModule::GetName() {
    return this->name;
}
/**
 * @brief return module name
 * @return name of module
 */
void ASuperBotModule::SetName(std::string n) {
    this->name = n;
}
/**
 * @brief set up player input component
 * @param InputComponent
 */
void ASuperBotModule::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    
}
/**
* @brief get sensor value 
* @return sensor value
*/
float ASuperBotModule::Joint0Sensor::GetFloatValue(ASuperBotModule* M) {
	return M->GetJointAngles().Motor0Angle;
}
/**
* @brief get sensor value
* @return sensor value
*/
float ASuperBotModule::Joint1Sensor::GetFloatValue(ASuperBotModule* M) {
	return M->GetJointAngles().Motor1Angle;
}
/**
* @brief get sensor value
* @return sensor value
*/
float ASuperBotModule::Joint2Sensor::GetFloatValue(ASuperBotModule* M) {
	return M->GetJointAngles().Motor2Angle;
}
/**
* @brief get sensor value
* @param M superbot module instance
* @return current sensor value
*/
FTransform ASuperBotModule::PoseSensor::GetTransformValue(ASuperBotModule *M) {
	return ASuperBotModule::SuperbotFix*M->MasterInner->GetComponentTransform();
}
/**
* @brief get sensor value
* @param M superbot module instance
* @return current sensor value
*/
std::vector<bool> ASuperBotModule::DockEnabledSensor::GetFlagValue(ASuperBotModule *M) {
	return M->GetDockEnabledStatuses();
}
/**
* @brief get sensor value
* @param M superbot module instance
* @return current sensor value
*/
std::vector<bool> ASuperBotModule::DockEngagedSensor::GetFlagValue(ASuperBotModule *M) {
	return M->GetDockEngagedStatuses();
}
/**
*@brief get sensor value
* @param M superbot module instance
* @return current sensor value
*/
std::vector<bool> ASuperBotModule::DockEngagedToGroundSensor::GetFlagValue(ASuperBotModule *M) {
	return M->GetDockEngagedToGroundStatuses();
}
/**
* @brief get sensor value
* @param M superbot module instance
* @return current sensor value
*/
std::vector<bool> ASuperBotModule::DockEngagedToObjectSensor::GetFlagValue(ASuperBotModule *M) {
	return M->GetDockEngagedToObjectStatuses();
}
/**
* @brief get module messages
* @param M superbot module
* @return messages
*/
std::vector<ModuleMessage> ASuperBotModule::MessageSensor::GetMessageValue(ASuperBotModule* M) {
	//get message code
	return std::vector<ModuleMessage>{};
}
/**
* @brief set actuator value
* @param M superbot module
* @param Val value to set
*/
void ASuperBotModule::Joint0Actuator::SetFloatValue(ASuperBotModule* M, float Val) {
	M->MasterJoint->SetAngularOrientationTarget(FRotator(0, Val, 0));
	M->desJoints.Motor0Angle = Val;
}
/**
* @brief set actuator value
* @param M superbot module
* @param Val value to set
*/
void ASuperBotModule::Joint1Actuator::SetFloatValue(ASuperBotModule* M, float Val) {
	M->InnerJoint->SetAngularOrientationTarget(FRotator(0, 0, Val));
	M->desJoints.Motor1Angle = Val;
}
/**
* @brief set actuator value
* @param M superbot module
* @param Val value to set
*/
void ASuperBotModule::Joint2Actuator::SetFloatValue(ASuperBotModule* M, float Val) {
	M->SlaveJoint->SetAngularOrientationTarget(FRotator(0, Val, 0));
	M->desJoints.Motor2Angle = Val;
}
/**
* @brief set actuator value
* @param M module
* @param Val value to set for actuator
*/
void ASuperBotModule::DockEnabledActuator::SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val) {
	for (int i = 0; i < 6; i++) {
		M->Docks[i].SetDockEnabled(Val[i]);
	}
}
/**
* @brief set actuator value
* @param M module
* @param Val value to set for actuator
*/
void ASuperBotModule::DockEngagedActuator::SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val) {
	for (int i = 0; i < 6; i++) {
		M->Docks[i].SetDockEngaged(Val[i]);
	}
}
/**
* @brief set actuator value
* @param M module
* @param Val value to set for actuator
*/
void ASuperBotModule::DockEngagedToGroundActuator::SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val) {
	for (int i = 0; i < 6; i++) {
		M->Docks[i].SetDockEngagedToGround(Val[i]);
	}
}
/**
* @brief set actuator value
* @param M module
* @param Val value to set for actuator
*/
void ASuperBotModule::DockEngagedToObjectActuator::SetFlagValue(ASuperBotModule* M, std::vector<bool>& Val) {
	for (int i = 0; i < 6; i++) {
		M->Docks[i].SetDockEngagedToObject(Val[i]);
	}
}
/**
* @brief set message actuator value
* @param M superbot module reference
* @param Mes message
*/
void ASuperBotModule::MessageActuator::SetMessageValue(ASuperBotModule* M, ModuleMessage Mes) {
	//send message code
}
int ASuperBotModule::numSuperBotMods = 0; /**< number of superbot modules */
FTransform ASuperBotModule::SuperbotFix = FTransform(FQuat(FVector(1,0,0),M_PI),FVector(-26.5,0.0,0));
