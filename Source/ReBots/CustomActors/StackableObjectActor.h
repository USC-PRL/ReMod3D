
#pragma once

#include "GameFramework/Actor.h"
#include "StackableObjectActor.generated.h"
UCLASS()
class REBOTS_API AStackableObjectActor : public AActor
{
    GENERATED_BODY()
private:
    UMaterial* RedMaterial; /**< red color material */
    UMaterial* BlueMaterial; /**< blue color material */
    FVector Scale; /**< 3d scale of particle */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ParticleBody, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* Box; /**< box of actor */
    class USceneComponent* SharedRoot; /**< root component */
public:
    // Sets default values for this actor's properties
    AStackableObjectActor();
    /**
     * @brief get box
     * @return box
     */
    UStaticMeshComponent* GetBox();
    /**
     * @brief set particle scale
     * @param particle scale
     */
    void SetScale(FVector s);
    /**
     * @brief get particle scale
     * @return particle scale
     */
    FVector GetScale();
    /**
     * @brief get actor transform
     * @return actor transform
     */
    FTransform GetActorTransform();
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    
    
};
