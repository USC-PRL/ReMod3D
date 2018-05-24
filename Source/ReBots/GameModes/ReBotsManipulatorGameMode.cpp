// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ReBotsManipulatorGameMode.h"


//#pragma mark -
//#pragma Superbot Docking
/**
 * @brief get corrective docking transform
 * @param d1 dock 1
 * @param d2 dock 2
 * @return corrective trnasform
 */
FTransform AReBotsManipulatorGameMode::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
    if (d1 == DOCK_0 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI));
    } else if (d1 == DOCK_1 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI));
    } else if (d1 == DOCK_0 && d2 == DOCK_2) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_2 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_3 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_0 && d2 == DOCK_3) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_1 && d2 == DOCK_2) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_2 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_3 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_1 && d2 == DOCK_3) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_0 && d2 == DOCK_4) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_4 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_1 && d2 == DOCK_4) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_4 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_0 && d2 == DOCK_5) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_5 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_1 && d2 == DOCK_5) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_5 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    }
    return FTransform(FVector(0,0,0));
}
/**
 * @brief dock two modules together
 * @param sm1 superbot module 1
 * @param sm2 superbot module 2
 * @param d1 dock face of module 1
 * @param d2 dock face of module 2
 */
void AReBotsManipulatorGameMode::DockModuleToGround(ASuperBotModule* sm1, ModuleDockFace d1) {
    //sm1->SetDockEngaged(d1, true);
    ModuleMotorVector mv1 = sm1->GetJointAngles();
    sm1->GetRootComponent()->AttachTo(Floor->GetRootComponent(),"",EAttachLocation::SnapToTarget, true);
    FTransform t = Floor->GetRootComponent()->GetComponentTransform();
    
    t =
    sm1->GetRootToMasterInnerTransform().Inverse()*
    SuperbotKinematics::computeTransformToDock(mv1,d1)*
    ASuperBotModule::SuperbotFix*sm1->GetMasterInnerMesh()->GetComponentTransform()*
    Floor->GetRootComponent()->GetComponentTransform().Inverse();
    //sm1->GetRootComponent()->SetRelativeTransform(sm1->GetRootToMasterInnerTransform().Inverse()*
    //                                              SuperbotKinematics::computeTransformFromDock(mv1, d1)*
    //                                              FTransform(
    //                                              Floor->GetStaticMeshComponent()->GetRelativeTransform());
    AReferenceFrameActor *arf1 = GetWorld()->SpawnActor<AReferenceFrameActor>(t.GetLocation(),FRotator(t.GetRotation()));
    /*FName d1S = "BackDock";
     if (d1 == DOCK_0) d1S = "FrontDock";
     else if (d1 == DOCK_1) d1S = "BackDock";
     else if (d1 == DOCK_2) d1S = "LeftDock";
     else if (d1 == DOCK_3) d1S = "RightDock";
     else if (d1 == DOCK_4) d1S = "UpDock";
     else if (d1 == DOCK_5) d1S = "DownDock";
     UStaticMeshComponent* stMesh1;
     
     if (d1 == DOCK_0 || d1 == DOCK_3 || d1 == DOCK_2) {
     stMesh1 = sm1->GetMasterOuterMesh();
     } else {
     stMesh1 = sm1->GetSlaveOuterMesh();
     }
     APhysicsConstraintActor *a = GetWorld()->SpawnActor<APhysicsConstraintActor>();
     a->GetConstraintComp()->SetConstrainedComponents(stMesh1, d1S, Floor->GetStaticMeshComponent(), "");
     a->GetConstraintComp()->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
     a->GetConstraintComp()->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
     a->GetConstraintComp()->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
     a->GetConstraintComp()->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
     a->GetConstraintComp()->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
     a->GetConstraintComp()->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);*/
}
/**
 * @brief dock two modules together
 * @param sm1 superbot module 1
 * @param sm2 superbot module 2
 * @param d1 dock face of module 1
 * @param d2 dock face of module 2
 */
