// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BoundingSphere.generated.h"
/**
 * @enum SphereColor
 * @brief color of sphere
 */
enum SphereColor {
    OrangeColor = 0,
    BlueColor = 1,
    YellowColor = 2
};
/**
 * @class ABoundingSphere
 * @brief bounding sphere around some object
 */
UCLASS()
class REBOTS_API ABoundingSphere : public AActor
{
	GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BoundingSphereBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* Sphere; /**< sphere mesh */
    FVector Scale; /** < actor scale in X, Y, Z*/
    UMaterial* OrangeMaterial; /**< red material */
    UMaterial* BlueMaterial; /**< blue material */
    UMaterial* YellowMaterial;/**< yellow material */
public:
	/**
     * @brief constructor
     */
	ABoundingSphere();
	/**
     * @brief begin play
     */
	virtual void BeginPlay() override;
    /**
     * @brief tick component
     * @param DeltaSeconds time change in seconds
     */
	virtual void Tick( float DeltaSeconds ) override;
    /**
     * @brief set color
     * @param C sphere color
     */
    void SetColor(SphereColor C);
	
	
};
