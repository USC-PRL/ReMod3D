// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ParticleActor.h"
/**
 * @brief constructor
 */
AParticleActor::AParticleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    Scale = FVector(0.75,0.75,0.75);
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    cubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    RMaterial(TEXT("/Game/SuperBotMaterials/RedMaterial.RedMaterial"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    BMaterial(TEXT("/Game/SuperBotMaterials/BlueMaterial.BlueMaterial"));
    RedMaterial = NULL;
    BlueMaterial = NULL;
    if (RMaterial.Object != NULL){RedMaterial = (UMaterial*)RMaterial.Object;}
    if (BMaterial.Object != NULL){BlueMaterial = (UMaterial*)BMaterial.Object;}
    Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
    SharedRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SharedRoot"));
    this->SetActorEnableCollision(false);
    RootComponent = SharedRoot;
    Sphere->AttachTo(RootComponent);
    Sphere->SetMobility(EComponentMobility::Movable);
    Sphere->SetWorldScale3D(FVector(Scale.X,Scale.Y,Scale.Z));
    Sphere->SetRelativeLocation(FVector(0,0,-50*Scale.Z));
    Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Sphere->SetMaterial(0,RedMaterial);
    Sphere->bIsActive = true;
    Sphere->SetHiddenInGame(false);
    Sphere->SetVisibility(true);
    Sphere->SetStaticMesh(cubeMesh.Object);
}
/**
 * @brief set particle scale
 * @param particle scale
 */
void AParticleActor::SetParticleScale(FVector s) {
    this->Scale = s;
}
/**
 * @brief get particle scale
 * @return particle scale
 */
FVector AParticleActor::GetParticleScale() {
    return this->Scale;
}
/**
 * @brief change material for best particle
 */
void AParticleActor::ChangeMaterialToBest() {
    ((UStaticMeshComponent*)RootComponent)->SetMaterial(0,BlueMaterial);
}
/**
 * @brief reset material to default
 */
/**
 * @brief change material for best particle
 */
void AParticleActor::ResetMaterialToDefault() {
    ((UStaticMeshComponent*)RootComponent)->SetMaterial(0,RedMaterial);
}
/**
 * @brief begin play for actor
 */
void AParticleActor::BeginPlay()
{
	Super::BeginPlay();
	
}
/**
 * @brief tick actor
 * @param DeltaTime change in time
 */
void AParticleActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

