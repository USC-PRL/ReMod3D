// Fill out your copyright notice in the Description page of Project Settings.

 
#include "SmoresModule.h"


// Sets default values
ASmoresModule::ASmoresModule()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitModule();

}

/**
* @brief initialize module
*/
void ASmoresModule::InitModule() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> innerMesh(TEXT("/Game/SmoresMeshes/SmoresInner.SmoresInner"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> outerMesh(TEXT("/Game/SmoresMeshes/SmoresOuter.SmoresOuter"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> frontWheelMesh(TEXT("/Game/SmoresMeshes/SmoresFrontWheel.SmoresFrontWheel"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mainWheelMesh(TEXT("/Game/SmoresMeshes/SmoresMainWheel.SmoresMainWheel"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

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


	SmoresInner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SmoresInner"));
	SmoresOuter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SmoresOuter"));
	WheelBack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelBack"));
	WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
	WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));
	BackWheelJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("BackWheelJoint"));
	LeftWheelJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("LeftWheelJoint"));
	RightWheelJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("RightWheelJoint"));
	InnerJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("InnerJoint"));
	SmoresController = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SmoresController"));
	RootComponent = BackWheelJoint;
	RootComponent->SetActive(true);
	RootComponent->SetMobility(EComponentMobility::Movable);
	SmoresInner->SetStaticMesh(innerMesh.Object);
	SmoresOuter->SetStaticMesh(outerMesh.Object);
	WheelBack->SetStaticMesh(frontWheelMesh.Object);
	WheelLeft->SetStaticMesh(mainWheelMesh.Object);
	WheelRight->SetStaticMesh(mainWheelMesh.Object);
	SmoresController->SetStaticMesh(cubeMesh.Object);

	SmoresInner->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	SmoresOuter->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	WheelBack->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	WheelLeft->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	WheelRight->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	SmoresController->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

	SmoresInner->SetCenterOfMass(FVector(-15,0,0));
	SmoresOuter->SetCenterOfMass(FVector(-10,0,0));

	SmoresInner->SetMaterial(0, GreenMaterial);
	SmoresOuter->SetMaterial(0, OuterMaterial);
	WheelBack->SetMaterial(0, RedMaterial);
	WheelLeft->SetMaterial(0, RedMaterial);
	WheelRight->SetMaterial(0, RedMaterial);
	SmoresController->SetMaterial(0, RedMaterial);

	SmoresInner->SetSimulatePhysics(true);
	SmoresOuter->SetSimulatePhysics(true);
	WheelBack->SetSimulatePhysics(true);
	WheelLeft->SetSimulatePhysics(true);
	WheelRight->SetSimulatePhysics(true);
	SmoresController->SetSimulatePhysics(true);

	SmoresInner->BodyInstance.bEnableGravity = true;
	SmoresOuter->BodyInstance.bEnableGravity = true;
	WheelBack->BodyInstance.bEnableGravity = true;
	WheelLeft->BodyInstance.bEnableGravity = true;
	WheelRight->BodyInstance.bEnableGravity = true;
	SmoresController->BodyInstance.bEnableGravity = true;

	SmoresInner->BodyInstance.MaxAngularVelocity = 400.0f;
	SmoresOuter->BodyInstance.MaxAngularVelocity = 400.0f;
	WheelBack->BodyInstance.MaxAngularVelocity = 500.0f;
	WheelLeft->BodyInstance.MaxAngularVelocity = 400.0f;
	WheelRight->BodyInstance.MaxAngularVelocity = 400.0f;
	SmoresController->BodyInstance.MaxAngularVelocity = 400.0f;

	SmoresController->SetWorldScale3D(FVector(0.04,0.4,0.4));

	SmoresInner->AttachTo(BackWheelJoint);
	SmoresOuter->AttachTo(BackWheelJoint);
	WheelBack->AttachTo(BackWheelJoint);
	InnerJoint->AttachTo(SmoresOuter);
	WheelLeft->AttachTo(SmoresOuter);
	LeftWheelJoint->AttachTo(WheelLeft);
	WheelRight->AttachTo(SmoresOuter);
	RightWheelJoint->AttachTo(WheelRight);
	SmoresController->AttachTo(SmoresInner);

	SmoresInner->SetRelativeLocation(FVector(-37,0,0));
	SmoresOuter->SetRelativeLocation(FVector(-50,0,0));
	WheelBack->SetRelativeLocation(FVector(3,0,0));
	WheelLeft->SetRelativeLocation(FVector(0,0,46));
	WheelLeft->SetRelativeRotation(FRotator(90, -90, 0));
	WheelRight->SetRelativeLocation(FVector(0,0,-46));
	WheelRight->SetRelativeRotation(FRotator(-90, -90, 0));
	InnerJoint->SetRelativeRotation(FRotator(90,180,180));
	LeftWheelJoint->SetRelativeLocation(FVector(-3,0,0));
	RightWheelJoint->SetRelativeLocation(FVector(-3,0,0));
	RightWheelJoint->SetRelativeRotation(FRotator(0,180,0));
	SmoresController->SetRelativeLocation(FVector(10,29,-24));
	SmoresController->SetRelativeRotation(FRotator(0,-90,0));


	InnerJoint->SetConstrainedComponents(SmoresInner, FName("SmoresInner"), SmoresOuter, FName("SmoresOuter"));
	InnerJoint->SetDisableCollision(true);
	BackWheelJoint->SetConstrainedComponents(SmoresInner, FName("SmoresInner"), WheelBack, FName("WheelBack"));
	BackWheelJoint->SetDisableCollision(true);
	LeftWheelJoint->SetConstrainedComponents(SmoresOuter, FName("SmoresOuter"), WheelLeft, FName("WheelLeft"));
	LeftWheelJoint->SetDisableCollision(true);
	RightWheelJoint->SetConstrainedComponents(SmoresOuter, FName("SmoresOuter"), WheelRight, FName("WheelRight"));
	RightWheelJoint->SetDisableCollision(true);


	//InnerJoint->ConstraintInstance.bAngularOrientationDrive = true;
	//InnerJoint->ConstraintInstance.bAngularVelocityDrive = false;
	//InnerJoint->ConstraintInstance.bEnableProjection = true;
	InnerJoint->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	InnerJoint->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	InnerJoint->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	InnerJoint->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0);
	InnerJoint->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	InnerJoint->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	//InnerJoint->ConstraintInstance.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	//InnerJoint->ConstraintInstance.ProjectionAngularTolerance = 0.0001;
	//InnerJoint->ConstraintInstance.ProjectionLinearTolerance = 0.0001;

	InnerJoint->SetAngularDriveParams(800000, 800000, 5000.0);
	InnerJoint->SetAngularOrientationTarget(FRotator(0, 0, 0));

	//BackWheelJoint->ConstraintInstance.bAngularOrientationDrive = false;
	//BackWheelJoint->ConstraintInstance.bAngularVelocityDrive = true;
	//BackWheelJoint->ConstraintInstance.bEnableProjection = true;
	BackWheelJoint->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	BackWheelJoint->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	BackWheelJoint->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	BackWheelJoint->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0);
	BackWheelJoint->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	BackWheelJoint->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	//BackWheelJoint->ConstraintInstance.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	//BackWheelJoint->ConstraintInstance.ProjectionAngularTolerance = 0.0001;
	//BackWheelJoint->ConstraintInstance.ProjectionLinearTolerance = 0.0001;

	BackWheelJoint->SetAngularDriveParams(10, 1000, 2000000);

	//LeftWheelJoint->ConstraintInstance.bAngularOrientationDrive = false;
	//LeftWheelJoint->ConstraintInstance.bAngularVelocityDrive = true;
	//LeftWheelJoint->ConstraintInstance.bEnableProjection = true;
	LeftWheelJoint->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	LeftWheelJoint->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	LeftWheelJoint->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	LeftWheelJoint->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0);
	LeftWheelJoint->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	LeftWheelJoint->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	//LeftWheelJoint->ConstraintInstance.ProjectionAngularTolerance = 0.0001;
	//LeftWheelJoint->ConstraintInstance.ProjectionLinearTolerance = 0.0001;
	//LeftWheelJoint->ConstraintInstance.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	LeftWheelJoint->SetAngularDriveParams(2000, 1000, 2000000);
	LeftWheelJoint->SetAngularVelocityTarget(FVector(0.35,0,0));

	//RightWheelJoint->ConstraintInstance.bAngularOrientationDrive = false;
	//RightWheelJoint->ConstraintInstance.bAngularVelocityDrive = true;
	//RightWheelJoint->ConstraintInstance.bEnableProjection = true;
	RightWheelJoint->ConstraintInstance.SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	RightWheelJoint->ConstraintInstance.SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	RightWheelJoint->ConstraintInstance.SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	RightWheelJoint->ConstraintInstance.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0);
	RightWheelJoint->ConstraintInstance.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	RightWheelJoint->ConstraintInstance.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	//RightWheelJoint->ConstraintInstance.ProjectionAngularTolerance = 0.0001;
	//RightWheelJoint->ConstraintInstance.ProjectionLinearTolerance = 0.0001;
	//RightWheelJoint->ConstraintInstance.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	RightWheelJoint->SetAngularDriveParams(2000, 1000, 2000000);
	RightWheelJoint->SetAngularVelocityTarget(FVector(0.35,0,0));



	SmoresInner->BodyInstance.PositionSolverIterationCount = 255;
	SmoresInner->BodyInstance.VelocitySolverIterationCount = 255;

	SmoresInner->BodyInstance.bOverrideMass = true;
	SmoresInner->BodyInstance.SetMassOverride(smores_mass_inner);

	WheelBack->BodyInstance.PositionSolverIterationCount = 255;
	WheelBack->BodyInstance.VelocitySolverIterationCount = 255;

	WheelBack->BodyInstance.bOverrideMass = true;
	WheelBack->BodyInstance.SetMassOverride(smores_mass_wheel);

	WheelLeft->BodyInstance.PositionSolverIterationCount = 255;
	WheelLeft->BodyInstance.VelocitySolverIterationCount = 255;

	WheelLeft->BodyInstance.bOverrideMass = true;
	WheelLeft->BodyInstance.SetMassOverride(smores_mass_wheel);

	WheelRight->BodyInstance.PositionSolverIterationCount = 255;
	WheelRight->BodyInstance.VelocitySolverIterationCount = 255;

	WheelRight->BodyInstance.bOverrideMass = true;
	WheelRight->BodyInstance.SetMassOverride(smores_mass_wheel);

	SmoresOuter->BodyInstance.PositionSolverIterationCount = 255;
	SmoresOuter->BodyInstance.VelocitySolverIterationCount = 255;

	SmoresOuter->BodyInstance.bOverrideMass = true;
	SmoresOuter->BodyInstance.SetMassOverride(smores_mass_outer);

	SmoresController->BodyInstance.PositionSolverIterationCount = 255;
	SmoresController->BodyInstance.VelocitySolverIterationCount = 255;

	SmoresController->BodyInstance.bOverrideMass = true;
	SmoresController->BodyInstance.SetMassOverride(0.001);

	SmoresInner->SetMobility(EComponentMobility::Movable);
	WheelBack->SetMobility(EComponentMobility::Movable);
	WheelLeft->SetMobility(EComponentMobility::Movable);
	WheelRight->SetMobility(EComponentMobility::Movable);
	SmoresOuter->SetMobility(EComponentMobility::Movable);
	SmoresController->SetMobility(EComponentMobility::Movable);

	curJoints.Motor0Angle = 0;
	curJoints.Motor1Angle = 0;
	curJoints.Motor2Angle = 0;
	//SetJointAngles(ModuleMotorVector(0, 0, 0));
	std::stringstream ss;
	ss << "SuperBot";
	//ss << numSuperBotMods;
	//this->name = ss.str();
	/////numSuperBotMods++;
}
// Called when the game starts or when spawned
void ASmoresModule::BeginPlay()
{
	Super::BeginPlay();
	SmoresController->AttachToComponent(SmoresInner, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
}

// Called every frame
void ASmoresModule::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

