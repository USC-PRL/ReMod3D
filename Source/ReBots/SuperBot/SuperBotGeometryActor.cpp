// Fill out your copyright notice in the Description page of Project Settings.

 
#include "SuperBotGeometryActor.h"


// Sets default values
ASuperBotGeometryActor::ASuperBotGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    Scale = FVector(0.75,0.75,1.0);
    JAngles = ModuleMotorVector(0,0,0);
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    cubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    BTMaterial(TEXT("/Game/SuperBotMaterials/BlueTrans.BlueTrans"));
    UMaterial * BlueTransMaterial = NULL;
    if (BTMaterial.Object != NULL){BlueTransMaterial = (UMaterial*)BTMaterial.Object;}
    SharedRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SharedRootGeom"));
    InnerBoxMaster = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InnerMaster"));
    InnerBoxMaster->SetMobility(EComponentMobility::Movable);
    InnerBoxMaster->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    
    InnerBoxMaster->SetStaticMesh(cubeMesh.Object);
    InnerBoxMaster->SetWorldScale3D(FVector(Scale.X,Scale.Y,Scale.Z));
    
    InnerBoxMaster->SetRelativeLocation(FVector(0,0,-50*Scale.Z));
    InnerBoxMaster->SetSimulatePhysics(false);
    
    RootComponent = SharedRootComponent;
    InnerBoxMaster->AttachTo(SharedRootComponent);
    
    InnerBoxMaster->SetMaterial(0, BlueTransMaterial);
}

// Called when the game starts or when spawned
void ASuperBotGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuperBotGeometryActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

