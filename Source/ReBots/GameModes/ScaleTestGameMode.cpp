// Fill out your copyright notice in the Description page of Project Settings.

#include "ScaleTestGameMode.h"
#include "SuperBot/SuperBotModule.h"
#include "RoomBot/RoomBotModule.h"
#include "Smores/SmoresModule.h"


/**
* @brief game mode constructor
* @param ObjectInitializer initializer
*/
AScaleTestGameMode::AScaleTestGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	ofile = ofstream("C:\\Users\\tjcol\\Desktop\\LogMixedScale.txt");
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator = std::mt19937(seed);
	//DefaultPawnClass = ASuperBotModule::StaticClass();
}

/**
* @brief advance the simulation
* @param DeltaSeconds fraction of a second by which to advance simulation
*/
void AScaleTestGameMode::Tick(float DeltaSeconds) {
	if (TickCounter % 1 == 0) {
		std::uniform_real_distribution<> posXYRand(-1000, 1000);
		std::uniform_real_distribution<> posZRand(700, 1200);

		if (NumSuperBots < 250) {
			FTransform T = FTransform(FVector(posXYRand(generator), posXYRand(generator), posZRand(generator)));
			ASuperBotModule* S = GetWorld()->SpawnActor<ASuperBotModule>(T.GetLocation(), T.GetRotation().Rotator());
			NumSuperBots++;
		}

		if (NumSuperBots < 250) {
			ofile << NumRoomBots + NumSmoresBots + NumSuperBots << " " << 1.0 / GetWorld()->GetDeltaSeconds() << endl;

		}

		if (NumRoomBots < 500) {

			FTransform T = FTransform(FVector(posXYRand(generator), posXYRand(generator), posZRand(generator)));
			ARoomBotModule* R = GetWorld()->SpawnActor<ARoomBotModule>(T.GetLocation(), T.GetRotation().Rotator());
			NumRoomBots++;
		}

		if (NumRoomBots < 500) {
			ofile << NumRoomBots + NumSmoresBots + NumSuperBots << " " << 1.0 / GetWorld()->GetDeltaSeconds() << endl;

		}
		if (NumSmoresBots < 300) {

			FTransform T = FTransform(FVector(posXYRand(generator), posXYRand(generator), posZRand(generator)));
			ASmoresModule* S = GetWorld()->SpawnActor<ASmoresModule>(T.GetLocation(), T.GetRotation().Rotator());
			NumSmoresBots++;
		}

		if (NumSmoresBots < 300) {
			ofile << NumRoomBots + NumSmoresBots + NumSuperBots << " " << 1.0 / GetWorld()->GetDeltaSeconds() << endl;

		}


	}
	GEngine->AddOnScreenDebugMessage(NumBotsKey, 15.0, FColor::Green, FString::Printf(TEXT("Num Superbots: %d"), NumSuperBots));
	GEngine->AddOnScreenDebugMessage(NumBotsKey + 1, 15.0, FColor::Green, FString::Printf(TEXT("Num RoomBots: %d"), NumRoomBots));
	GEngine->AddOnScreenDebugMessage(NumBotsKey + 2, 15.0, FColor::Green, FString::Printf(TEXT("Num SmoresBots: %d"), NumSmoresBots));
	TickCounter++;
}


