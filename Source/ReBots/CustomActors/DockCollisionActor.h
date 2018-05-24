// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Framework/ModuleDock.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Framework/ModularRobot.h"
#include "Framework/ModuleDockFace.h"
#include "DockCollisionActor.generated.h"
/**
 * @class ADockCollisionActor
 * @brief dock collision actor representing collision between module docks
 */
UCLASS()
class REBOTS_API ADockCollisionActor : public AActor
{
	GENERATED_BODY()
    ModuleDockFace Face; /**< dock face associated with collision */
    AModularRobot* Module; /**< module associated with this actor */
    bool CurrentlyOverlapping = false; /**< currently overlapping actors ? */
    ADockCollisionActor* OtherDockCollision; /**< currently overlapped with this actor */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* BoxComponent; /**< box component */
    FVector BoxExtents; /**< box extents */
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
     * @brief test dock compatibility
     * @param d1
     * @param d2
     * @return d1 and d2 are compatible with each other for docking
     */
    bool TestDockCompatibility(ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief get dock face
     * @pram return dock face
     */
    ModuleDockFace GetDockFace();
    /**
     * @brief set module
     * @param mod module
     */
    void SetModuleAndDockFace(AModularRobot* mod, ModuleDockFace f);
    /**
     * @brief get module
     * @return module
     */
    AModularRobot* GetModule();
	/**
     * @brief constructor
     */
	ADockCollisionActor();
	/**
     * @brief begin play for this actor
     */
	virtual void BeginPlay() override;
	/**
     * @brief tick the actor
     */
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
