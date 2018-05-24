// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "ParticleActor.generated.h"
/**
 * @class AParticleActor
 * @brief represents a particle visualization
 */
UCLASS()
class REBOTS_API AParticleActor : public AActor
{
	GENERATED_BODY()
private:
    UMaterial* RedMaterial; /**< red color material */
    UMaterial* BlueMaterial; /**< blue color material */
    FVector Scale; /**< 3d scale of particle */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ParticleBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* Sphere; /**< z axis */
    class USceneComponent* SharedRoot; /**< root component */
public:
	/**
     * @brief constructor
     */
	AParticleActor();
    /**
     * @brief set particle scale
     * @param particle scale
     */
    void SetParticleScale(FVector s);
    /**
     * @brief get particle scale
     * @return particle scale
     */
    FVector GetParticleScale();
    /**
     * @brief change material for best particle
     */
    void ChangeMaterialToBest();
    /**
     * @brief reset material to default
     */
    void ResetMaterialToDefault();
	/**
     * @brief begin play for component
     */
	virtual void BeginPlay() override;
    /**
     * @brief tick actor
     * @param DeltaTime change in time
     */
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
