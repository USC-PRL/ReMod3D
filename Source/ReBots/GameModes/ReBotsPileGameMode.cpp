// Fill out your copyright notice in the Description page of Project Settings.

 #include "ReBotsPileGameMode.h"
#include "SuperBot/SuperBotModule.h"


/**
* @brief game mode constructor
* @param ObjectInitializer initializer
*/
AReBotsPileGameMode::AReBotsPileGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	//DefaultPawnClass = ASuperBotModule::StaticClass();
}

/**
* @brief advance the simulation
* @param DeltaSeconds fraction of a second by which to advance simulation
*/
void AReBotsPileGameMode::Tick(float DeltaSeconds) {

	if (NumSuperBots < 2) {
		FTransform T = FTransform(FVector(120,130,250*(NumSuperBots + 1)));
		ASuperBotModule* S = GetWorld()->SpawnActor<ASuperBotModule>(T.GetLocation(), T.GetRotation().Rotator());
		NumSuperBots++;
	}
	GEngine->AddOnScreenDebugMessage(NumBotsKey, 15.0, FColor::Green, FString::Printf(TEXT("Num Superbots: %d"), NumSuperBots));
	TickCounter++;
}


