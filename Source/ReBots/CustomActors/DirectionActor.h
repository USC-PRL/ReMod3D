// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DirectionActor.generated.h"

UCLASS()
class REBOTS_API ADirectionActor : public AActor
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* XAxis; /**< x axis */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* XCap; /**< x axis cap */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* SharedRootComponent; /**< shared root */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* OriginSphere; /**< z axis */
public:
	/**
	* @brief set the direction
	*/
	void SetDirection(FVector Dir);
    /**
     * @brief get the direction
     */
    FVector GetDirection();
    /**
     * @brief get yaw
     */
    float GetYaw();
    /**
     * @brief constructor
     */
    ADirectionActor();
    /**
     * @brief begin play for actor
     */
    virtual void BeginPlay() override;
    /**
     * @brief tick actor
     * @param DeltaSeconds change in number of seconds
     */
    virtual void Tick( float DeltaSeconds ) override;

	
};
