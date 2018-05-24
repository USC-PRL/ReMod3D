// Fill out your copyright notice in the Description page of Project Settings.

 
#include "SixDDockingGameMode.h"



//#pragma mark -
//#pragma Superbot Docking
/**
 * @brief get corrective docking transform
 * @param d1 dock 1
 * @param d2 dock 2
 * @return corrective trnasform
 */
FTransform ASixDDockingGameMode::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
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
void ASixDDockingGameMode::DockTwoModules(ASuperBotModule* sm1, ASuperBotModule* sm2, ModuleDockFace d1, ModuleDockFace d2) {
    
    //TODO: use root hierarchy somehow?
    connections[sm1->GetIDNumber()][d1] = sm2->GetDocks()[d2];
    connections[sm2->GetIDNumber()][d2] = sm1->GetDocks()[d1];
    sm1->SetDockEngaged(d1, true);
    sm2->SetDockEngaged(d2, true);
    ModuleMotorVector mv1 = sm1->GetJointAngles();
    ModuleMotorVector mv2 = sm2->GetJointAngles();
    sm1->GetRootComponent()->AttachTo(sm2->GetRootComponent(), "", EAttachLocation::SnapToTarget, true);
    //sm1->AttachRootComponentTo(sm2->GetRootComponent(),"",EAttachLocation::SnapToTarget, true);
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
FTransform ASixDDockingGameMode::GetTransformOfEndEffector(std::vector<ModuleMotorVector> JAngles) {
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
float ASixDDockingGameMode::Fitness(PSOParticle P) {
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
float ASixDDockingGameMode::BBPSOFitness(BranchBoundParticle P, vector<float> st, vector<float> tar) {
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
ASixDDockingGameMode::ASixDDockingGameMode(const FObjectInitializer& ObjectInitializer)
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
bool ASixDDockingGameMode::IsInSelfCollision(FTransform ToGround, std::vector<ModuleMotorVector> JAngles) {
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
bool ASixDDockingGameMode::IsInCollisionWithGround(FTransform ToGround,
                                                         std::vector<ModuleMotorVector> JAngles, float GroundZVal, float Thresh) {
    return false;
}
/**
 * @brief get bounding spheres for joint angles
 * @param mvs motor vectors
 * @return bounding spheres
 */
vector<ABoundingSphere*> ASixDDockingGameMode::GetBoundingSpheresForJointAngles(FTransform ToGround,
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
void ASixDDockingGameMode::Tick(float DeltaSeconds) {
    
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
        //EndEffectorFrame = GetWorld()->SpawnActor<AReferenceFrameActor>(modules[0]->GetMasterInnerMesh()-//>GetComponentTransform().GetLocation(),
          //                                                              FRotator(modules[0]->GetMasterInnerMesh()->//GetComponentTransform().GetRotation()));
        
        
        GoalEndEffectorFrame = NULL;
        FTransform t;
        if (ToMasterKinematics) {
            t = SuperbotKinematics::computeTransformToDock(modules[0]->GetJointAngles(),DOCK_1)*ASuperBotModule::SuperbotFix*modules[0]->GetMasterInnerMesh()->GetComponentTransform();
        } else {
            t = SuperbotKinematics::computeTransformToDock(modules[0]->GetJointAngles(),DOCK_0)*ASuperBotModule::SuperbotFix*modules[0]->GetMasterInnerMesh()->GetComponentTransform();
        }
        ToGroundTransform = t;
        //ToGroundFrame = GetWorld()->SpawnActor<AReferenceFrameActor>(ToGroundTransform.GetLocation(),
         //                                                            FRotator(ToGroundTransform.GetRotation()));
    } else {
        for (int i=0; i<modules.size(); i++) {
            modules[i]->SetModuleBehavior(NULL);
        }
        std::vector<ModuleMotorVector> mvs(3);
        mvs[0] = ModuleMotorVector(-75,0,80);
        mvs[1] = ModuleMotorVector(55,0,-55);
        mvs[2] = ModuleMotorVector(0,20,0);
        modules[0]->SetJointAngles(mvs[2]);
        for (int i=1; i<mvs.size() + 1; i++) {
            modules[i]->GetMasterInnerMesh()->WakeAllRigidBodies();
            modules[i]->GetSlaveInnerMesh()->WakeAllRigidBodies();
            modules[i]->GetMasterOuterMesh()->WakeAllRigidBodies();
            modules[i]->GetSlaveOuterMesh()->WakeAllRigidBodies();
            modules[i]->SetJointAngles(mvs[i-1]);
        }
    }
}