void AReBotsManipulatorGameMode::DockTwoModules(ASuperBotModule* sm1, ASuperBotModule* sm2, ModuleDockFace d1, ModuleDockFace d2) {
    
    //TODO: use root hierarchy somehow?
    connections[sm1->GetIDNumber()][d1] = sm2->GetDocks()[d2];
    connections[sm2->GetIDNumber()][d2] = sm1->GetDocks()[d1];
    sm1->SetDockEngaged(d1, true);
    sm2->SetDockEngaged(d2, true);
    ModuleMotorVector mv1 = sm1->GetJointAngles();
    ModuleMotorVector mv2 = sm2->GetJointAngles();
    sm1->GetRootComponent()->AttachTo(sm2->GetRootComponent(),"",EAttachLocation::SnapToTarget, true);
    sm1->GetRootComponent()->SetRelativeTransform(sm1->GetRootToMasterInnerTransform().Inverse()*
                                                  SuperbotKinematics::computeTransformFromDock(mv1, d1)*
                                                  GetCorrectiveDockingTransform(d1, d2)*
                                                  SuperbotKinematics::computeTransformToDock(mv2, d2)*
                                                  sm2->GetRootToMasterInnerTransform());
    
    sm1->WeldDockToComponent(d1, sm2->GetDockComponent(d2));
    FName d1S = "BackDock";
    FName d2S = "FrontDock";
    if (d1 == DOCK_0) d1S = "FrontDock";
    else if (d1 == DOCK_1) d1S = "BackDock";
    else if (d1 == DOCK_2) d1S = "LeftDock";
    else if (d1 == DOCK_3) d1S = "RightDock";
    else if (d1 == DOCK_4) d1S = "UpDock";
    else if (d1 == DOCK_5) d1S = "DownDock";
    if (d2 == DOCK_0) d1S = "FrontDock";
    else if (d2 == DOCK_1) d2S = "BackDock";
    else if (d2 == DOCK_2) d2S = "LeftDock";
    else if (d2 == DOCK_3) d2S = "RightDock";
    else if (d2 == DOCK_4) d2S = "UpDock";
    else if (d2 == DOCK_5) d2S = "DownDock";
    UStaticMeshComponent* stMesh1;
    UStaticMeshComponent* stMesh2;
    
    if (d1 == DOCK_0 || d1 == DOCK_3 || d1 == DOCK_2) {
        stMesh1 = sm1->GetMasterOuterMesh();
    } else {
        stMesh1 = sm1->GetSlaveOuterMesh();
    }
    
    if (d2 == DOCK_0 || d2 == DOCK_3 || d2 == DOCK_2) {
        stMesh2 = sm2->GetMasterOuterMesh();
    } else {
        stMesh2 = sm2->GetSlaveOuterMesh();
    }
    APhysicsConstraintActor *a = GetWorld()->SpawnActor<APhysicsConstraintActor>();
    a->GetConstraintComp()->SetConstrainedComponents(stMesh1, d1S, stMesh2, d2S);
    a->GetConstraintComp()->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
    a->GetConstraintComp()->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
    a->GetConstraintComp()->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
    a->GetConstraintComp()->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
    a->GetConstraintComp()->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
    a->GetConstraintComp()->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
    a->GetConstraintComp()->SetDisableCollision(true);
}
/**
 * @brief get transform of end effector for joint angles
 * @param JAngles joint angles
 * @return transform of End effector
 */
FTransform AReBotsManipulatorGameMode::GetTransformOfEndEffector(std::vector<ModuleMotorVector> JAngles) {
    FTransform endEffectorTransform = FTransform(FVector(0,0,0));
    if (ToMasterKinematics) {
        for (int i=0; i<JAngles.size(); i++) {
            endEffectorTransform = SuperbotKinematics::computeTransformFromDock(JAngles[i], DOCK_1)*endEffectorTransform;
            endEffectorTransform = SuperbotKinematics::computeTransformToDock(JAngles[i], DOCK_0)*endEffectorTransform;
        }
    } else {
        for (int i=0; i<JAngles.size(); i++) {
            endEffectorTransform = SuperbotKinematics::computeTransformFromDock(JAngles[i], DOCK_0)*endEffectorTransform;
            endEffectorTransform = SuperbotKinematics::computeTransformToDock(JAngles[i], DOCK_1)*endEffectorTransform;
        }
    }
    return endEffectorTransform;
}
/**
 * @brief fitness function
 * @param P particle
 * @return particle fitness
 */

