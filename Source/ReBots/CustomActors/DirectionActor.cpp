// Fill out your copyright notice in the Description page of Project Settings.

 
#include "DirectionActor.h"


// Sets default values
ADirectionActor::ADirectionActor()
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
    XAxis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XAxis"));
    XAxis->SetStaticMesh(pipeMesh.Object);
    XAxis->SetMaterial(0, RedMaterial);
    XAxis->SetRelativeTransform(FTransform(FQuat(FVector(0,0,1),M_PI/2.0),FVector(35.0,0.0,-2.25)));
    XAxis->SetWorldScale3D(FVector(0.15,0.7,0.15));
    XAxis->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    XAxis->SetMobility(EComponentMobility::Movable);
    XAxis->AttachTo(SharedRootComponent);
    XCap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XAxisCap"));
    XCap->SetStaticMesh(coneMesh.Object);
    XCap->SetMaterial(0, RedMaterial);
    XCap->SetRelativeTransform(FTransform(FQuat(FVector(0,1,0),M_PI/2.0),FVector(70.0,0.0,0.0)));
    XCap->SetWorldScale3D(FVector(0.08,0.08,0.08));
    XCap->SetMobility(EComponentMobility::Movable);
    XCap->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    XCap->AttachTo(SharedRootComponent);
    OriginSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OriginSphere"));
    OriginSphere->SetStaticMesh(sphereMesh.Object);
    OriginSphere->SetRelativeTransform(FTransform(FVector(0.0,0.0,-4.0)));
    OriginSphere->SetWorldScale3D(FVector(0.08, 0.08, 0.08));
    OriginSphere->SetMobility(EComponentMobility::Movable);
    OriginSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    OriginSphere->AttachTo(SharedRootComponent);
    XAxis->SetSimulatePhysics(false);
    XCap->SetSimulatePhysics(false);
    OriginSphere->SetSimulatePhysics(false);
}
/**
 * @brief get yaw
 */
float ADirectionActor::GetYaw() {
    FTransform OriginSphereTransform = OriginSphere->GetComponentTransform();
    OriginSphereTransform.NormalizeRotation();
    return FRotator(OriginSphereTransform.GetRotation()).Yaw;
}
/**
* @brief set the direction
*/
void ADirectionActor::SetDirection(FVector Dir) {
}
/**
 * @brief get the direction
 */
FVector ADirectionActor::GetDirection() {
    return OriginSphere->GetComponentTransform().GetRotation().GetAxisX();
}

// Called when the game starts or when spawned
void ADirectionActor::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ADirectionActor::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}
