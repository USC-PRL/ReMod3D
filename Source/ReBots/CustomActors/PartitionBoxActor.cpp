// Fill out your copyright notice in the Description page of Project Settings.

 
#include "PartitionBoxActor.h"
/**
 * @brief constructor
 */
APartitionBoxActor::APartitionBoxActor() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
    SharedRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SharedRoot"));
    Extents = FVector(1.0,1.0,1.0);
    RootComponent = SharedRoot;
    Scale = FVector(Extents.X,Extents.Y,Extents.Z);
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    cubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    OMaterial(TEXT("/Game/SuperBotMaterials/OrangeTrans.OrangeTrans"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    BMaterial(TEXT("/Game/SuperBotMaterials/BlueTrans.BlueTrans"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    YMaterial(TEXT("/Game/SuperBotMaterials/YellowTrans.YellowTrans"));
    OrangeMaterial = NULL;
    BlueMaterial = NULL;
    YellowMaterial = NULL;
    if (OMaterial.Object != NULL){OrangeMaterial = (UMaterial*)OMaterial.Object;}
    if (BMaterial.Object != NULL){BlueMaterial = (UMaterial*)BMaterial.Object;}
    if (YMaterial.Object != NULL){YellowMaterial = (UMaterial*)YMaterial.Object;}
    Box->AttachTo(SharedRoot);
    Box->SetMobility(EComponentMobility::Movable);
    Box->SetWorldScale3D(FVector(Scale.X,Scale.Y,Scale.Z));
    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetMaterial(0,BlueMaterial);
    Box->bIsActive = true;
    Box->SetHiddenInGame(false);
    Box->SetVisibility(true);
    Box->SetStaticMesh(cubeMesh.Object);
    Box->SetRelativeLocation(FVector(0,0,-50*Scale.Z));
}
/**
 * @brief set box extents
 * @param E extents
 */
void APartitionBoxActor::SetBoxExtents(FVector E) {
    this->Extents = E;
    Box->SetWorldScale3D(FVector(0.02*this->Extents.X,0.02*this->Extents.Y,0.02*this->Extents.Z));
    Box->SetRelativeLocation(FVector(Box->GetRelativeTransform().GetLocation().X*0.02*Extents.X,
                             Box->GetRelativeTransform().GetLocation().Y*0.02*Extents.Y,
                             Box->GetRelativeTransform().GetLocation().Z*0.02*Extents.Z));
}
/**
 * @brief get box extents
 * @return box extents
 */
FVector APartitionBoxActor::GetBoxExtents() {
    return this->Extents;
}
/**
 * @brief begin play for component
 */
void APartitionBoxActor::BeginPlay() {
    Super::BeginPlay();
}
/**
 * @brief tick actor
 * @param DeltaTime change in time
 */
void APartitionBoxActor::Tick( float DeltaSeconds ) {
    Super::Tick(DeltaSeconds);
}