/////TODO fix manipulator transform moving with end effector. need fixed frame of reference
float AReBotsManipulatorGameMode::Fitness(PSOParticle P) {
    std::vector<ModuleMotorVector> mvs(P.getPosition().size()/3);
    for (int i=0; i<P.getPosition().size()/3; i++) {mvs[i] = ModuleMotorVector(P.getPosition()[3*i + 0],P.getPosition()[3*i + 1],P.getPosition()[3*i + 2]);}
    FTransform PEndTransform = GetTransformOfEndEffector(mvs)*ToGroundTransform;
    FTransform GoalTransform = GoalEndEffector;
    FRotator DiffRot = FRotator(GoalTransform.GetRotation()) - FRotator(PEndTransform.GetRotation());
    FVector DiffPos = GoalTransform.GetLocation() - PEndTransform.GetLocation();
    float MagOrient = sqrtf(DiffRot.Pitch*DiffRot.Pitch + DiffRot.Yaw*DiffRot.Yaw + DiffRot.Roll*DiffRot.Roll);
    return DiffPos.Size() + MagOrient + 1000*IsInSelfCollision(ToGroundTransform,mvs);
}

/////TODO fix manipulator transform moving with end effector. need fixed frame of reference
float AReBotsManipulatorGameMode::BBPSOFitness(BranchBoundParticle P, vector<float> st, vector<float> tar) {
    std::vector<ModuleMotorVector> mvs(P.GetPosition().size()/3);
    for (int i=0; i<P.GetPosition().size()/3; i++) {mvs[i] = ModuleMotorVector(P.GetPosition()[3*i + 0],P.GetPosition()[3*i + 1],P.GetPosition()[3*i + 2]);}
    FTransform PEndTransform = GetTransformOfEndEffector(mvs)*ToGroundTransform;
    FTransform GoalTransform = GoalEndEffector;
    FRotator DiffRot = FRotator(GoalTransform.GetRotation()) - FRotator(PEndTransform.GetRotation());
    FVector DiffPos = GoalTransform.GetLocation() - PEndTransform.GetLocation();
    float MagOrient = sqrtf(DiffRot.Pitch*DiffRot.Pitch + DiffRot.Yaw*DiffRot.Yaw + DiffRot.Roll*DiffRot.Roll);
    return DiffPos.Size() + MagOrient + 1000*IsInSelfCollision(ToGroundTransform,mvs);
}
/**
 * @brief game mode constructor
 * @param ObjectInitializer initializer
 */
AReBotsManipulatorGameMode::AReBotsManipulatorGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    //DefaultPawnClass = ASuperBotModule::StaticClass();
}
/**
 * @brief detect self collision
 * @param ToGround to ground transform
 * @param JAngles joint angles
 * @param Thresh threshold for self collision
 * @param ToMaster run kinematics toward master side
 */
bool AReBotsManipulatorGameMode::IsInSelfCollision(FTransform ToGround, std::vector<ModuleMotorVector> JAngles) {
    FTransform endEffectorTransform = ToGround;
    std::vector<FTransform> ModuleTransforms(JAngles.size());
    if (ToMasterKinematics) {
        for (int i=0; i<JAngles.size(); i++) {
            endEffectorTransform = SuperbotKinematics::computeTransformFromDock(JAngles[i], DOCK_1)*endEffectorTransform;
            ModuleTransforms[i] = endEffectorTransform;
            endEffectorTransform = SuperbotKinematics::computeTransformToDock(JAngles[i], DOCK_0)*endEffectorTransform;
        }
    } else {
        for (int i=0; i<JAngles.size(); i++) {
            endEffectorTransform = SuperbotKinematics::computeTransformFromDock(JAngles[i], DOCK_0)*endEffectorTransform;
            ModuleTransforms[i] = endEffectorTransform;
            endEffectorTransform = SuperbotKinematics::computeTransformToDock(JAngles[i], DOCK_1)*endEffectorTransform;
        }
    }
    for (int i=0; i<ModuleTransforms.size(); i++) {
        for (int j=i + 1; j<ModuleTransforms.size(); j++) {
            FVector DiffVec = ModuleTransforms[i].GetLocation() - ModuleTransforms[j].GetLocation();
            if (DiffVec.Size() < 150.0) return true;
        }
    }
    return false;
}
/**
 * @brief detect collision with ground
 * @param ToGround to ground transform
 * @param JAngles joint angles
 * @param GroundZVal ground z value (vertical)
 * @param Thresh threshold
 * @param ToMaster run kinematics toward master side
 */
