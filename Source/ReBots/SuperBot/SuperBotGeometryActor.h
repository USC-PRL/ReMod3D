// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Framework/ModuleMotorVector.h"
#include "SuperbotKinematics.h"
#include "SuperBotGeometryActor.generated.h"
/**
 * @class ASuperBotGeometryActor
 * @brief geometry actor for superbot
 */
UCLASS()
class REBOTS_API ASuperBotGeometryActor : public AActor
{
	GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotGeometryBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* InnerBoxMaster; /**< master inner box*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotGeometryBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* OuterBoxMaster; /**< slave inner box*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotGeometryBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* OuterBoxSlave; /**< slave inner box*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SuperBotGeometryBody, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* SharedRootComponent; /**< slave inner box*/
    FVector Scale; /** < actor scale in X, Y, Z*/
    ModuleMotorVector JAngles; /**< joint angles */
public:	
	/**
     * @brief a superbot geometry actor constructor
     */
	ASuperBotGeometryActor();
    /**
    * @brief begin play for actor
    */
	virtual void BeginPlay() override;
	/**
     * @brief tick actor
     * @param DeltaSeconds amount of time to simulate
     */
	virtual void Tick( float DeltaSeconds ) override;
    
    
	
};
