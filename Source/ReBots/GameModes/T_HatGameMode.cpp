// Fill out your copyright notice in the Description page of Project Settings.

 
#include "T_HatGameMode.h"
AT_HatGameMode::AT_HatGameMode() {
    static ConstructorHelpers::FObjectFinder<UMaterial>
    BMaterial(TEXT("/Game/SuperBotMaterials/RedMaterial.RedMaterial"));
    if (BMaterial.Succeeded()) {
        Material = BMaterial.Object;
    }
}

void AT_HatGameMode::Tick(float DeltaSeconds) {
    count += DeltaSeconds;
    calOptimalOpTime();
    GEngine->AddOnScreenDebugMessage(1221, 1.0, FColor::Yellow, FString::Printf(TEXT("Best Possible Time: %f"), optimalOpTime));
    GEngine->AddOnScreenDebugMessage(1222, 1.0, FColor::Yellow, FString::Printf(TEXT("Elapsed Time: %f"), count));
    
    if(count >= 0.5 && startCal == true) {
        calOptimalOpTime();
        calSupplySinkOpList();
        startCal = false;
        calNewOpTime = true;
    }
    if (calNewOpTime == true && operationTimeList.size() > 0) {
        std::shared_ptr<PSSuperBot> tempSupply = moduleNameToStruct[operationTimeListInverse.begin()->second];
        std::shared_ptr<PSSuperBot> tempSink = moduleNameToStruct[operationTimeListInverse.rbegin()->second];
        calNewOptimalTime(tempSupply, tempSink);
        updateOperationTimeList();
        calNewOpTime = ifCalNewOpTime(tempSupply, tempSink);
        if (!calNewOpTime) {
            GEngine->AddOnScreenDebugMessage(1111, 20.0, FColor::Red, FString("DONE!!!!!!"));
            float sampleMean = 0.0;
            float sampleVariance = 0.0;
            int meanCount = 0;
            
            for (int i=0; i<nodes.size(); i++) {
                if(nodes[i]->currentShareAmt < nodes[i]->ratedCurrent) {
                    sampleMean += nodes[i]->origOpTime;
                    meanCount++;
                }
            }
            sampleMean /= meanCount;
            for (int i=0; i<nodes.size(); i++) {
                if(nodes[i]->currentShareAmt < nodes[i]->ratedCurrent) {
                    sampleVariance += (nodes[i]->origOpTime - sampleMean)*(nodes[i]->origOpTime - sampleMean);
                }
            }
            sampleVariance /= meanCount;
            std::cout<<"Variance: "<<sampleVariance<<std::endl;
            
        }
        UMaterialInstanceDynamic* DynMaterialSupply = UMaterialInstanceDynamic::Create(Material, this);
        UMaterialInstanceDynamic* DynMaterialSink = UMaterialInstanceDynamic::Create(Material, this);
        float newRSupply = fmax(0, 1 - ((tempSupply->origOpTime)/(optimalOpTime)));
        float newGSupply = fmin(1, ((tempSupply->origOpTime)/(optimalOpTime)));
        DynMaterialSupply->SetVectorParameterValue("Color", FLinearColor(newRSupply, newGSupply, 0));
        tempSupply->module->SetMaterialForAllBodies(DynMaterialSupply);
        tempSupply->material = DynMaterialSupply;
        float newRSink = fmax(0, 1 - ((tempSink->origOpTime)/(optimalOpTime)));
        float newGSink = fmin(1, ((tempSink->origOpTime)/(optimalOpTime)));
        DynMaterialSink->SetVectorParameterValue("Color", FLinearColor(newRSink, newGSink, 0));
        tempSink->module->SetMaterialForAllBodies(DynMaterialSink);
        tempSink->material = DynMaterialSink;
    }
    //int n = 1236;
   /* for (int i=0; i<nodes.size(); i++) {
        GEngine->AddOnScreenDebugMessage(n++, 10.0, FColor::Green, FString::Printf(TEXT("Node %d, remaining optime: %f"), i, nodes[i]->origOpTime));
    }*/
    
}