bool AReBotsManipulatorGameMode::IsInCollisionWithGround(FTransform ToGround,
                                                         std::vector<ModuleMotorVector> JAngles, float GroundZVal, float Thresh) {
    return false;
}
/**
 * @brief get bounding spheres for joint angles
 * @param mvs motor vectors
 * @return bounding spheres
 */
vector<ABoundingSphere*> AReBotsManipulatorGameMode::GetBoundingSpheresForJointAngles(FTransform ToGround,
                                                                                      std::vector<ModuleMotorVector> JAngles) {
    FTransform endEffectorTransform = ToGround*FTransform(FVector(0,0,0));
    vector<ABoundingSphere*> BSpheres;
    if (ToMasterKinematics) {
        for (int i=0; i<JAngles.size(); i++) {
            endEffectorTransform = SuperbotKinematics::computeTransformFromDock(JAngles[i], DOCK_1)*endEffectorTransform;
            BSpheres.push_back(GetWorld()->SpawnActor<ABoundingSphere>(endEffectorTransform.GetLocation(),
                                                                             FRotator(endEffectorTransform.GetRotation())));
            endEffectorTransform = SuperbotKinematics::computeTransformToDock(JAngles[i], DOCK_0)*endEffectorTransform;
        }
    } else {
        for (int i=0; i<JAngles.size(); i++) {
            endEffectorTransform = SuperbotKinematics::computeTransformFromDock(JAngles[i], DOCK_0)*endEffectorTransform;
            BSpheres.push_back(GetWorld()->SpawnActor<ABoundingSphere>(endEffectorTransform.GetLocation(),
                                                                       FRotator(endEffectorTransform.GetRotation())));
            endEffectorTransform = SuperbotKinematics::computeTransformToDock(JAngles[i], DOCK_1)*endEffectorTransform;
        }
    }
    return BSpheres;
}
/**
 * @brief advance the simulation
 * @param DeltaSeconds fraction of a second by which to advance simulation
 */
