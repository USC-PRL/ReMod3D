// Fill out your copyright notice in the Description page of Project Settings.

 
#include "RoomBotModule.h"


// Sets default values
ARoomBotModule::ARoomBotModule()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitModule();

}

/**
* @brief initialize module
*/
void ARoomBotModule::InitModule() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> hemMesh(TEXT("/Game/RoomBotMeshes/hemisphere_filled.hemisphere_filled"));

	static ConstructorHelpers::FObjectFinder<UMaterial>
		IMaterial(TEXT("/Game/SuperBotMaterials/SlaveMaterial.SlaveMaterial"));
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

	UMaterial* GreenMaterial = NULL;
	if (GMaterial.Object != NULL) { GreenMaterial = (UMaterial*)GMaterial.Object; }
	UMaterial* RedMaterial = NULL;
	if (RMaterial.Object != NULL) { RedMaterial = (UMaterial*)RMaterial.Object; }
	UMaterial* InnerMaterial = NULL;
	if (IMaterial.Object != NULL) { InnerMaterial = (UMaterial*)IMaterial.Object; }
	UMaterial* OuterMaterial = NULL;
	if (OMaterial.Object != NULL) { OuterMaterial = (UMaterial*)OMaterial.Object; }


	RoomBotHem1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hem1"));
	RoomBotHem2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hem2"));
	HemJoint1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("HemJoint1"));

	RootComponent = RoomBotHem1;
	RootComponent->SetActive(true);
	RootComponent->SetMobility(EComponentMobility::Movable);

	RoomBotHem1->SetStaticMesh(hemMesh.Object);
	RoomBotHem2->SetStaticMesh(hemMesh.Object);


	RoomBotHem1->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RoomBotHem2->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

	RoomBotHem1->SetMaterial(0, GreenMaterial);
	RoomBotHem2->SetMaterial(0, RedMaterial);

	RoomBotHem1->SetSimulatePhysics(true);
	RoomBotHem2->SetSimulatePhysics(true);

	RoomBotHem1->BodyInstance.bEnableGravity = true;
	RoomBotHem2->BodyInstance.bEnableGravity = true;

	RoomBotHem1->BodyInstance.MaxAngularVelocity = 400.0f;
	RoomBotHem2->BodyInstance.MaxAngularVelocity = 400.0f;

	RoomBotHem2->AttachTo(RoomBotHem1);
	HemJoint1->AttachTo(RoomBotHem1);

	RoomBotHem2->SetRelativeLocation(FVector(0, 0, -2));
	RoomBotHem2->SetRelativeRotation(FRotator(0, -180, -180));
	HemJoint1->SetRelativeLocation(FVector(0,0,0));
	HemJoint1->SetRelativeRotation(FRotator(90,0,0));

	HemJoint1->SetConstrainedComponents(RoomBotHem1, FName("Hem1"), RoomBotHem2, FName("Hem2"));
	HemJoint1->SetDisableCollision(true);


	//HemJoint1->ConstraintInstance.bAngularOrientationDrive = true;
	//HemJoint1->ConstraintInstance.bAngularVelocityDrive = true;
	//HemJoint1->ConstraintInstance.bEnableProjection = true;
	HemJoint1->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	HemJoint1->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	HemJoint1->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	HemJoint1->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0);
	HemJoint1->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	HemJoint1->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	//HemJoint1->ConstraintInstance.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	//HemJoint1->ConstraintInstance.ProjectionAngularTolerance = 0.0001;
	//HemJoint1->ConstraintInstance.ProjectionLinearTolerance = 0.0001;
	HemJoint1->SetAngularDriveParams(2000, 1000, 2000000);
	HemJoint1->SetAngularVelocityTarget(FVector(3.0,0,0));



	RoomBotHem1->BodyInstance.PositionSolverIterationCount = 255;
	RoomBotHem1->BodyInstance.VelocitySolverIterationCount = 255;
	RoomBotHem1->BodyInstance.bOverrideMass = true;
	RoomBotHem1->BodyInstance.SetMassOverride(roombot_mass_hem);

	RoomBotHem2->BodyInstance.PositionSolverIterationCount = 255;
	RoomBotHem2->BodyInstance.VelocitySolverIterationCount = 255;
	RoomBotHem2->BodyInstance.bOverrideMass = true;
	RoomBotHem2->BodyInstance.SetMassOverride(roombot_mass_hem);


	RoomBotHem1->SetMobility(EComponentMobility::Movable);
	RoomBotHem2->SetMobility(EComponentMobility::Movable);

	curJoints.Motor0Angle = 0;
	curJoints.Motor1Angle = 0;
	curJoints.Motor2Angle = 0;
	//SetJointAngles(ModuleMotorVector(0, 0, 0));
	std::stringstream ss;
	ss << "SuperBot";
	//ss << numSuperBotMods;
	//this->name = ss.str();
	/////numSuperBotMods++;*/
}
// Called when the game starts or when spawned
void ARoomBotModule::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoomBotModule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

