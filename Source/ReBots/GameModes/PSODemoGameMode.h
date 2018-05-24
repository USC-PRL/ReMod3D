// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "PSO/PSOParticle.h"
#include "PSO/PSOParticleSwarm.h"
#include <memory>
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "CustomActors/ParticleActor.h"
#include <functional>
#include "PSODemoGameMode.generated.h"
/**
 * @class PSODemoGameMode
 * @brief pso demo game mode
 */
UCLASS()
class REBOTS_API APSODemoGameMode : public AGameMode
{
	GENERATED_BODY()
private:
    int ProgramCounter; /**< program counter */
    std::vector<AParticleActor*> PActors; /**< particle actors */
    PSOParticleSwarm *PS; /**< particle swarm */
public:
    /**
     * @brief game mode constructor
     * @param ObjectInitializer initializer
     */
    APSODemoGameMode(const FObjectInitializer& ObjectInitializer);
    /**
     * @brief advance the simulation
     * @param DeltaSeconds fraction of a second by which to advance simulation
     */
    virtual void Tick( float DeltaSeconds ) override;
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
    bool Trace(UWorld* World,AActor* ActorToIgnore,const FVector& Start,const FVector& End,FHitResult& HitOut, ECollisionChannel CollisionChannel = ECC_Pawn,
               bool ReturnPhysMat = false);
    /**
     * @brief fitness for particle
     * @param P particle
     * @return fitness of particle
     */
    float Fitness(PSOParticle P,std::vector<float> st, std::vector<float> tar);
	
	
};
