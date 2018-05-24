// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ReferenceFrameActor.h"


// Sets default values
AReferenceFrameActor::AReferenceFrameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    pipeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    coneMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    sphereMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    RMaterial(TEXT("/Game/SuperBotMaterials/RedMaterial.RedMaterial"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    BMaterial(TEXT("/Game/SuperBotMaterials/BlueMaterial.BlueMaterial"));
    static ConstructorHelpers::FObjectFinder<UMaterial>
    GMaterial(TEXT("/Game/SuperBotMaterials/GreenMaterial.GreenMaterial"));
    UMaterial* BlueMaterial = NULL;
    if (BMaterial.Object != NULL){BlueMaterial = (UMaterial*)BMaterial.Object;}
    UMaterial* GreenMaterial = NULL;
    if (GMaterial.Object != NULL){GreenMaterial = (UMaterial*)GMaterial.Object;}
    UMaterial* RedMaterial = NULL;
    if (RMaterial.Object != NULL){RedMaterial = (UMaterial*)RMaterial.Object;}
    SharedRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SharedRoot"));
    RootComponent = SharedRootComponent;
    ZAxis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZAxis"));
    ZAxis->SetStaticMesh(pipeMesh.Object);
    ZAxis->SetMaterial(0, BlueMaterial);
    ZAxis->SetRelativeTransform(FTransform(FQuat(FVector(1,0,0),M_PI/2.0),FVector(0.0,2.25,35.0)));
    ZAxis->SetWorldScale3D(FVector(0.15,0.7,0.15));
    ZAxis->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ZAxis->SetMobility(EComponentMobility::Movable);
    ZAxis->AttachTo(SharedRootComponent);
    XAxis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XAxis"));
    XAxis->SetStaticMesh(pipeMesh.Object);
    XAxis->SetMaterial(0, RedMaterial);
    XAxis->SetRelativeTransform(FTransform(FQuat(FVector(0,0,1),M_PI/2.0),FVector(35.0,0.0,-2.25)));
    XAxis->SetWorldScale3D(FVector(0.15,0.7,0.15));
    XAxis->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    XAxis->SetMobility(EComponentMobility::Movable);
    XAxis->AttachTo(SharedRootComponent);
    YAxis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YAxis"));
    YAxis->SetStaticMesh(pipeMesh.Object);
    YAxis->SetMaterial(0, GreenMaterial);
    YAxis->SetRelativeTransform(FTransform(FVector(0.0,35.0,-2.25)));
    YAxis->SetWorldScale3D(FVector(0.15,0.7,0.15));
    YAxis->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    YAxis->SetMobility(EComponentMobility::Movable);
    YAxis->AttachTo(SharedRootComponent);
    ZCap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZAxisCap"));
    ZCap->SetStaticMesh(coneMesh.Object);
    ZCap->SetMaterial(0, BlueMaterial);
    ZCap->SetRelativeTransform(FTransform(FQuat(FVector(1,0,0),0),FVector(0.0,0.0,70.0)));
    ZCap->SetWorldScale3D(FVector(0.08,0.08,0.08));
    ZCap->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ZCap->SetMobility(EComponentMobility::Movable);
    ZCap->AttachTo(SharedRootComponent);
    XCap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XAxisCap"));
    XCap->SetStaticMesh(coneMesh.Object);
    XCap->SetMaterial(0, RedMaterial);
    XCap->SetRelativeTransform(FTransform(FQuat(FVector(0,1,0),M_PI/2.0),FVector(70.0,0.0,0.0)));
    XCap->SetWorldScale3D(FVector(0.08,0.08,0.08));
    XCap->SetMobility(EComponentMobility::Movable);
    XCap->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    XCap->AttachTo(SharedRootComponent);
    YCap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YAxisCap"));
    YCap->SetStaticMesh(coneMesh.Object);
    YCap->SetMaterial(0, GreenMaterial);
    YCap->SetRelativeTransform(FTransform(FQuat(FVector(1,0,0),-M_PI/2.0),FVector(0.0,70.0,0.0)));
    YCap->SetWorldScale3D(FVector(0.08,0.08,0.08));
    YCap->SetMobility(EComponentMobility::Movable);
    YCap->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    YCap->AttachTo(SharedRootComponent);
    OriginSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OriginSphere"));
    OriginSphere->SetStaticMesh(sphereMesh.Object);
    OriginSphere->SetRelativeTransform(FTransform(FVector(0.0,0.0,-4.0)));
    OriginSphere->SetWorldScale3D(FVector(0.08, 0.08, 0.08));
    OriginSphere->SetMobility(EComponentMobility::Movable);
    OriginSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    OriginSphere->AttachTo(SharedRootComponent);
    XAxis->SetSimulatePhysics(false);
    YAxis->SetSimulatePhysics(false);
    ZAxis->SetSimulatePhysics(false);
    XCap->SetSimulatePhysics(false);
    YCap->SetSimulatePhysics(false);
    ZCap->SetSimulatePhysics(false);
    OriginSphere->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void AReferenceFrameActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReferenceFrameActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

