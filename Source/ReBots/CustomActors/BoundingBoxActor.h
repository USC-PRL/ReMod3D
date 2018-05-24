// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BoundingBoxActor.generated.h"
/**
 * @enum BoundingBoxColor
 * @brief color of the bounding box
 */
enum BoundingBoxColor {
    OrangeBoundingBoxColor = 0,
    BlueBoundingBoxColor = 1,
    YellowBoundingBoxColor = 2
};
/**
 * @class ABoundingBoxActor
 * @brief visualization of bounding box around module parts
 */
UCLASS()
class REBOTS_API ABoundingBoxActor : public AActor
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
	ABoundingBoxActor();
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
	virtual void Tick( float DeltaSeconds ) override;
    /**
     * @brief set color
     * @param C box color
     */
    void SetColor(BoundingBoxColor C);
	
	
};
