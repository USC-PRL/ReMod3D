// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ReferenceFrameActor.generated.h"
/**
 * @class AReferenceFrameActor
 * @brief represents a visualization of a reference frame
 */
UCLASS()
class REBOTS_API AReferenceFrameActor : public AActor
{
	GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* XAxis; /**< x axis */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* YAxis; /**< y axis */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ZAxis; /**< z axis */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* XCap; /**< x axis cap */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* YCap; /**< y axis cap */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ZCap; /**< z axis cap */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* OriginSphere; /**< z axis */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FrameBody, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* SharedRootComponent; /**< shared root */
public:	
	/**
     * @brief constructor
     */
	AReferenceFrameActor();
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