void AT_HatGameMode::BeginPlay() {
    TActorIterator< ASuperBotModule > SuperbotIt = TActorIterator< ASuperBotModule >(GetWorld());
    while (SuperbotIt) {
        int idNum = atoi(&SuperbotIt->GetName().c_str()[SuperbotIt->GetName().length() - 1]);
        std::cout<<"ID Number: "<<idNum<<endl;
        (*SuperbotIt)->SetIDNumber(modules.size());
        modules.push_back(*SuperbotIt);
        ++SuperbotIt;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disHP(1000, 10000);
    std::uniform_real_distribution<> disCC(10, 500);
    std::uniform_real_distribution<> disB(10, 20);
    nodes = std::vector<std::shared_ptr<PSSuperBot>>(modules.size());
    for (int i=0; i<nodes.size(); i++) {
        nodes[i] = std::shared_ptr<PSSuperBot>(new PSSuperBot());
        nodes[i]->ratedCurrent = disB(gen);
        nodes[i]->hp = disHP(gen);
        nodes[i]->origHp = nodes[i]->hp;
        nodes[i]->cc = disCC(gen);
        nodes[i]->origCc = nodes[i]->cc;
        nodes[i]->origOpTime = (nodes[i]->origHp)/(nodes[i]->cc);
        std::stringstream ss;
        ss << "n" << i;
        nodes[i]->name = ss.str();
        moduleNameToStruct[ss.str()] = nodes[i];
    }
    calOptimalOpTime();
    
    for (int i=0; i<nodes.size(); i++) {
        if (nodes[i]->currentShareAmt >= nodes[i]->ratedCurrent) {
            UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
            DynMaterial->SetVectorParameterValue("Color", FLinearColor(0, 0, 1));
            nodes[i]->module = modules[i];
            nodes[i]->module->SetMaterialForAllBodies(DynMaterial);
            nodes[i]->material = DynMaterial;
        } else {
            UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
            float newR = fmax(0, 1 - ((nodes[i]->origOpTime)/(optimalOpTime)));
            float newG = fmin(1, ((nodes[i]->origOpTime)/(optimalOpTime)));
            DynMaterial->SetVectorParameterValue("Color", FLinearColor(newR, newG, 0));
            nodes[i]->module = modules[i];
            nodes[i]->module->SetMaterialForAllBodies(DynMaterial);
            nodes[i]->material = DynMaterial;
        }
    }
    

    
}

//Cal Original Operation Time
void AT_HatGameMode::calOptimalOpTime() {
    for(int i = 0; i < nodes.size(); i++) {
        totalHp += nodes[i]->origHp;
        totalCc += nodes[i]->cc;
    }
    optimalOpTime = totalHp / totalCc;
}

//Get Original Supply and Sink List
//Get Original Supply and Sink Per Second List
//Get Original Operation Time List
void AT_HatGameMode::calSupplySinkOpList() {
    float tempHp = 0;
    float tempCc = 0;
    float tempVal = 0;
    float tempOp = 0;
    supplySink.clear ();
    for(int i = 0; i < nodes.size(); i++) {
        tempHp = nodes[i]->origHp;
        tempCc = nodes[i]->cc;
        tempOp = nodes[i]->origOpTime;
        tempVal = tempHp - optimalOpTime*tempCc;
        nodes[i]->sinkSupplyAmt = tempVal;
        supplySink.push_back(tempVal);
        operationTimeList[nodes[i]->name] = tempOp;
        operationTimeListInverse[tempOp] = nodes[i]->name;
        supplySinkPerSecDict[nodes[i]->name] = tempVal/optimalOpTime;
        if(tempVal/optimalOpTime > 50) {nodes[i]->sinkSupplyAmtPerSec = ratedCurrent;}
        else if(tempVal/optimalOpTime <= 50) {nodes[i]->sinkSupplyAmtPerSec = tempVal/optimalOpTime;}
    }
}

//if Supply != Sink, Time Can't Reach Optimal Time
//Input: supplySinkPerSecDict
bool AT_HatGameMode::ifCalNewOpTime(std::shared_ptr<PSSuperBot> supply, std::shared_ptr<PSSuperBot> sink) {
    
    float supplyOpTime = supply->origOpTime;
    float sinkOpTime = sink->origOpTime;
    
    if(fabs(supplyOpTime - sinkOpTime) <= 0.05) {
        return false;
    }
    else {
        return true;
    }
}

void AT_HatGameMode::updateOpTime(std::shared_ptr<PSSuperBot> nodeObj) {
    nodeObj->origOpTime = nodeObj->origHp / nodeObj->origCc;
}

void AT_HatGameMode::updateOperationTimeList() {
    float tempOp = 0;
    string tempName = " ";
    operationTimeList.clear();
    operationTimeListInverse.clear();
    for (int i = 0; i < nodes.size(); i++) {
        if(nodes[i]->currentShareAmt < nodes[i]->ratedCurrent) {
            tempOp = nodes[i]->origOpTime;
            tempName = nodes[i]->name;
            operationTimeList[tempName] = tempOp;
            operationTimeListInverse[tempOp] = tempName;
        }
    }
}

void AT_HatGameMode::calNewOptimalTime(std::shared_ptr<PSSuperBot> tempSupply, std::shared_ptr<PSSuperBot> tempSink) {
    if(tempSupply->currentShareAmt < tempSupply->ratedCurrent) {
        tempSupply->origCc += 1;
        tempSupply->currentShareAmt += 1;
        updateOpTime (tempSupply);
        tempSink->origCc -= 1;
        tempSink->currentShareAmt -= 1;
        updateOpTime(tempSink);
    }
}