void AReBotsManipulatorGameMode::Tick(float DeltaSeconds) {
    
    if (FirstTick) {
        TActorIterator< APhysicsConstraintActor > ConstraintIt = TActorIterator< APhysicsConstraintActor >(GetWorld());
        TActorIterator< ASuperBotModule > SuperbotIt = TActorIterator< ASuperBotModule >(GetWorld());
        while (SuperbotIt) {
            modsToIDs[*SuperbotIt] = modules.size();
            (*SuperbotIt)->SetIDNumber(modules.size());
            //modules.push_back(*SuperbotIt);
            string str = (*SuperbotIt)->GetName();
            size_t last_index = str.find_last_not_of("0123456789");
            string result = str.substr(last_index + 1);
            stringstream  ss(result);
            int resultInt;
            ss >> resultInt;
            modulesMap[resultInt] = *SuperbotIt;
            ++SuperbotIt;
        }
        
        typedef std::map<int, ASuperBotModule*>::iterator it_type;
        for(it_type iterator = modulesMap.begin(); iterator != modulesMap.end(); iterator++) {
            modules.push_back(iterator->second);
        }
        
        int numConstraints = 0;
        while (ConstraintIt) {
            numConstraints++;
            APhysicsConstraintActor *c = *ConstraintIt;
            if (c->GetConstraintComp()->ConstraintActor1->GetClass() == ASuperBotModule::StaticClass() &&
                c->GetConstraintComp()->ConstraintActor2->GetClass() == ASuperBotModule::StaticClass()) {
                ASuperBotModule* sm1 = Cast<ASuperBotModule>(c->GetConstraintComp()->ConstraintActor1);
                ASuperBotModule* sm2 = Cast<ASuperBotModule>(c->GetConstraintComp()->ConstraintActor2);
                FConstrainComponentPropName n1 = c->GetConstraintComp()->ComponentName1;
                FConstrainComponentPropName n2 = c->GetConstraintComp()->ComponentName2;
                FString name1 = n1.ComponentName.ToString();
                FString name2 = n2.ComponentName.ToString();
                FString bone1 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone1.ToString();
                FString bone2 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone2.ToString();
                ModuleDockFace dock1 = sm1->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone1)));
                ModuleDockFace dock2 = sm2->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone2)));
                if (sm1 && sm2) {
                    if (DockDebug) {
                        cout<<"Constraint Found: "<<sm1->GetName()<<"-"<<std::string(TCHAR_TO_UTF8(*bone1))<<
                        "("<<dock1<<")"<<","<<sm2->GetName()<<"-"<<std::string(TCHAR_TO_UTF8(*bone2))<<"("<<dock2<<")"<<endl;
                    }
                    CMonitor.AddConstraint(sm1->GetName(), sm2->GetName(), (ModuleDockFace)dock1, (ModuleDockFace)dock2);
                    connections[sm1->GetIDNumber()][dock1] = sm2->GetDocks()[dock2];
                    connections[sm2->GetIDNumber()][dock2] = sm1->GetDocks()[dock1];
                    sm1->WeldDockToComponent(dock1, sm2->GetDocks()[dock2].GetDockComponent());
                    
                    sm1->SetDockEngaged(dock1, true);
                    sm2->SetDockEngaged(dock2, true);
                    if (DockDebug) {
                        cout<<sm1->GetName()<<" Dock Status: ";
                        for (int i=0; i<6; i++) {
                            cout<<sm1->GetDocks()[i].GetDockEngaged()<<" ";
                        }
                        cout<<endl;
                        cout<<sm2->GetName()<<" Dock Status: ";
                        for (int i=0; i<6; i++) {
                            cout<<sm2->GetDocks()[i].GetDockEngaged()<<" ";
                        }
                        cout<<endl;
                    }
                }
            } else if (c->GetConstraintComp()->ConstraintActor1->GetClass() == ASuperBotModule::StaticClass() &&
                       c->GetConstraintComp()->ConstraintActor2->GetClass() == AStaticMeshActor::StaticClass()) {
                ASuperBotModule *m = (ASuperBotModule*)c->GetConstraintComp()->ConstraintActor1;
                AStaticMeshActor *sma = (AStaticMeshActor*)c->GetConstraintComp()->ConstraintActor2;
                if (std::string(TCHAR_TO_UTF8(*sma->GetName())).compare("Floor") == 0) {
                    FString bone1 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone1.ToString();
                    ModuleDockFace dock1 = m->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone1)));
                    m->SetDockEngagedToGround(dock1,true);
                    cout<<m->GetName()<<" Connected to floor statuses: "<<endl;
                    if (DockDebug) {
                        for (int i=0; i<6; i++) {
                            cout<<m->GetDocks()[i].GetDockEngagedToGround()<<" ";
                        }
                        cout<<endl;
                    }
                }
            } else if (c->GetConstraintComp()->ConstraintActor1->GetClass() == AStaticMeshActor::StaticClass() &&
                       c->GetConstraintComp()->ConstraintActor2->GetClass() == ASuperBotModule::StaticClass()) {
                ASuperBotModule *m = (ASuperBotModule*)c->GetConstraintComp()->ConstraintActor2;
                AStaticMeshActor *sma = (AStaticMeshActor*)c->GetConstraintComp()->ConstraintActor1;
                if (std::string(TCHAR_TO_UTF8(*sma->GetName())).compare("Floor") == 0) {
                    FString bone2 = c->GetConstraintComp()->ConstraintInstance.ConstraintBone2.ToString();
                    ModuleDockFace dock2 = m->GetDockFaceForName(std::string(TCHAR_TO_UTF8(*bone2)));
                    m->SetDockEngagedToGround(dock2,true);
                    cout<<m->GetName()<<" Connected to floor statuses ";
                    if (DockDebug) {
                        for (int i=0; i<6; i++) {
                            cout<<m->GetDocks()[i].GetDockEngagedToGround()<<" ";
                        }
                        cout<<endl;
                    }
                }
            }
            ++ConstraintIt;
        }
        TActorIterator< AStaticMeshActor > StaticMeshActorsIt = TActorIterator< AStaticMeshActor >(GetWorld());
        while (StaticMeshActorsIt) {
            if(std::string(TCHAR_TO_UTF8(*(*StaticMeshActorsIt)->GetName())).compare("Floor") == 0) {
                AStaticMeshActor* MeshActor = (*StaticMeshActorsIt);
                Floor = MeshActor;
                //AFloorCollisionActor* FloorCollision = GetWorld()->SpawnActor<AFloorCollisionActor>(MeshActor->GetActorLocation(),
                //                                                              MeshActor->GetActorRotation());
                
                break;
            }
            ++StaticMeshActorsIt;
        }
        FirstTick = false;
        EndEffectorFrame = GetWorld()->SpawnActor<AReferenceFrameActor>(modules[0]->GetMasterInnerMesh()->GetComponentTransform().GetLocation(),
                                                                        FRotator(modules[0]->GetMasterInnerMesh()->GetComponentTransform().GetRotation()));
        

        GoalEndEffectorFrame = NULL;
        FTransform t;
        if (ToMasterKinematics) {
            t = SuperbotKinematics::computeTransformToDock(modules[0]->GetJointAngles(),DOCK_1)*ASuperBotModule::SuperbotFix*modules[0]->GetMasterInnerMesh()->GetComponentTransform();
        } else {
            t = SuperbotKinematics::computeTransformToDock(modules[0]->GetJointAngles(),DOCK_0)*ASuperBotModule::SuperbotFix*modules[0]->GetMasterInnerMesh()->GetComponentTransform();
        }
        ToGroundTransform = t;
        ToGroundFrame = GetWorld()->SpawnActor<AReferenceFrameActor>(ToGroundTransform.GetLocation(),
                                                                    FRotator(ToGroundTransform.GetRotation()));
    } else {
        if (!GoalEndEffectorFrame) {
            GoalEndEffectorFrame = GetWorld()->SpawnActor<AReferenceFrameActor>();
            std::vector<ModuleMotorVector> JAnglesDes(modules.size());
            Seed = std::chrono::system_clock::now().time_since_epoch().count();
            Generator = std::mt19937(Seed);
            std::uniform_real_distribution<> realDis(-30,30);
            for (int i=0; i<modules.size(); i++) {
                JAnglesDes[i] = ModuleMotorVector(realDis(Generator),realDis(Generator),realDis(Generator));
            }
            GoalEndEffector = GetTransformOfEndEffector(JAnglesDes)*ToGroundTransform;
            GoalEndEffectorFrame->GetRootComponent()->SetWorldTransform(GetTransformOfEndEffector(JAnglesDes)*ToGroundTransform);
            //BoundingSpheresGoal = GetBoundingSpheresForJointAngles(ToGroundTransform,JAnglesDes);
        }
        if (!HaveInitiatedIK) {
            std::vector<std::pair<float,float> > posB(modules.size()*3);
            std::vector<std::pair<float,float> > velB(modules.size()*3);
            for (int i=0; i<modules.size()*3; i++) {
                posB[i] = std::pair<float,float>(-85,85);
                velB[i] = std::pair<float,float>(-85,85);
            }
            SolutionPos = vector<float>(modules.size()*3);
            PSOWorker = FBBPSOWorker::BBPSOInit(50,50,modules.size()*3,posB,velB,2.0,std::bind(&AReBotsManipulatorGameMode::BBPSOFitness,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3),std::vector<float> {0,200,400,100},std::vector<float> {0,200,400,100},SolutionPos,&SolutionFitness);
            HaveInitiatedIK = true;
        } else if (!HaveCompletedIK) {
            HaveCompletedIK = PSOWorker->IsFinished();
        } else {
            std::vector<ModuleMotorVector> mvs(modules.size());
            for (int i=0; i<SolutionPos.size()/3; i++)
            {
                mvs[i] = ModuleMotorVector(SolutionPos[3*i + 0],
                                             SolutionPos[3*i + 1],
                                             SolutionPos[3*i + 2]);
            }
            for (int i=0; i<modules.size(); i++) {
                modules[i]->GetMasterInnerMesh()->WakeAllRigidBodies();
                modules[i]->GetSlaveInnerMesh()->WakeAllRigidBodies();
                modules[i]->GetMasterOuterMesh()->WakeAllRigidBodies();
                modules[i]->GetSlaveOuterMesh()->WakeAllRigidBodies();
                modules[i]->SetJointAngles(mvs[i]);
            }
            cout<<"Best Fitness: "<<SolutionFitness<<endl;
            if (!HaveAddedOnScreenMessage) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BBPSO Done"));
                HaveAddedOnScreenMessage = true;
                PSOWorker->Stop();
                PSOWorker->Shutdown();
                //if (PSOWorker) delete PSOWorker;
                //PSOWorker = NULL;
            }
        }
        std::vector<ModuleMotorVector> JAngles(modules.size());
        for (int i=0; i<modules.size(); i++) {
            JAngles[i] = modules[i]->GetJointAngles();
        }
        EndEffectorFrame->GetRootComponent()->SetWorldTransform(GetTransformOfEndEffector(JAngles)*ToGroundTransform);
        for (int i=0;i<BoundingSpheresCurrent.size(); i++) {
            BoundingSpheresCurrent[i]->Destroy();
        }
        //BoundingSpheresCurrent = GetBoundingSpheresForJointAngles(ToGroundTransform,JAngles);
    }
}




