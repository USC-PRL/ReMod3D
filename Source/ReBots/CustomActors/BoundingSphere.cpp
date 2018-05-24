// Fill out your copyright notice in the Description page of Project Settings.

 
#include "BoundingSphere.h"


// Sets default values
ABoundingSphere::ABoundingSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
    Scale = FVector(1.5,1.5,1.5);
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
    cubeMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
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
    Sphere->SetMobility(EComponentMobility::Movable);
    Sphere->SetWorldScale3D(FVector(Scale.X,Scale.Y,Scale.Z));
    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Sphere->SetMaterial(0,BlueMaterial);
    Sphere->bIsActive = true;
    Sphere->SetHiddenInGame(false);
    Sphere->SetVisibility(true);
    Sphere->SetStaticMesh(cubeMesh.Object);
    Sphere->SetRelativeLocation(FVector(0,0,-50*Scale.Z));
    RootComponent = Sphere;
}
/**
 * @brief set color
 * @param C sphere color
 */
void ABoundingSphere::SetColor(SphereColor C) {
    UMaterial* Mat = NULL;
    if (C == OrangeColor) {
        Mat = OrangeMaterial;
    } else if (C == BlueColor) {
        Mat = BlueMaterial;
    } else if (C == YellowColor) {
        Mat = YellowMaterial;
    }
    Sphere->SetMaterial(0, Mat);
}

// Called when the game starts or when spawned
void ABoundingSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoundingSphere::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

