// Fill out your copyright notice in the Description page of Project Settings.

 
#include "StackableObjectActor.h"


// Sets default values
AStackableObjectActor::AStackableObjectActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Scale = FVector(2., 2., 0.25);
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    cubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    RMaterial(TEXT("/Game/SuperBotMaterials/RedMaterial.RedMaterial"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    BMaterial(TEXT("/Game/SuperBotMaterials/BlueMaterial.BlueMaterial"));
    RedMaterial = NULL;
    BlueMaterial = NULL;
    if (RMaterial.Object != NULL) { RedMaterial = (UMaterial*)RMaterial.Object; }
    if (BMaterial.Object != NULL) { BlueMaterial = (UMaterial*)BMaterial.Object; }
    Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ManipBox"));
    SharedRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SharedRoot"));
    RootComponent = SharedRoot;
    RootComponent->SetActive(true);
    Box->AttachTo(RootComponent);
    Box->SetWorldScale3D(FVector(Scale.X, Scale.Y, Scale.Z));
    Box->SetRelativeLocation(FVector(0, 0, -50*Scale.Z));
    Box->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
    Box->SetMaterial(0, RedMaterial);
    Box->SetStaticMesh(cubeMesh.Object);
    Box->SetSimulatePhysics(true);
    Box->BodyInstance.bOverrideMass = true;
    //Box->BodyInstance.MassInKg = 0.2;
    Box->BodyInstance.SetMassOverride(0.05);
    Box->BodyInstance.PositionSolverIterationCount = 255;
    Box->BodyInstance.VelocitySolverIterationCount = 255;
}
/**
 * @brief get box
 * @return box
 */
UStaticMeshComponent* AStackableObjectActor::GetBox() {
    return this->Box;
}
// Called when the game starts or when spawned
void AStackableObjectActor::BeginPlay()
{
    Super::BeginPlay();
    
}
/**
 * @brief get actor transform
 * @return actor transform
 */
FTransform AStackableObjectActor::GetActorTransform() {
    return Box->GetComponentTransform();
}
// Called every frame
void AStackableObjectActor::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

/**
 * @brief set particle scale
 * @param particle scale
 */
void AStackableObjectActor::SetScale(FVector s) {
    this->Scale = s;
}
/**
 * @brief get particle scale
 * @return particle scale
 */
FVector AStackableObjectActor::GetScale() {
    return this->Scale;
}

