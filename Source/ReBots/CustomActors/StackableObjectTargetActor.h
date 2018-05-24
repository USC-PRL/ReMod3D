// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "StackableObjectTargetActor.generated.h"
/**
* @enum BoundingBoxColor
* @brief color of the bounding box
*/
enum StackableTargetColor {
	OrangeTargetColor = 0,
	BlueTargetColor = 1,
	YellowTargetColor = 2
};
UCLASS()
class REBOTS_API AStackableObjectTargetActor : public AActor
{
	GENERATED_BODY()
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BoundingSphereBody, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Box; /**< box mesh */
	class USceneComponent* SharedRoot; /**< root component */
	FVector Scale; /** < actor scale in X, Y, Z*/
	UMaterial* OrangeMaterial; /**< red material */
	UMaterial* BlueMaterial; /**< blue material */
	UMaterial* YellowMaterial;/**< yellow material */
public:
	/**
	* @brief constructor
	*/
	AStackableObjectTargetActor();
	/**
	* @brief set 3d scale
	* @param SC 3d scale
	*/
	void SetScale(FVector SC);
	/**
	* @brief called when simulation begins for this actor
	*/
	virtual void BeginPlay() override;
	/**
	* @brief called at every tick for this actor
	* @param DeltaSeconds amount of time that has passed
	*/
	virtual void Tick(float DeltaSeconds) override;
	/**
	* @brief set color
	* @param C box color
	*/
	void SetColor(StackableTargetColor C);
	
};
