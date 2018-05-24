// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include <random>
#include <fstream>
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "CustomActors/StackableObjectActor.h"
#include "ScaleTestGameMode.generated.h"

/**
*
*/
UCLASS()
class REBOTS_API AScaleTestGameMode : public AGameMode
{
	GENERATED_BODY()

	unsigned seed; /**< seed value */
	std::mt19937 generator; /**< generator for random nums */
	int TickCounter = 0; /**< Elapsed Ticks*/
	int NumSuperBots = 0; /**< Number of SuperBot Modules */
	int NumRoomBots = 0;
	int NumSmoresBots = 0;
	int NumBotsKey = 100; /**< Key for displaying number of SuperBot modules */
    std::ofstream ofile; /**< output logging file */
	/**
	 * @brief game mode constructor
	 * @param ObjectInitializer initializer
	*/
	AScaleTestGameMode(const FObjectInitializer& ObjectInitializer);
	/**
	* @brief advance the simulation
	* @param DeltaSeconds fraction of a second by which to advance simulation
	*/
	virtual void Tick(float DeltaSeconds) override;
};