//#pragma mark -
//#pragma mark Messaging Functionality
/**
 *	@brief	Sends a message from module to the module connected to dock
 *	@param 	module 	sending module
 *	@param 	dock 	dock out which message is sent
 *	@param 	message 	message contents
 */
void AReBotsManipulatorGameMode::sendMessageToDock(ASuperBotModule *module, ModuleDock dock, std::string message) {
    if (connections[modsToIDs[module]][dock.GetDockFace()].GetDockFace() == DOCK_6) {
        cout<<"Message unroutable: module "<<modsToIDs[module]<<" dock "<<dock.GetDockFace()<<endl;\
        cout<<"No dock connected"<<endl;
        return;
    }
    Message m = Message(message, dock, connections[modsToIDs[module]][dock.GetDockFace()]);
    messageRoom[modsToIDs[(ASuperBotModule*)connections[modsToIDs[module]][dock.GetDockFace()].GetModule()]].push_back(m);
}
/**
 *	@brief	Sends a kinematics message out on dock
 *	@param 	sendingModule 	module sending the message
 * @param dock dock send ing message
 *	@param 	mes 	message contents
 */
void AReBotsManipulatorGameMode::sendKinematicsMessageToDock(ASuperBotModule *module, ModuleDock dock, KinematicsMessage mes) {
    if (connections[modsToIDs[module]][dock.GetDockFace()].GetDockFace() == DOCK_6) {
        cout<<"Message unroutable: module "<<modsToIDs[module]<<" dock "<<dock.GetDockFace()<<endl;
        cout<<"No dock connected"<<endl;
        return;
    }
    mes.SetSendingDock(dock);
    mes.SetReceivingDock(connections[modsToIDs[module]][dock.GetDockFace()]);
    messageRoomKinematics[modsToIDs[(ASuperBotModule*)connections[modsToIDs[module]][dock.GetDockFace()].GetModule()]].push_back(mes);
}
/**
 *	@brief	Sends a kinematics message out on dock
 *	@param 	sendingModule 	module sending the message
 * @param dock dock send ing message
 *	@param 	mes 	message contents
 */
