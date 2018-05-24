// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "SuperBotBoundingGeometry.generated.h"

UCLASS()
class REBOTS_API ASuperBotBoundingGeometry : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuperBotBoundingGeometry();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
