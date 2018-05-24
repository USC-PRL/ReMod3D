// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "BBPSO/BranchBoundPartition.h"
#include "BBPSO/BranchBoundParticle.h"
#include "CustomActors/ParticleActor.h"
#include "CustomActors/PartitionBoxActor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "BBPSO/BranchBoundParticleSwarm.h"
#include "BBPSO/BranchBoundPSO.h"
#include "BranchBoundTestGameMode.generated.h"
/**
 * @class ABranchBoundTestGameMode
 * @brief branch bound testing game mode
 */
UCLASS()
class REBOTS_API ABranchBoundTestGameMode : public AGameMode
{
	GENERATED_BODY()
private:
    int ProgramCounter; /**< program counter */
    int CurrentDepth = 0; /**< current depth */
    std::vector<AParticleActor*> PartitionCenters; /**< partition centers */
    std::vector<APartitionBoxActor*> PartitionBoxes; /**< partition boxes */
    BranchBoundParticleSwarm *PS; /**< particle swarm for BB PSO*/
    std::vector<AParticleActor*> ParticleActors; /**< particle actors */
    BranchBoundPSO BBPSO; /**< branch and bound pso */
public:
    /**
     * @brief fitness function for PSO
     * @param P particle
     * @param T target vector
     * @return fitness value
     */
    float Fitness(BranchBoundParticle P, std::vector<float> ST, std::vector<float> T);
    /**
     * @brief game mode constructor
     * @param ObjectInitializer initializer
     */
    ABranchBoundTestGameMode(const FObjectInitializer& ObjectInitializer);
    /**
     * @brief recursively subdivide space to depth
     * @param Partition branch bound partition
     * @param currentDepth current depth of procedure
     * @param depthLimit depth at which to stop subdivision
     */
    void RecursivelySubdivideSpaceToDepth(BranchBoundPartition Partition, int currentDepth, int depthLimit);
    /**
     * @brief advance the simulation
     * @param DeltaSeconds fraction of a second by which to advance simulation
     */
    virtual void Tick( float DeltaSeconds ) override;
	
};