void AReBotsManipulatorGameMode::sendTreeMessageToDock(ASuperBotModule *module, ModuleDock dock, TreeMessage mes) {
    if (connections[modsToIDs[module]][dock.GetDockFace()].GetDockFace() == DOCK_6) {
        cout<<"Message unroutable: module "<<modsToIDs[module]<<" dock "<<dock.GetDockFace()<<endl;
        cout<<"No dock connected"<<endl;
        return;
    }
    mes.SetSendingDock(dock);
    mes.SetReceivingDock(connections[modsToIDs[module]][dock.GetDockFace()]);
    messageRoomSuperBotTree[modsToIDs[(ASuperBotModule*)connections[modsToIDs[module]][dock.GetDockFace()].GetModule()]].push_back(mes);
}
/**
 *	@brief	Sends a wireless message out from sendingModule's center of mass. The range of the message is a sphere
 *          centered at sendingModule's center of mass with a radius of range.
 *	@param 	sendingModule 	module sending the message
 *	@param 	range 	range of the message
 *	@param 	message 	message contents
 */
void AReBotsManipulatorGameMode::sendRangedMessage(ASuperBotModule *sendingModule, float range, string message) {
    
    RangedMessage m = RangedMessage(message, range);
    for (int i=0; i<(int)modules.size(); i++) {
        if (modsToIDs[modules[i]] != modsToIDs[sendingModule]) {
            FTransform pose1 = ASuperBotModule::SuperbotFix*modules[i]->GetMasterInnerMesh()->GetComponentTransform();
            FTransform pose2 = ASuperBotModule::SuperbotFix*sendingModule->GetMasterInnerMesh()->GetComponentTransform();
            float dist = FVector::Dist(pose1.GetLocation(), pose2.GetLocation());
            if (dist <= range) {
                messageRoomRanged[modsToIDs[modules[i]]].push_back(m);
            }
        }
    }
}
/**
 *	@brief	retrieves the last message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent message in module's queue of messages
 */
