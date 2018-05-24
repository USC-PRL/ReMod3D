// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "CustomActors/StackableObjectActor.h"
#include "ReBotsPileGameMode.generated.h"

class ASuperBotModule;
/**
 * 
 */
UCLASS()
class REBOTS_API AReBotsPileGameMode : public AGameMode
{
	GENERATED_BODY()
	int TickCounter = 0; /**< Elapsed Ticks*/
	int NumSuperBots = 0; /**< Number of SuperBot Modules */
	int NumBotsKey = 100; /**< Key for displaying number of SuperBot modules */
	/**
	* @brief game mode constructor
	* @param ObjectInitializer initializer
	*/
	AReBotsPileGameMode(const FObjectInitializer& ObjectInitializer);
	/**
	* @brief advance the simulation
	* @param DeltaSeconds fraction of a second by which to advance simulation
	*/
	virtual void Tick(float DeltaSeconds) override;
};
