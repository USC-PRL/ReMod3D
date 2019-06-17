// Fill out your copyright notice in the Description page of Project Settings.

#include "DockCollisionActor.h"
#include "GameModes/ReBotsModuleGameMode.h"
/**
 * @brief begin collision overlap
 * @param OtherActor the other actor involved in the collision
 * @param OtherComp the other component involved in the collision
 * @param OtherBodyIndex index of the other body
 * @param bFromSweep overlap invoked from sweep?
 * @param SweepResult result of sweep
 */
void ADockCollisionActor::StartOverlap(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    
    if (OtherActor->GetClass() == ADockCollisionActor::StaticClass()) {
        CurrentlyOverlapping = true;
        OtherDockCollision = (ADockCollisionActor*)OtherActor;
    }
}
/**
 * @brief set module
 * @param mod module
 */
void ADockCollisionActor::SetModuleAndDockFace(AModularRobot* mod, ModuleDockFace d) {
    this->Module = mod;
    this->Face = d;
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ADockCollisionActor::StartOverlap);
}
/**
 * @brief get module
 * @return module
 */
AModularRobot* ADockCollisionActor::GetModule() {
    return this->Module;
}
/**
 * @brief initialization
 */
void ADockCollisionActor::Init() {
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    RootComponent = BoxComponent;
    BoxComponent->bHiddenInGame = true;
    BoxComponent->bAutoActivate = true;
    BoxComponent->bIsActive = true;
    BoxComponent->SetVisibility(true);
    BoxComponent->bMultiBodyOverlap = true;
    BoxComponent->SetGenerateOverlapEvents(true);
    BoxComponent->SetSimulatePhysics(false);
    BoxComponent->SetMobility(EComponentMobility::Movable);
    BoxComponent->SetBoxExtent(FVector(10,15,15));
}
/**
 * @brief get dock face
 * @pram return dock face
 */
ModuleDockFace ADockCollisionActor::GetDockFace() {
    return this->Face;
}

// Sets default values
ADockCollisionActor::ADockCollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Init();

}

// Called when the game starts or when spawned
void ADockCollisionActor::BeginPlay()
{
	Super::BeginPlay();
	
}
/**
 * @brief test dock compatibility
 * @param d1
 * @param d2
 * @return d1 and d2 are compatible with each other for docking
 */
bool ADockCollisionActor::TestDockCompatibility(ModuleDockFace d1, ModuleDockFace d2) {
    if (d1 == DOCK_2 && d2 == DOCK_2) {
        return false;
    } else if (d1 == DOCK_2 && d2 == DOCK_3) {
        return false;
    } else if (d1 == DOCK_2 && d2 == DOCK_4) {
        return false;
    } else if (d1 == DOCK_2 && d2 == DOCK_5) {
        return false;
    }
    
    if (d1 == DOCK_3 && d2 == DOCK_2) {
        return false;
    } else if (d1 == DOCK_3 && d2 == DOCK_3) {
        return false;
    } else if (d1 == DOCK_3 && d2 == DOCK_4) {
        return false;
    } else if (d1 == DOCK_3 && d2 == DOCK_5) {
        return false;
    }
    
    if (d1 == DOCK_4 && d2 == DOCK_2) {
        return false;
    } else if (d1 == DOCK_4 && d2 == DOCK_3) {
        return false;
    } else if (d1 == DOCK_4 && d2 == DOCK_4) {
        return false;
    } else if (d1 == DOCK_4 && d2 == DOCK_5) {
        return false;
    }
    
    if (d1 == DOCK_5 && d2 == DOCK_2) {
        return false;
    } else if (d1 == DOCK_5 && d2 == DOCK_3) {
        return false;
    } else if (d1 == DOCK_5 && d2 == DOCK_4) {
        return false;
    } else if (d1 == DOCK_5 && d2 == DOCK_5) {
        return false;
    }
    
    return true;
}
// Called every frame
void ADockCollisionActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    float seconds = GetWorld()->GetTimeSeconds();
    if (CurrentlyOverlapping && seconds > waitForSeconds) {
		if (this->Module && this->OtherDockCollision->GetModule()) {
			if (GetWorld()->GetAuthGameMode()->GetClass() == AReBotsModuleGameMode::StaticClass()) {
				AReBotsModuleGameMode* Mode = (AReBotsModuleGameMode*)GetWorld()->GetAuthGameMode();
				ASuperBotModule* sm1 = (ASuperBotModule*)this->Module;
				ADockCollisionActor* d1 = OtherDockCollision;
				ASuperBotModule* sm2 = (ASuperBotModule*)d1->GetModule();
				ModuleDockFace df1 = this->Face;
				ModuleDockFace df2 = d1->GetDockFace();

				if (sm1->GetDocks()[df1].GetDockEnabled() && !sm1->GetDocks()[df1].GetDockEngaged() &&
					sm2->GetDocks()[df2].GetDockEnabled() && !sm2->GetDocks()[df2].GetDockEngaged() &&
					sm1 != sm2 &&
					TestDockCompatibility(df1, df2)) {
					CurrentlyOverlapping = false;
					OtherDockCollision = NULL;
					Mode->DockTwoModules(sm1, sm2, df1, df2);
					waitForSeconds += 2.0;
				}
			}
		}
    }

}

