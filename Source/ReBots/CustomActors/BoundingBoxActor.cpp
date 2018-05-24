// Fill out your copyright notice in the Description page of Project Settings.

 
#include "BoundingBoxActor.h"


// Sets default values
ABoundingBoxActor::ABoundingBoxActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
    SharedRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SharedRoot"));
    Scale = FVector(1.0,1.0,1.0);
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
    Box->SetMobility(EComponentMobility::Movable);
    Box->SetWorldScale3D(FVector(Scale.X,Scale.Y,Scale.Z));
    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetMaterial(0,BlueMaterial);
    Box->bIsActive = true;
    Box->SetHiddenInGame(false);
    Box->SetVisibility(true);
    Box->SetStaticMesh(cubeMesh.Object);
    Box->SetRelativeLocation(FVector(0,0,-50.0*Scale.Z));
    RootComponent = SharedRoot;
    Box->AttachTo(SharedRoot);
}
/**
 * @brief set 3d scale
 * @param SC 3d scale
 */
void ABoundingBoxActor::SetScale(FVector SC) {
    Box->SetWorldScale3D(FVector(SC.X, SC.Y, SC.Z));
    Box->SetRelativeLocation(FVector(0,0,-50*SC.Z));
}
/**
 * @brief set color
 * @param C sphere color
 */
void ABoundingBoxActor::SetColor(BoundingBoxColor C) {
    UMaterial* Mat = NULL;
    if (C == OrangeBoundingBoxColor) {
        Mat = OrangeMaterial;
    } else if (C == BlueBoundingBoxColor) {
        Mat = BlueMaterial;
    } else if (C == YellowBoundingBoxColor) {
        Mat = YellowMaterial;
    }
    Box->SetMaterial(0, Mat);
}

// Called when the game starts or when spawned
void ABoundingBoxActor::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ABoundingBoxActor::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}
