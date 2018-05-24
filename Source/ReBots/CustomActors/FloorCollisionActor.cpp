#include "FloorCollisionActor.h"
#include "GameModes/ReBotsSimulatorGameMode.h"


/**
 * @brief begin collision overlap
 * @param OtherActor the other actor involved in the collision
 * @param OtherComp the other component involved in the collision
 * @param OtherBodyIndex index of the other body
 * @param bFromSweep overlap invoked from sweep?
 * @param SweepResult result of sweep
 */
void AFloorCollisionActor::StartOverlap(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult) {
    
    if (OtherActor->GetClass() == ADockCollisionActor::StaticClass()) {
        CurrentlyOverlapping = true;
        CollidingActor = (ADockCollisionActor*)OtherActor;
    }
}
/**
 * @brief initialization
 */
void AFloorCollisionActor::Init() {
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorBox"));
    RootComponent = BoxComponent;
    BoxComponent->bHiddenInGame = false;
    BoxComponent->bAutoActivate = true;
    BoxComponent->bIsActive = true;
    BoxComponent->SetVisibility(true);
    BoxComponent->bMultiBodyOverlap = true;
    BoxComponent->bGenerateOverlapEvents = true;
    BoxComponent->SetSimulatePhysics(false);
    BoxComponent->SetMobility(EComponentMobility::Movable);
    BoxComponent->SetBoxExtent(FVector(500,500,7));
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AFloorCollisionActor::StartOverlap);
}
// Sets default values
AFloorCollisionActor::AFloorCollisionActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Init();
    
}

// Called when the game starts or when spawned
void AFloorCollisionActor::BeginPlay()
{
    Super::BeginPlay();
    
}
// Called every frame
void AFloorCollisionActor::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    float seconds = GetWorld()->GetTimeSeconds();
    if (CurrentlyOverlapping && seconds > waitForSeconds && CollidingActor->GetModule()) {
        AReBotsSimulatorGameMode* Mode = (AReBotsSimulatorGameMode*)GetWorld()->GetAuthGameMode();
        ADockCollisionActor* d1 = CollidingActor;
        ASuperBotModule* sm = (ASuperBotModule*)d1->GetModule();
        ModuleDockFace df = d1->GetDockFace();
        
        if ((df == DOCK_0 || df == DOCK_1) && !sm->GetDockEngagedStatus(df)) {
            cout<<"Connect ground to "<<df<<" of module "<<sm->GetName()<<endl;
            CurrentlyOverlapping = false;
            Mode->DockModuleToGround(sm, df);
            CollidingActor = NULL;
            
            waitForSeconds += 2.0;
        }
    }
    
}
