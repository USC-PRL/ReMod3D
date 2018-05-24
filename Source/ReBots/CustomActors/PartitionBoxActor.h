// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "PartitionBoxActor.generated.h"
/**
 * @enum BoxColor
 * @brief color of box
 */
enum BoxColor {
    BlueBoxColor = 0,
    YellowBoxColor = 1,
    OrangeBoxColor = 2
};
/**
 * @class APartitionBoxActor
 * @brief represents the visualization of a partition box
 */
UCLASS()
class REBOTS_API APartitionBoxActor : public AActor
{
	GENERATED_BODY()
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartitionBoxBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* Box; /**< z axis */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartitionBoxBody, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* SharedRoot; /**< z axis */
    FVector Scale; /** < actor scale in X, Y, Z*/
    FVector Extents; /**< 3d size of box */
    UMaterial* OrangeMaterial; /**< red material */
    UMaterial* BlueMaterial; /**< blue material */
    UMaterial* YellowMaterial;/**< yellow material */
public:
    /**
     * @brief constructor
     */
    APartitionBoxActor();
    /**
     * @brief set box extents
     * @param E extents
     */
    void SetBoxExtents(FVector E);
    /**
     * @brief get box extents
     * @return box extents
     */
    FVector GetBoxExtents();
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
