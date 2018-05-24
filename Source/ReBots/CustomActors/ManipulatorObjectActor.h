// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "ManipulatorObjectActor.generated.h"

UCLASS()
class REBOTS_API AManipulatorObjectActor : public AActor
{
	GENERATED_BODY()
private:
	UMaterial* RedMaterial; /**< red color material */
	UMaterial* BlueMaterial; /**< blue color material */
	FVector Scale; /**< 3d scale of particle */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ParticleBody, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Box; /**< box of actor */
	class USceneComponent* SharedRoot; /**< root component */
public:	
	// Sets default values for this actor's properties
	AManipulatorObjectActor();
	/**
	* @brief get box
	* @return box
	*/
	UStaticMeshComponent* GetBox();
	/**
	* @brief set particle scale
	* @param particle scale
	*/
	void SetScale(FVector s);
	/**
	* @brief get particle scale
	* @return particle scale
	*/
	FVector GetScale();
	/**
	* @brief get actor transform
	* @return actor transform
	*/
	FTransform GetActorTransform();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
