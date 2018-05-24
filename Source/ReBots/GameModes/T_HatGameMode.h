// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <random>
#include <utility>
#include <memory>
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "SuperBot/SuperBotModule.h"
#include "T_HatGameMode.generated.h"

/**
 * 
 */
UCLASS()
class REBOTS_API AT_HatGameMode : public AGameMode
{
	GENERATED_BODY()
private:
    struct PSSuperBot {
        float origHp = 0;
        float hp = 0;
        float origCc = 0;
        float cc = 0;
        float ratedCurrent = 0;
        float origOpTime = 0;
        float sinkSupplyAmt = 0;
        float sinkSupplyAmtPerSec = 0;
        float currentShareAmt = 0;
        float count = 0;
        float operationTime = 0;
        std::string name;
        ASuperBotModule *module;
        UMaterialInstanceDynamic* material;
        
    };
    float totalHp = 0;
    float totalCc = 0;
    float count = 0;
    float optimalOpTime = 0;
    float ratedCurrent = 50;
    bool startCal = true;
    bool calNewOpTime = false;
    float maxHP = 10000;
    float minHP = 0;
    std::vector<float> supplySink;
    std::map<std::string, float> supplySinkPerSecDict;
    std::map<std::string, float> operationTimeList;
    std::map<float, std::string, std::greater<float> > operationTimeListInverse;
    std::map<std::string, std::shared_ptr<PSSuperBot> > moduleNameToStruct;
    std::vector<std::shared_ptr<PSSuperBot> > nodes;
    std::vector<ASuperBotModule*> modules;
    std::map<int, ASuperBotModule*, std::less<int> > IdsToModules;
    bool nodeDied = false;
    UMaterialInterface* Material = NULL;
public:
    AT_HatGameMode();
    void Tick(float DeltaSeconds) override;
    void BeginPlay() override;
    void calOptimalOpTime();
    void calSupplySinkOpList();
    bool ifCalNewOpTime(std::shared_ptr<PSSuperBot> supply, std::shared_ptr<PSSuperBot> sink);
    void updateOpTime(std::shared_ptr<PSSuperBot> nodeObj);
    void updateOperationTimeList();
    void calNewOptimalTime(std::shared_ptr<PSSuperBot> tempSupply, std::shared_ptr<PSSuperBot> tempSink);

    
	
	
	
};
