// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Framework/ModuleDockFace.h"
#include "Framework/ModuleDock.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Framework/ModularRobot.h"
#include "CustomActors/DockCollisionActor.h"
#include "FloorCollisionActor.generated.h"
/**
 * @class AFloorCollisionActor
 * @brief represents a collision with the floor
 */
UCLASS()
class REBOTS_API AFloorCollisionActor : public AActor
{
    GENERATED_BODY()
    bool CurrentlyOverlapping = false; /**< currently overlapping actors ? */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* BoxComponent; /**< box component */
    FVector BoxExtents; /**< box extents */
    ADockCollisionActor *CollidingActor; /**< colliding actor */
    float waitForSeconds = 2.0; /**< wait until after this time to start recording overlaps again */
public:
    /**
     * @brief begin collision overlap
     * @param OtherActor the other actor involved in the collision
     * @param OtherComp the other component involved in the collision
     * @param OtherBodyIndex index of the other body
     * @param bFromSweep overlap invoked from sweep?
     * @param SweepResult result of sweep
     */
    UFUNCTION()
    void StartOverlap(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    /**
     * @brief initialization
     */
    void Init();
    /**
     * @brief constructor
     */
    AFloorCollisionActor();
    /**
     * @brief begin play for this actor
     */
    virtual void BeginPlay() override;
    /**
     * @brief tick the actor
     */
    virtual void Tick( float DeltaSeconds ) override;
};