Message AReBotsManipulatorGameMode::getLastMessage(int module) {
    Message m = messageRoom[module].back();
    messageRoom[module].pop_back();
    return m;
}
/**
 *	@brief	retrieves the last ranged message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent ranged message in module's queue of ranged messages
 */
RangedMessage AReBotsManipulatorGameMode::getLastRangedMessage(int module) {
    RangedMessage m = messageRoomRanged[module].back();
    messageRoomRanged[module].pop_back();
    return m;
}
/**
 *	@brief	retrieves the ranged messages for a given module
 *	@param 	module 	name of module
 *	@return	messages from modules ranged message queue
 */
vector<RangedMessage> AReBotsManipulatorGameMode::getRangedMessages(int module) {
    vector<RangedMessage> messagesR;
    for (int i=messageRoomRanged[module].size() - 1; i>=0; i--) {
        messagesR.push_back(messageRoomRanged[module][i]);
    }
    messageRoomRanged[module].clear();
    return messagesR;
}
/**
 *	@brief	retrieves messages for a given module
 *	@param 	module 	name of module
 *	@return	messages fromm module's message queue
 */
vector<Message> AReBotsManipulatorGameMode::getMessages(int module) {
    vector<Message> messages;
    for (int i=messageRoom[module].size() - 1; i>=0; i--) {
        messages.push_back(messageRoom[module][i]);
    }
    messageRoom[module].clear();
    return messages;
}
/**
 *	@brief	Clears (deletes) the messages of a module with the given name
 *	@param 	module 	name of the module
 */
void AReBotsManipulatorGameMode::clearMessages(int module) {
    messageRoom[module].clear();
}

/**
 *	@brief	retrieves the last message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent message in module's queue of messages
 */
KinematicsMessage AReBotsManipulatorGameMode::getLastKinematicsMessage(int module) {
    KinematicsMessage m = messageRoomKinematics[module].back();
    messageRoomKinematics[module].pop_back();
    return m;
}

/**
 *	@brief	retrieves messages for a given module
 *	@param 	module 	name of module
 *	@return	messages fromm module's message queue
 */
vector<KinematicsMessage> AReBotsManipulatorGameMode::getKinematicsMessages(int module) {
    vector<KinematicsMessage> messages;
    for (int i=messageRoomKinematics[module].size() - 1; i>=0; i--) {
        messages.push_back(messageRoomKinematics[module][i]);
    }
    messageRoomKinematics[module].clear();
    return messages;
}
/**
 *	@brief	retrieves the last message sent to the module with the given name
 *	@param 	module 	name of module
 *	@return	most recent message in module's queue of messages
 */
TreeMessage AReBotsManipulatorGameMode::getLastTreeMessage(int module) {
    TreeMessage m = messageRoomSuperBotTree[module].back();
    messageRoomSuperBotTree[module].pop_back();
    return m;
}

/**
 *	@brief	retrieves messages for a given module
 *	@param 	module 	name of module
 *	@return	messages fromm module's message queue
 */
vector<TreeMessage> AReBotsManipulatorGameMode::getTreeMessages(int module) {
    vector<TreeMessage> messages;
    for (int i=messageRoomSuperBotTree[module].size() - 1; i>=0; i--) {
        messages.push_back(messageRoomSuperBotTree[module][i]);
    }
    messageRoomSuperBotTree[module].clear();
    return messages;
}


