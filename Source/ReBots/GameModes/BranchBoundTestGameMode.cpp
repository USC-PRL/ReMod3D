// Fill out your copyright notice in the Description page of Project Settings.

 
#include "BranchBoundTestGameMode.h"



/**
 * @brief game mode constructor
 * @param ObjectInitializer initializer
 */
ABranchBoundTestGameMode::ABranchBoundTestGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    this->ProgramCounter = 0;
}
/**
 * @brief recursively subdivide space to depth
 * @param currentDepth current depth of procedure
 * @param depthLimit depth at which to stop subdivision
 */
void ABranchBoundTestGameMode::RecursivelySubdivideSpaceToDepth(BranchBoundPartition Partition, int currentDepth, int depthLimit) {
    /*if (currentDepth > depthLimit) {
        return;
    } else {
        std::vector<BranchBoundPartition*> partitions = Partition.CreatePartitionsWithRule();
        for (int i=0; i<partitions.size(); i++) {
            if (currentDepth == depthLimit) {
                AParticleActor* pActor = NULL;
                APartitionBoxActor* pBActor = NULL;
                PartitionCenters.push_back((pActor = GetWorld()->SpawnActor<AParticleActor>(FVector(partitions[i].GetPartitionCenter()[0],
                                                                                      partitions[i].GetPartitionCenter()[1],
                                                                                      partitions[i].GetPartitionCenter()[2]),FRotator(0,0,0))));
                PartitionBoxes.push_back((pBActor = GetWorld()->SpawnActor<APartitionBoxActor>(FVector(partitions[i].GetPartitionCenter()[0],
                                                                                                  partitions[i].GetPartitionCenter()[1],
                                                                                                  partitions[i].GetPartitionCenter()[2]),FRotator(0,0,0))));
                pBActor->SetBoxExtents(FVector(partitions[i].GetPartitionExtents()[0],partitions[i].GetPartitionExtents()[1],
                                               partitions[i].GetPartitionExtents()[2]));
            }
            RecursivelySubdivideSpaceToDepth(partitions[i], currentDepth +1, depthLimit);
        }
    }*/
}
/**
 * @brief fitness function for PSO
 * @param P particle
 * @param T target vector
 * @return fitness value
 */
float ABranchBoundTestGameMode::Fitness(BranchBoundParticle P, std::vector<float> ST, std::vector<float> T) {
    float totalError  = 0.0;
    for (int i=0; i<P.GetPosition().size(); i++) {
        totalError += (P.GetPosition()[i] - T[i])*(P.GetPosition()[i] - T[i]);
    }
    return totalError;
}
/**
 * @brief tick game mode
 * @param DeltaSeconds amount of time elapsed
 */
void ABranchBoundTestGameMode::Tick(float DeltaSeconds) {
    if (this->ProgramCounter == 0) {
        /*BranchBoundPartition rootPartition = BranchBoundPartition();
        std::vector<std::pair<float,float> > rootBounds;
        rootBounds.push_back(std::pair<float, float>(-500,500));
        rootBounds.push_back(std::pair<float, float>(-500,500));
        rootBounds.push_back(std::pair<float, float>(0,500));
        rootPartition.SetDimension(3);
        rootPartition.SetBoundsPerDimension(rootBounds);
        std::vector<float> extents {1000/2.0,1000/2.0,500/2.0};
        std::vector<float> center {0, 0, 250};
        rootPartition.SetPartitionExtents(extents);
        rootPartition.SetPartitionCenter(center);*/
        //RecursivelySubdivideSpaceToDepth(rootPartition, 0, 1);
        //PS = new BranchBoundParticleSwarm(30,100,3);
        std::vector<std::pair<float,float> > PosBounds {std::pair<float,float>(-500,500), std::pair<float,float>(-500,500), std::pair<float,float>(50,500),
            std::pair<float,float>(-500,500)};
        std::vector<std::pair<float,float> > VelBounds {std::pair<float,float>(-500,500), std::pair<float,float>(-500,500), std::pair<float,float>(-500,500),
            std::pair<float,float>(-500,500)};
        /*PS->InitializeSwarm(PosBounds, VelBounds, 2.0, std::bind(&ABranchBoundTestGameMode::Fitness,this,std::placeholders::_1,std::placeholders::_2),
                            std::vector<float> {0,0,400});
        AParticleActor* PA = GetWorld()->SpawnActor<AParticleActor>(FVector(0,0,200),FRotator(0,0,0));
        for (int i=0; i<PS->GetNumParticles(); i++) {
            ParticleActors.push_back(GetWorld()->SpawnActor<AParticleActor>(FVector(PS->GetParticleAtIndex(i).GetPosition()[0],
                                                                                    PS->GetParticleAtIndex(i).GetPosition()[1],
                                                                                    PS->GetParticleAtIndex(i).GetPosition()[2]),FRotator(0,0,0)));
        }*/
        BBPSO = BranchBoundPSO(50,50,4);
        BBPSO.InitializeBBPSO(PosBounds, VelBounds, 0.1,
                              std::bind(&ABranchBoundTestGameMode::Fitness,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3),std::vector<float> {0,200,400,100},
                              std::vector<float> {0,200,400,100});
        
    } else if (/*!PS->IsSwarmingDone()*/false) {
        /*PS->UpdateSwarm();
        for (int i=0; i<PS->GetNumParticles(); i++) {
            ParticleActors[i]->SetActorLocation(FVector(PS->GetParticleAtIndex(i).GetPosition()[0], PS->GetParticleAtIndex(i).GetPosition()[1],
                                                       PS->GetParticleAtIndex(i).GetPosition()[2]));
        }*/
    } else {
        bool isDone = BBPSO.BBPSOOptimizeStep();
        if (isDone) {
            //cout<<"Done Optimizing"<<endl;
            cout<<"Final Solution "<<BBPSO.GetFinalSolution().GetPosition()[0]<<","<<BBPSO.GetFinalSolution().GetPosition()[1]<<","<<
            BBPSO.GetFinalSolution().GetPosition()[2]<<","<<BBPSO.GetFinalSolution().GetPosition()[3]<<endl;
        }
        //cout<<"Particle: "<<PS->GetGlobalBestParticle().GetPosition()[0]<<","<<PS->GetGlobalBestParticle().GetPosition()[1]<<","<<PS->GetGlobalBestParticle().GetPosition()[2]<<endl;
    }
    this->ProgramCounter++;
}
