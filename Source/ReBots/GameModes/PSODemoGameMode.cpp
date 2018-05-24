 
#include "PSODemoGameMode.h"
#include <sstream>
using namespace std;
/**
 * @brief game mode constructor
 * @param ObjectInitializer initializer
 */
APSODemoGameMode::APSODemoGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PS = new PSOParticleSwarm(200, 50, 2);
    //PS.SetFitnessFunction(std::bind(&APSODemoGameMode::Fitness,this, std::placeholders::_1));
    //PS.SetAlphaAndBeta(0.7,0.5);
    this->ProgramCounter = 0;
}
/**
 * @brief tick game mode
 * @param DeltaSeconds amount of time elapsed
 */
void APSODemoGameMode::Tick(float DeltaSeconds) {
    if (ProgramCounter == 0) {
        std::vector<std::pair<float,float> > pBounds(2); pBounds[0] = std::pair<float,float>(-3000,3000); pBounds[1] = std::pair<float,float>(-3000,3000);
        std::vector<std::pair<float,float> > vBounds(2); vBounds[0] = std::pair<float,float>(-10,10); vBounds[1] = std::pair<float,float>(-10,10);
        std::vector<float> tar {0,0};
        PS->initializeSwarm(pBounds, vBounds, pBounds, vBounds, 0.001,
                            MODE_CONSTRICTION, std::bind(&APSODemoGameMode::Fitness,this,std::placeholders::_1,std::placeholders::_2,
                                                         std::placeholders::_3),tar,tar);
        for (int i=0; i<PS->getNumParticles(); i++) {
            FTransform t = FTransform(FVector(PS->getBestParticleAtIndex(i).getPositionAtIndex(0),
                                              PS->getBestParticleAtIndex(i).getPositionAtIndex(1),2000));
            float partFit = Fitness(PS->getParticleAtIndex(i), tar, tar);
            t.SetLocation(FVector(FVector(PS->getBestParticleAtIndex(i).getPositionAtIndex(0),
                                          PS->getBestParticleAtIndex(i).getPositionAtIndex(1),5075-partFit)));
            AParticleActor* A = GetWorld()->SpawnActor<AParticleActor>(t.GetLocation(),FRotator(t.GetRotation()));
            PActors.push_back(A);
            /*if (i == PS.GetGlobalBestIndex()) {
                A->ChangeMaterialToBest();
            } else {
                A->ResetMaterialToDefault();
            }*/
            std::string bFitString = "Current best fitness: ";
            std::stringstream ss;
            ss << PS->getGlobalBestFitness();
            bFitString.append(ss.str());
            FString bFit = FString(bFitString.c_str());
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, bFit);

        }
        FTransform bestt = FTransform(FVector(PS->getGlobalBestParticle().getPositionAtIndex(0),
                                          PS->getGlobalBestParticle().getPositionAtIndex(1),2000));
        float partFit = Fitness(PS->getGlobalBestParticle(),tar, tar);
        bestt.SetLocation(FVector(FVector(PS->getGlobalBestParticle().getPositionAtIndex(0),
                                      PS->getGlobalBestParticle().getPositionAtIndex(1),5075-partFit)));
        AParticleActor* A = GetWorld()->SpawnActor<AParticleActor>(bestt.GetLocation(),FRotator(bestt.GetRotation()));
        PActors.push_back(A);
        PActors[PActors.size() -1]->ChangeMaterialToBest();
    } else if (ProgramCounter != 0){
        PS->updateSwarm();
        std::vector<float> tar {0,0};
        for (int i=0; i<PS->getNumParticles(); i++) {
            FTransform t = FTransform(FVector(PS->getBestParticleAtIndex(i).getPositionAtIndex(0),
                                              PS->getBestParticleAtIndex(i).getPositionAtIndex(1),2000));
            float partFit = Fitness(PS->getParticleAtIndex(i), tar, tar);
            t.SetLocation(FVector(FVector(PS->getBestParticleAtIndex(i).getPositionAtIndex(0),
                                          PS->getBestParticleAtIndex(i).getPositionAtIndex(1),5075-partFit)));
            PActors[i]->GetRootComponent()->SetWorldLocation(t.GetLocation());
            /*if (i == PS.GetGlobalBestIndex()) {
                PActors[i]->ChangeMaterialToBest();
            } else {
                PActors[i]->ResetMaterialToDefault();
            }*/
        }
        FTransform bestt = FTransform(FVector(PS->getGlobalBestParticle().getPositionAtIndex(0),
                                              PS->getGlobalBestParticle().getPositionAtIndex(1),2000));
        float partFit = Fitness(PS->getGlobalBestParticle(),tar,tar);
        bestt.SetLocation(FVector(FVector(PS->getGlobalBestParticle().getPositionAtIndex(0),
                                      PS->getGlobalBestParticle().getPositionAtIndex(1),5075-partFit)));
        PActors[PActors.size() - 1]->GetRootComponent()->SetWorldLocation(bestt.GetLocation());
        PActors[PActors.size() -1]->ChangeMaterialToBest();
        std::string bFitString = "Current best fitness: ";
        std::stringstream ss;
        ss << PS->getGlobalBestFitness();
        bFitString.append(ss.str());
        FString bFit = FString(bFitString.c_str());
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, bFit);
    }
    ProgramCounter++;
}
/**
 * @brief fitness for particle
 * @param P particle
 * @return fitness of particle
 */
float APSODemoGameMode::Fitness(PSOParticle P, std::vector<float> st, std::vector<float> tar) {
    FHitResult HitR(ForceInit);
    PSOParticleFitness partFit = PSOParticleFitness();
    bool tHit = Trace(GetWorld(),NULL,FVector(P.getPosition()[0],P.getPosition()[1],5000),FVector(P.getPosition()[0],P.getPosition()[1],0),HitR);
    return HitR.Distance;
}
/**
 * @brief perform a line trace query
 * @param World world in which to perform query
 * @param array of actors to ignore during query
 * @param Start starting vector
 * @param End ending vector
 * @param HitOut hit result
 * @param CollisionChannel collision channel
 * @param ReturnPhysMat return physical material hit
 * @return whether or not anything was hit
 */
bool APSODemoGameMode::Trace(UWorld* World,AActor* ActorToIgnore,const FVector& Start,const FVector& End, FHitResult& HitOut,
                             ECollisionChannel CollisionChannel, bool ReturnPhysMat) {
    if(!World) {return false;}
    FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
    TraceParams.bTraceComplex = true;
    TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;
    if (ActorToIgnore) TraceParams.AddIgnoredActor(ActorToIgnore);
    HitOut = FHitResult(ForceInit);
    World->LineTraceSingleByChannel(HitOut,Start,End,CollisionChannel,TraceParams);
    return (HitOut.GetActor() != NULL);
}
