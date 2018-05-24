// Fill out your copyright notice in the Description page of Project Settings.

 
#include "FKIKBehavior.h"

/**
 * @brief constructor
 */
FKIKBehavior::FKIKBehavior() {
    Init();
    this->Name = "FKIK";
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
}
/**
 * @brief compute distance between point1 and point2
 * @param point1 point number 1
 * @param point2 point number 2
 * @return euclidean distance between point1 and point2
 */
float FKIKBehavior::Distance(std::vector<float> point1, std::vector<float> point2) {
    float distance = 0.0;
    for (int i=0; i<point1.size(); i++) {
        distance += (point1[i] - point2[i])*(point1[i] - point2[i]);
    }
    return sqrtf(distance);
}
/**
 * @brief state valid
 * @param point point to check
 * @return true if state valid false otherwise
 */
bool FKIKBehavior::StateValid(std::vector<float> point) {
    return !CollisionFunction(point);
}
/**
 * @brief fitness for PASO
 * @param P PSO particle
 * @param st start vector
 * @param tar target vector
 */
float FKIKBehavior::FitnessPSO(PSOParticle P, std::vector<float> start, std::vector<float> target) {
    float DistanceError = Distance(P.getPosition(), target);
    int CollisionVal = CollisionFunction(P.getPosition());
    return DistanceError + 1000*CollisionVal;
}
/**
 * @brief destructor
 */
FKIKBehavior::~FKIKBehavior(){}
/**
 * @brief set joints distributed
 * @param JAngles joint angles
 */
void FKIKBehavior::SetJointAnglesDistributed(std::vector<float> JAngles) {
    TreeMessage tcm("SetJoints",st.GetVertices().size(),st.GetVertices().size());
    for (int i=0; i<st.GetVertices().size(); i++) {
        double a0 = JAngles[3*i + 0];
        double a1 = JAngles[3*i + 1];
        double a2 = JAngles[3*i + 2];
        if (i == 0) {
            AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_0,a0));
            AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_1,a1));
            AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_2,a2));
        } else {
            ModuleNode* cNode = st.GetVertices()[i];
            tcm.N = cNode;
            vector<float> cAngles(3);
            cAngles[0] = a0;
            cAngles[1] = a1;
            cAngles[2] = a2;
            tcm.CommandAngles = cAngles;
            if (cNode->GetDockFacePath().size() > 2) {
                tcm.Command = "SetJointsI";
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first),tcm));
            } else {
                tcm.Command = "SetJoints";
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first),tcm));
            }
        }
    }
}
/**
 * @brief set joints distributed
 * @param JAngles joint angles
 */
void FKIKBehavior::ConnectNewEffector() {
    cout<<"Selected End Effector: "<<SelectedEndEffector<<endl;
    TreeMessage tcm("ConnectEffector",st.GetVertices().size(),st.GetVertices().size());
    ModuleNode* cNode = st.GetVertices()[SelectedEndEffector];
    tcm.N = cNode;
    if (cNode->GetDockFacePath().size() > 2) {
        tcm.Command = "ConnectEffectorI";
        AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first),tcm));
    } else {
        tcm.Command = "ConnectEffector";
        AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)cNode->GetDockFacePath()[0].first),tcm));
    }
}
/**
 * @brief initialize kinematic tree
 * @param aEE am i end effector?
 * @param cTG connected to ground?
 */
void FKIKBehavior::InitializeKinematicTree() {
    ModuleNode *rootNode = new ModuleNode(CurrentAngles,0,FTransform(FVector(0,0,0)));
    rootNode->SetDiscoveredLevel(0 );
    rootNode->SetDiscoveredDock(-1);
    rootNode->SetDiscoveringNode(NULL);
    rootNode->SetAmIEndEffector(false);
    rootNode->SetConnectedToGround(this->AmIEngagedToGround);
    if (CurrentDockEngagedToGroundStatus[DOCK_0]) {
        rootNode->SetDockFaceConnectedToGround(DOCK_0);
    } else if (CurrentDockEngagedToGroundStatus[DOCK_1]) {
        rootNode->SetDockFaceConnectedToGround(DOCK_1);
    }
    ModuleMotorVector RAngles(CurrentAngles[0],CurrentAngles[1],CurrentAngles[2]);
    rootNode->SetTransform(SuperbotKinematics::computeTransformFromDock(RAngles, rootNode->GetDockFaceConnectedToGround()));
    ModNodes[rootNode->GetName()] = rootNode;
    st.InitializeTree(rootNode);
    st.AddNodeToBFSQueue(rootNode);
    HasBeenInitialized = true;
    this->CanSendMessage = true;
}
/**
 * @brief discover kinematic structure
 */
void FKIKBehavior::DiscoverKinematicStructure() {
    ModuleNode *cNode = st.GetQueueFront();
    TreeMessage tm = TreeMessage("StateProbe", st.GetVertices().size(),st.GetVertices().size());
    if (CurrentModel.GetCurrentState().GetIDNumber() == 0 && ShouldPrintDiscovery) {
        cout<<"Module Num: 0"<<endl;
        cout<<cNode->GetName()<<endl;
        cout<<cNode->GetCurrentDock();
        cout<<endl<<endl;
    }
    if (st.GetQueueSize() > 0 && cNode->GetCurrentDock() < 6) {
        tm.N = cNode;
        if (cNode->GetDockFacePath().size() > 0) {
            tm.Command = "StateProbeI";
            tm.CurrentPathElement = 0;
            tm.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)cNode->GetDockFacePath()[tm.CurrentPathElement].first,0));
            if (cNode->GetDiscoveredLevel() < 15) {
                CanSendMessage = false;
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>
                                     (GetTreeActionForDock(cNode->GetDockFacePath()[tm.CurrentPathElement].first),tm));
            } else {
                if (cNode) cNode->IncrementCurrentDock();
            }
        } else {
            if (CurrentDockEngagedStatus[cNode->GetCurrentDock()]) {
                this->CanSendMessage = false;
                cNode->SetDiscoveredDock(cNode->GetCurrentDock());
                tm.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)cNode->GetCurrentDock(),0));
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>
                                     (GetTreeActionForDock((ModuleDockFace)cNode->GetCurrentDock()),tm));
            } else {
                CanSendMessage = true;
                if (cNode) cNode->IncrementCurrentDock();
            }
        }
    }
    
    if (st.GetQueueSize() > 0 && cNode->GetCurrentDock() >= 6) {
        this->CanSendMessage = true;
        FVector p = cNode->GetTransform().GetLocation();
        st.AddCenterOfMassTotal(p);
        st.SetCenterOfMass(st.GetCenterOfMassTotal()/st.GetVertices().size());
        st.PopBFSQueue();
    }
}
/**
 * @brief process message
 * @param aEE am i end effector?
 * @param cTG connected to ground?
 * @param messages messages vector
 */
void FKIKBehavior::ProcessMessages(vector<TreeMessage> messages) {
    for (int i=0; i<messages.size(); i++) {
        TreeMessage mes = messages[i];
        if (mes.Command.compare("ConnectEffector") == 0) {
            cout<<"Will Connect Effector at Module: "<<mes.N->GetName()<<endl;
            if (CurrentDockEngagedStatus[DOCK_1]) {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_FRONT_DOCK_TO_GROUND,true));
            } else {
                AddDockAction(std::pair<ModuleAction, bool>(ENGAGE_BACK_DOCK_TO_GROUND,true));
            }
        } else if (mes.Command.compare("ConnectEffectorI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
                mes.Command = "ConnectEffectorI";
            } else {
                mes.Command = "ConnectEffector";
            }
            if (mes.N->GetDockFacePath().size() > 0) {
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(d),mes));
            }
        }else if (mes.Command.compare("StateProbe") == 0) {
            mes.MV.push_back(ModuleMotorVector(CurrentAngles[0],CurrentAngles[1],CurrentAngles[2]));
            mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(), 0));
            mes.CurrentPathElement = mes.DockFacePath.size() - 1;
            mes.DockConnectedStatuses = CurrentDockEngagedStatus;
            mes.Command = "ReturnState";
            mes.AmIEndEffector = this->AmIEndEffector;
            mes.ConnectedToGround = this->AmIEngagedToGround;
            if (mes.N->GetDockFacePath().size() > 0) {mes.Command = "ReturnStateI";}
            AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()),mes));
        } else if (mes.Command.compare("StateProbeI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size()) {
                mes.Command = "StateProbeI";
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
            } else {
                mes.Command = "StateProbe";
                d = (ModuleDockFace)mes.N->GetCurrentDock();
            }
            
            if (CurrentDockEngagedStatus[d] && d != mes.GetReceivingDock().GetDockFace()) {
                mes.MV.push_back(ModuleMotorVector(CurrentAngles[0],CurrentAngles[1],CurrentAngles[2]));
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(),0));
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)d,0));
                if (mes.Command.compare("StateProbe") == 0) {
                    mes.N->SetDiscoveredDock(mes.N->GetCurrentDock());
                }
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(d),mes));
            } else {
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(),0));
                mes.CurrentPathElement = mes.DockFacePath.size() - 1;
                if (mes.CurrentPathElement > 1) {
                    mes.Command = "ReturnStateFI";
                } else {
                    mes.Command = "ReturnStateF";
                }
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()),mes));
            }
        } else if (mes.Command.compare("ReturnStateI") == 0) {
            mes.CurrentPathElement -= 2;
            if (mes.CurrentPathElement <= 1) {
                mes.Command = "ReturnState";
            } else {
                mes.Command = "ReturnStateI";
            }
            AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(mes.N->GetDockFacePath()[mes.CurrentPathElement].first),mes));
        } else if (mes.Command.compare("ReturnState") == 0) {
            this->CanSendMessage = true;
            std::vector<float> angles = std::vector<float>(3);
            angles[0] = CurrentAngles[0];angles[1] = CurrentAngles[1];angles[2] = CurrentAngles[2];
            FTransform CurrentTransform = FTransform(FVector(0,0,0));
            ModuleMotorVector mv = ModuleMotorVector(angles[0],angles[1],angles[2]);
            int dockCounter = 0;
            CurrentTransform = st.GetVertices()[0]->GetTransform();
            for (int j=0; j<mes.MV.size(); j++) {
                ModuleDockFace d1 = mes.DockFacePath[dockCounter++].first;
                ModuleDockFace d2 = mes.DockFacePath[dockCounter++].first;
                FTransform trans1 = SuperbotKinematics::computeTransformToDock(mv, d1);
                angles[0] = mes.MV[j].Motor0Angle;angles[1] = mes.MV[j].Motor1Angle;angles[2] = mes.MV[j].Motor2Angle;
                mv = ModuleMotorVector(angles[0],angles[1],angles[2]);
                FTransform trans2 = SuperbotKinematics::computeTransformFromDock(mv,d2);
                CurrentTransform = trans2*GetCorrectiveDockingTransform(d1,d2)*trans1*CurrentTransform;
                if (!CurrentTransform.IsValid()) {
                    cout<<"Problem"<<endl;
                }
            }
            mes.N->IncrementCurrentDock();
            ModuleNode *n = new ModuleNode(angles, mes.GetNeighborNumID(), CurrentTransform);
            n->SetDiscoveredLevel(mes.DockFacePath.size()/2);
            n->SetDockFacePath(mes.DockFacePath);
            n->SetDiscoveredDock(mes.N->GetDiscoveredDock());
            n->SetDiscoveringNode(mes.N);
            n->SetDockEngagedStatuses(mes.DockConnectedStatuses);
            n->SetJointAngles(angles);
            n->SetAmIEndEffector(mes.AmIEndEffector);
            n->SetConnectedToGround(mes.ConnectedToGround);
            st.AddEdge(mes.N->GetName(),n->GetName(), mes.DockFacePath[mes.DockFacePath.size() - 2].first,mes.DockFacePath[mes.DockFacePath.size() - 1].first);
            st.AddNodeToBFSQueue(n);
            st.AddVertex(n);
            ModNodes[mes.GetNeighborNumID()] = n;
        } else if (mes.Command.compare("ReturnStateF") == 0) {
            this->CanSendMessage = true;
            mes.N->IncrementCurrentDock();
        } else if (mes.Command.compare("ReturnStateFI") == 0) {
            mes.CurrentPathElement -= 2;
            ModuleDockFace d = (ModuleDockFace)mes.DockFacePath[mes.CurrentPathElement].first;
            if (mes.CurrentPathElement <= 1) {
                mes.Command = "ReturnStateF";
            } else {
                mes.Command = "ReturnStateFI";
            }
            AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(d),mes));
        } else if (mes.Command.compare("Reset") == 0) {
            this->ShouldSetTreeDirty = true;
            //cout<<"Received Reset"<<endl;
            TreeMessage tm = TreeMessage("Reset",st.GetVertices().size(),0);
            for (int j=0; j<6; j++) {
                if (CurrentDockEngagedStatus[j] && j != mes.GetReceivingDock().GetDockFace()) {
                    AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)j),tm));
                }
            }
        } else if (mes.Command.compare("SetJoints") == 0) {
            AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_0,mes.CommandAngles[0]));
            AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_1,mes.CommandAngles[1]));
            AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_2,mes.CommandAngles[2]));
        } else if (mes.Command.compare("SetJointsI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size() - 2) {
                mes.Command = "SetJointsI";
            } else {
                mes.Command = "SetJoints";
            }
            if (mes.N->GetDockFacePath().size() > 0) {
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(d),mes));
            }
        }
    }
}
/**
 * @brief update the current joint angles
 */
void FKIKBehavior::UpdateCurrentAngles() {
    float motor0Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor0Angle;
    float motor1Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor1Angle;
    float motor2Angle = CurrentModel.GetCurrentState().GetJointAngles().Motor2Angle;
    if (this->ProgramCounter == 0) {
        CurrentAngles[0] = motor0Angle;
        CurrentAngles[1] = motor1Angle;
        CurrentAngles[2] = motor2Angle;
        CAngleDiffs[0] = 0;
        CAngleDiffs[1] = 0;
        CAngleDiffs[2] = 0;
    } else {
        CAngleDiffs[0] += motor0Angle - CurrentAngles[0];
        CAngleDiffs[1] += motor1Angle - CurrentAngles[1];
        CAngleDiffs[2] += motor2Angle - CurrentAngles[2];
        CurrentAngles[0] = motor0Angle;
        CurrentAngles[1] = motor1Angle;
        CurrentAngles[2] = motor2Angle;
    }
}
/**
 * @brief update dock engaged status
 */
void FKIKBehavior::UpdateDockEngagedStatus() {
    bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_0];
    bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_1];
    bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_2];
    bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_3];
    bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_4];
    bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedStatus()[DOCK_5];
    
    if (this->ProgramCounter == 0) {
        CDockDiffs[DOCK_0] = 0;
        CDockDiffs[DOCK_1] = 0;
        CDockDiffs[DOCK_2] = 0;
        CDockDiffs[DOCK_3] = 0;
        CDockDiffs[DOCK_4] = 0;
        CDockDiffs[DOCK_5] = 0;
        this->CurrentDockEngagedStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedStatus[DOCK_5] = currentDock5;
    } else {
        CDockDiffs[DOCK_0] = CurrentDockEngagedStatus[DOCK_0] - currentDock0;
        CDockDiffs[DOCK_1] = CurrentDockEngagedStatus[DOCK_1] - currentDock1;
        CDockDiffs[DOCK_2] = CurrentDockEngagedStatus[DOCK_2] - currentDock2;
        CDockDiffs[DOCK_3] = CurrentDockEngagedStatus[DOCK_3] - currentDock3;
        CDockDiffs[DOCK_4] = CurrentDockEngagedStatus[DOCK_4] - currentDock4;
        CDockDiffs[DOCK_5] = CurrentDockEngagedStatus[DOCK_5] - currentDock5;
        this->CurrentDockEngagedStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedStatus[DOCK_5] = currentDock5;
    }
}
/**
 * @brief update dock engaged status
 */
void FKIKBehavior::UpdateDockEngagedToGroundStatus() {
    bool currentDock0 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_0];
    bool currentDock1 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_1];
    bool currentDock2 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_2];
    bool currentDock3 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_3];
    bool currentDock4 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_4];
    bool currentDock5 = CurrentModel.GetCurrentState().GetDocksEngagedToGroundStatus()[DOCK_5];
    if (this->ProgramCounter == 0) {
        CDockToGroundDiffs[DOCK_0] = 0;
        CDockToGroundDiffs[DOCK_1] = 0;
        CDockToGroundDiffs[DOCK_2] = 0;
        CDockToGroundDiffs[DOCK_3] = 0;
        CDockToGroundDiffs[DOCK_4] = 0;
        CDockToGroundDiffs[DOCK_5] = 0;
        this->CurrentDockEngagedToGroundStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedToGroundStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedToGroundStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedToGroundStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedToGroundStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedToGroundStatus[DOCK_5] = currentDock5;
    } else {
        CDockToGroundDiffs[DOCK_0] = CurrentDockEngagedToGroundStatus[DOCK_0] - currentDock0;
        CDockToGroundDiffs[DOCK_1] = CurrentDockEngagedToGroundStatus[DOCK_1] - currentDock1;
        CDockToGroundDiffs[DOCK_2] = CurrentDockEngagedToGroundStatus[DOCK_2] - currentDock2;
        CDockToGroundDiffs[DOCK_3] = CurrentDockEngagedToGroundStatus[DOCK_3] - currentDock3;
        CDockToGroundDiffs[DOCK_4] = CurrentDockEngagedToGroundStatus[DOCK_4] - currentDock4;
        CDockToGroundDiffs[DOCK_5] = CurrentDockEngagedToGroundStatus[DOCK_5] - currentDock5;
        this->CurrentDockEngagedToGroundStatus[DOCK_0] = currentDock0;
        this->CurrentDockEngagedToGroundStatus[DOCK_1] = currentDock1;
        this->CurrentDockEngagedToGroundStatus[DOCK_2] = currentDock2;
        this->CurrentDockEngagedToGroundStatus[DOCK_3] = currentDock3;
        this->CurrentDockEngagedToGroundStatus[DOCK_4] = currentDock4;
        this->CurrentDockEngagedToGroundStatus[DOCK_5] = currentDock5;
    }
}
/**
 * @brief get kinematics action for dock face
 * @param d dock face
 * @return Superbot action
 */
ModuleAction FKIKBehavior::GetKinematicsActionForDock(ModuleDockFace d) {
    if (d == DOCK_0) {
        return SEND_KINEMATICS_MESSAGE_FRONT_DOCK;
    } else if (d == DOCK_1) {
        return SEND_KINEMATICS_MESSAGE_BACK_DOCK;
    } else if (d == DOCK_2) {
        return SEND_KINEMATICS_MESSAGE_LEFT_DOCK;
    } else if (d == DOCK_3) {
        return SEND_KINEMATICS_MESSAGE_RIGHT_DOCK;
    } else if (d == DOCK_4) {
        return SEND_KINEMATICS_MESSAGE_UP_DOCK;
    } else if (d == DOCK_5) {
        return SEND_KINEMATICS_MESSAGE_DOWN_DOCK;
    }
    return SEND_KINEMATICS_MESSAGE_FRONT_DOCK;
}
/**
 * @brief get kinematics action for dock face
 * @param d dock face
 * @return Superbot action
 */
ModuleAction FKIKBehavior::GetTreeActionForDock(ModuleDockFace d) {
    if (d == DOCK_0) {
        return SEND_TREE_MESSAGE_FRONT_DOCK;
    } else if (d == DOCK_1) {
        return SEND_TREE_MESSAGE_BACK_DOCK;
    } else if (d == DOCK_2) {
        return SEND_TREE_MESSAGE_LEFT_DOCK;
    } else if (d == DOCK_3) {
        return SEND_TREE_MESSAGE_RIGHT_DOCK;
    } else if (d == DOCK_4) {
        return SEND_TREE_MESSAGE_UP_DOCK;
    } else if (d == DOCK_5) {
        return SEND_TREE_MESSAGE_DOWN_DOCK;
    }
    return SEND_TREE_MESSAGE_FRONT_DOCK;
}

/**
 * @brief get the transforms of modules for joint angles
 * @param Mods modules
 * @param JAngles joint angles
 * @return transform of modules in tree
 */
vector<FTransform> FKIKBehavior::GetTransformsOfModulesForJointAngles(std::vector<ModuleNode*> Mods,
                                                                      std::vector<float> JAngles) {
    vector<FTransform> Transforms(Mods.size());
    vector<ModuleMotorVector> MVS(Mods.size());
    std::queue<ModuleNode*> SearchQueue;
    SearchQueue.push(Mods[0]);
    vector<bool> Discovered(Mods.size());
    for (int i=0; i<Mods.size(); i++) {
        Discovered[i] = false;
        Transforms[i] = FTransform(FVector(0,0,0));
    }
    for (int i=0; i<Mods.size(); i++) {MVS[i] = ModuleMotorVector(JAngles[3*i + 0],JAngles[3*i + 1],JAngles[3*i + 2]);}
    
    int CurrentDock = 0;
    bool AmIEngagedToGroundFront = CurrentDockEngagedToGroundStatus[DOCK_0];
    bool AmIEngagedToGroundBack = CurrentDockEngagedToGroundStatus[DOCK_1];
    if (AmIEngagedToGroundFront) {
        Transforms[0] = SuperbotKinematics::computeTransformFromDock(MVS[0], DOCK_0);
    } else if (AmIEngagedToGroundBack) {
        Transforms[0] = SuperbotKinematics::computeTransformFromDock(MVS[0], DOCK_1);
    }
    for (int i=1; i<st.GetVertices().size(); i++) {
        FTransform CurrentTransform = Transforms[0];
        std::vector<int> P = GetPathToRootFromNode(st.GetVertices()[i]);
        std::vector<std::pair<ModuleDockFace, int> > DP = st.GetVertices()[i]->GetDockFacePath();
        for (int j=1; j<P.size(); j++) {
            ModuleDockFace d1 = DP[2*j-2].first;
            ModuleDockFace d2 = DP[2*j-1].first;
            FTransform trans1 = SuperbotKinematics::computeTransformToDock(MVS[P[j-1]],d1);
            FTransform trans2 =SuperbotKinematics::computeTransformFromDock(MVS[P[j]],d2);
            CurrentTransform = trans2*GetCorrectiveDockingTransform(d1, d2)*trans1*CurrentTransform;
            Transforms[i] = CurrentTransform;
        }
    }
    return Transforms;
}
/**
 * @brief get path to root from node
 * @param n superbot module node
 * @return path
 */
std::vector<int> FKIKBehavior::GetPathToRootFromNode(ModuleNode* n) {
    std::vector<int> path;
    ModuleNode* CNode = n;
    path.push_back(n->GetName());
    while (CNode->GetDiscoveringNode()) {
        CNode = CNode->GetDiscoveringNode();
        path.push_back(CNode->GetName());
    }
    std::reverse(path.begin(), path.end());
    return path;
}
/**
 * @brief get corrective docking transform
 * @param d1 dock 1
 * @param d2 dock 2
 * @return corrective trnasform
 */
FTransform FKIKBehavior::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
    if (d1 == DOCK_0 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI));
    } else if (d1 == DOCK_1 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI));
    } else if (d1 == DOCK_0 && d2 == DOCK_2) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_2 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_3 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_0 && d2 == DOCK_3) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_1 && d2 == DOCK_2) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_2 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_3 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_1 && d2 == DOCK_3) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
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
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_5 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    }
    return FTransform(FVector(0,0,0));
}
/**
 * @brief get kinematic graph
 * @return get kinematic graph
 */
KinematicGraph FKIKBehavior::GetKinematicGraph() {
    return this->KG;
}
/**
 * @brief get superbot module tree
 */
ModuleTree FKIKBehavior::GetSuperBotTree() {
    return this->st;
}
/**
 * @brief should reinitialize program ?
 * @return whether or not we need to re init program
 */
bool FKIKBehavior::ShouldReInit() {
    return false;
}
/**
 * @brief get the selected end effector
 */
ModuleDockFace FKIKBehavior::GetEndEffectorDockFace() {
    return EEDock;
}
/**
 * @brief initiate inverse kinematics
 */
void FKIKBehavior::InitiateIK() {
    HaveInitiatedIK = true;
    std::vector<int> PossibleEndEffectors;
    for (int i=1; i<st.GetVertices().size(); i++) {
        ModuleNode *smn = st.GetVertices()[i];
        if (smn->GetAmIEndEffector()) {
            PossibleEndEffectors.push_back(i);
        }
    }
    if (CurrentDockEngagedToGroundStatus[0]) {
        GDock = DOCK_0;
    } else if (CurrentDockEngagedToGroundStatus[1]) {
        GDock = DOCK_1;
    }
    
    for (int i=0; i<st.GetVertices().size(); i++) {
        ModuleNode *smn = st.GetVertices()[i];
        if (smn->GetConnectedToGround()) {
            GroundModule = smn->GetName();
        }
    }
    ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                  st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                  st.GetVertices()[GroundModule]->GetJointAngles()[2]);
    if (PossibleEndEffectors.size() > 1) {
        std::uniform_int_distribution<> posRand(0,PossibleEndEffectors.size() - 1);
        int RandEffector = posRand(Generator);
        cout<<"Chose end effector "<<PossibleEndEffectors[RandEffector]<<endl;
        SelectedEndEffector = PossibleEndEffectors[RandEffector];
        ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
        if (LastDockFace == DOCK_0) {
            EEDock = DOCK_1;
        } else {
            EEDock = DOCK_0;
        }
    } else if (PossibleEndEffectors.size() == 1) {
        SelectedEndEffector = PossibleEndEffectors[0];
        ModuleDockFace LastDockFace = (ModuleDockFace)st.GetVertices()[SelectedEndEffector]->GetDockFacePath()[st.GetVertices()[SelectedEndEffector]->GetDockFacePath().size() - 1].first;
        if (LastDockFace == DOCK_0) {
            EEDock = DOCK_1;
        } else {
            EEDock = DOCK_0;
        }
    } else {
        SelectedEndEffector = -1;
    }
    TActorIterator<ADirectionActor> DirectionActorIt = TActorIterator<ADirectionActor>(this->World);
    bool DirectionSet = false;
    if (DirectionActorIt) {
        TargetRandVector = (*DirectionActorIt)->GetDirection();
        TargetYaw = (*DirectionActorIt)->GetYaw();
        DirectionSet = true;
    }
    FTransform FullBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround,GDock)*
    ASuperBotModule::SuperbotFix*SModule->GetMasterInnerMesh()->GetComponentTransform();
    
    FTransform GroundTransform = Floor->GetTransform();
    GroundTransform.SetScale3D(FVector(1.0,1.0,1.0));
    
    FTransform BaseToGround = GroundTransform*FullBaseTransform.Inverse();
    BaseToGround = FTransform(FQuat(FVector(0,1,0),-M_PI_2))*BaseToGround;
    FTransform LocalBaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround,GDock);
    ModuleBaseToGroundTransform = BaseToGround;
    FTransform InvV = FTransform(FVector(0,ModuleBaseToGroundTransform.Inverse().GetLocation().Y,
                                 ModuleBaseToGroundTransform.Inverse().GetLocation().Z));
    ModuleBaseToGroundTransform = InvV*BaseToGround;
    ActualGroundTransform = BaseToGround*LocalBaseTransform;
    
    if (SelectedEndEffector != -1) {
        std::uniform_real_distribution<> Rand2DDirDist(-100,100);
        float StepSize = 400;
        FVector RandDir = FVector(0,Rand2DDirDist(Generator),Rand2DDirDist(Generator));
        RandDir.Normalize();
        std::uniform_real_distribution<> Rand2DAngleDist(-M_PI,M_PI);
        FTransform BToG = FTransform(BaseToGround.GetRotation(), FVector(BaseToGround.GetLocation().X,
                                                                         LocalBaseTransform.GetLocation().Y,
                                                                         LocalBaseTransform.GetLocation().Z));
        if (!DirectionSet) {
            TargetRandVector = RandDir;
        }
        std::vector<std::pair<float,float> > posB(st.GetVertices().size()*3);
        std::vector<std::pair<float,float> > velB(st.GetVertices().size()*3);
        for (int i=0; i<st.GetVertices().size()*3; i++)
        {posB[i] = std::pair<float,float>(-90,90);velB[i] = std::pair<float,float>(-90,90);}
        SolutionPos = vector<float>(st.GetVertices().size()*3);
        PSOWorker = FBBPSOWorker::BBPSOInit(50,50,st.GetVertices().size()*3,posB,velB,3.0,
                                            std::bind(&FKIKBehavior::Fitness,this,
                                            std::placeholders::_1,std::placeholders::_2,std::placeholders::_3),
                                            std::vector<float> {0,200,400,100},std::vector<float> {0,200,400,100},
                                            SolutionPos,&SolutionFitness);
        HaveInitiatedIK = true;
    } else {
        PS = NULL;
    }
}
/**
 * @brief get module base to ground transform
 * @return module base to ground transform
 */
FTransform FKIKBehavior::GetModuleBaseToGroundTransform() {
    return ModuleBaseToGroundTransform;
}
/**
 * @brief get the selected end effector
 */
int FKIKBehavior::GetSelectedEndEffector() {
    return SelectedEndEffector;
}
/**
 * @brief get target transform
 * @return target transform
 */
FTransform FKIKBehavior::GetTargetTransform() {
    return this->TargetTransform;
}
/**
 * @brief reinit program
 */
void FKIKBehavior::Init() {
    this->NeighborAngles = std::vector<std::vector<float> >(6);
    for (int i=0; i<6; i++) {
        this->NeighborAngles[i] = std::vector<float>(3);
    }
    for (int i=0; i<6; i++) {
        for (int j=0; j<3; j++) {
            this->NeighborAngles[i][j] = -1000;
        }
    }
    HasReturned[0] = true;
    HasReturned[1] = true;
    HasReturned[2] = true;
    HasReturned[3] = true;
    HasReturned[4] = true;
    HasReturned[5] = true;
    
    this->CurrentAngles = std::vector<float>(3);
    this->CurrentDockEngagedStatus = std::vector<bool>(6);
    this->CurrentDockEngagedToGroundStatus = std::vector<bool>(6);
    for (int i=0; i<6; i++) {
        this->CurrentDockEngagedStatus[i] = false;
        this->CurrentDockEngagedToGroundStatus[i] = false;
    }
    this->CurrentDepth = 0;
    this->CAngleDiffs = std::vector<float>(3);
    this->CDockDiffs = std::vector<int>(6);
    this->CDockToGroundDiffs = std::vector<int>(6);
    for (int i=0; i<6; i++) {
        this->CDockDiffs[i] = 0;
        this->CDockToGroundDiffs[i] = 0;
    }
    this->CAngleDiffs[0] = 0.0;
    this->CAngleDiffs[1] = 0.0;
    this->CAngleDiffs[2] = 0.0;
}
/**
 * @brief update engaged to ground
 */
void FKIKBehavior::UpdateEngagedToGround() {
    AmIEngagedToGround = (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1]);
}
/**
 * @brief update whether or not I am end effector
 */
void FKIKBehavior::UpdateEndEffectorStatus() {
    int numDocksConnected = 0;
    for (int i=0; i<6; i++) {
        numDocksConnected += CurrentDockEngagedStatus[i];
    }
    if (numDocksConnected == 1) {
        AmIEndEffector = true;
    } else {
        AmIEndEffector = false;
    }
}
/**
 * @brief get the selected end effector
 */
int FKIKBehavior::GetGroundModule() {
    return this->GroundModule;
}
/**
 * @brief get the selected end effector
 */
ModuleDockFace FKIKBehavior::GetGroundDockFace() {
    return this->GDock;
}
/**
 * @brief detect self collision
 * @param point point to check
 * @return is position in self collision
 */
bool FKIKBehavior::IsInSelfCollision(std::vector<float> point) {
    vector<ModuleNode*> Mods(st.GetVertices().size());
    for (int i=0; i<st.GetVertices().size(); i++) {
        Mods[i] = st.GetVertices()[i];
    }
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);
    for (int i=0; i<Ts.size(); i++) {
        for (int j=i + 1; j<Ts.size(); j++) {
            FVector DiffVec = Ts[i].GetLocation() - Ts[j].GetLocation();
            if (DiffVec.Size() < 150.0) return true;
        }
    }
    return false;
}
/**
 * @brief constructor
 * @param W world
 */
FKIKBehavior::FKIKBehavior(UWorld* W, std::string NameOfModule) {
    Init();
    this->Name = "FKIK";
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
    this->World = W;
    this->ModuleName = NameOfModule;
    TActorIterator< AStaticMeshActor > ActorIt = TActorIterator< AStaticMeshActor >(World);
    while (ActorIt) {
        if (std::string(TCHAR_TO_UTF8(*(*ActorIt)->GetName())).compare("Floor") == 0) {
            Floor = *ActorIt;
            break;
        }
        ++ActorIt;
    }
    TActorIterator< ASuperBotModule > SuperBotIt = TActorIterator< ASuperBotModule >(World);
    while (SuperBotIt) {
        if ((*SuperBotIt)->GetName().compare(ModuleName) == 0) {
            SModule = *SuperBotIt;
            break;
        }
        ++SuperBotIt;
    }
    cout<<"Init Done"<<endl;
    cout<<"Floor: "<<Floor->GetUniqueID()<<endl;
    cout<<"Module: "<<SModule->GetName()<<endl;
}
/**
 * @brief Get master inner transform of module associated with this program
 * @return master inner transform
 */
FTransform FKIKBehavior::GetMasterInnerTransformForBaseModule() {
    TActorIterator< ASuperBotModule > SuperbotIt = TActorIterator< ASuperBotModule >(World);
    while (SuperbotIt) {
        string str = (*SuperbotIt)->GetName();
        if (str.compare(this->ModuleName) == 0) {
            return (*SuperbotIt)->GetMasterInnerMesh()->GetComponentTransform();
        }
    }
    return FTransform(FVector(-1,-1,-1));
}
/**
 * @brief detect ground collision
 * @param point point to check
 * @return is position in collision with ground
 */
bool FKIKBehavior::IsInCollisionWithGround(std::vector<float> point) {
    vector<ModuleNode*> Mods(st.GetVertices().size());
    ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                  st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                  st.GetVertices()[GroundModule]->GetJointAngles()[2]);
    FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround,GDock);
    for (int i=0; i<st.GetVertices().size(); i++) {Mods[i] = st.GetVertices()[i];}
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, point);

    vector<ModuleMotorVector> mvsFinals;
    vector<ModuleDockFace> mvsDocks;
    for (int i=0; i<st.GetVertices().size(); i++) {
        if (st.GetVertices()[i]->GetAmIEndEffector()) {
            mvsFinals.push_back(ModuleMotorVector(point[3*i + 0],point[3*i + 1],point[3*i + 2]));
            ModuleDockFace D = (ModuleDockFace)st.GetVertices()[i]->GetDockFacePath()[st.GetVertices()[i]->GetDockFacePath().size() - 1].first;
            if (D == DOCK_0) {
                mvsDocks.push_back(DOCK_1);
            } else {
                mvsDocks.push_back(DOCK_0);
            }
        }
    }
    physx::PxTransform transGround;
    physx::PxBoxGeometry groundGeometry;
    if (GDock == DOCK_0) {
        BaseTransform = FTransform(FVector(50,0,0))*BaseTransform;
    } else {
        BaseTransform = FTransform(FVector(-50,0,0))*BaseTransform;
    }
    physx::PxTransform transBase = U2PTransform(FTransform(FVector(-50,0,0))*ActualGroundTransform/*BaseTransform*/);
    groundGeometry = physx::PxBoxGeometry(25,1000,1000);
    for (int i=0; i<Ts.size(); i++) {
        physx::PxTransform transTs = U2PTransform(Ts[i]);
        physx::PxBoxGeometry geomTs(40,40,40);
        if (physx::PxGeometryQuery::overlap(geomTs, transTs, groundGeometry, transBase)) {
            return true;
        }
    }
    BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround,GDock);
    int EECount = 0;
    for (int i=0; i<Mods.size(); i++) {
        if (Mods[i]->GetAmIEndEffector()) {
            FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinals[EECount],mvsDocks[EECount])*
            Ts[i]*BaseTransform;
            EECount++;
            if (mvsDocks[EECount] == DOCK_0) {
                FinalFKActorTrans = FTransform(FVector(-17,0,0))*FinalFKActorTrans;
            } else {
                FinalFKActorTrans = FTransform(FVector(17,0,0))*FinalFKActorTrans;
            }
            physx::PxTransform transTs = U2PTransform(FinalFKActorTrans);
            physx::PxBoxGeometry geomTs = PxBoxGeometry(8,60,60);
            if (physx::PxGeometryQuery::overlap(geomTs, transTs, groundGeometry, transBase)) {
                return true;
            }
        }
    }
    /*for (int i=0; i<Ts.size(); i++) {
        if (fabs(Ts[i].GetLocation().X - BaseTransform.GetLocation().X) < 100.0) {
            return true;
        }
    }*/
    return false;
}
/**
 * @brief plan path to 0
 */
void FKIKBehavior::PlanPathTo0() {
    std::vector<std::pair<float,float> > run(st.GetVertices().size()*3);
    std::vector<std::pair<float,float> > vel(st.GetVertices().size()*3);
    std::vector<float> goal(st.GetVertices().size()*3);
    std::vector<float> start(st.GetVertices().size()*3);
    for (int i=0; i<vel.size(); i++) {
        run[i] = std::pair<float,float>(-90,90);
        vel[i] = std::pair<float,float>(-90,90);
        goal[i] = 0;
    }
    for (int i=0; i<st.GetVertices().size(); i++) {
        start[3*i + 0] = st.GetVertices()[i]->GetJointAngles()[0];
        start[3*i + 1] = st.GetVertices()[i]->GetJointAngles()[1];
        start[3*i + 2] = st.GetVertices()[i]->GetJointAngles()[2];
    }
    PathTo0.clear();
    float FitVal;
    PASOWorker = FPASOWorker::PASOInit(50, 50, st.GetVertices().size()*3, 100, run, vel, 5.0,
                                       std::bind(&FKIKBehavior::FitnessPSO, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                       std::bind(&FKIKBehavior::StateValid, this, std::placeholders::_1),
                                       std::bind(&FKIKBehavior::Distance, this, std::placeholders::_1,
                                                 std::placeholders::_2),
                                       start, goal, PathTo0, &FitVal);
}
/**
 * @brief plan path to goal
 */
void FKIKBehavior::PlanPathToGoal() {
    std::vector<std::pair<float,float> > run(st.GetVertices().size()*3);
    std::vector<std::pair<float,float> > vel(st.GetVertices().size()*3);
    std::vector<float> goal(st.GetVertices().size()*3);
    std::vector<float> start(st.GetVertices().size()*3);
    for (int i=0; i<vel.size(); i++) {
        run[i] = std::pair<float,float>(-90,90);
        vel[i] = std::pair<float,float>(-90,90);
        goal[i] = SolutionPos[i];
    }
    for (int i=0; i<st.GetVertices().size(); i++) {
        start[3*i + 0] = 0;
        start[3*i + 1] = 0;
        start[3*i + 2] = 0;
    }
    Path0ToGoal.clear();
    HaveCompletedPP = false;
    CurrentPathElement = 0;
    float FitVal;
    vector<ModuleNode*> Mods(st.GetVertices().size());
    for (int i=0; i<st.GetVertices().size(); i++) {
        Mods[i] = st.GetVertices()[i];
    }
    BestTransformsFound = GetTransformsOfModulesForJointAngles(Mods, SolutionPos);
    PASOWorker = FPASOWorker::PASOInit(50, 50, st.GetVertices().size()*3, 100, run, vel, 5.0,
                                       std::bind(&FKIKBehavior::FitnessPSO, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                       std::bind(&FKIKBehavior::StateValid, this, std::placeholders::_1),
                                       std::bind(&FKIKBehavior::Distance, this, std::placeholders::_1,
                                                 std::placeholders::_2),
                                       start, goal, Path0ToGoal, &FitVal);
    
    PathTo0.clear();
}
/**
 * @brief fitness function for IK
 * @param P particle
 * @param tar target
 * @return fitness value
 */
float FKIKBehavior::Fitness(BranchBoundParticle P, std::vector<float> start, std::vector<float> target) {
    ModuleMotorVector mvsGround(st.GetVertices()[GroundModule]->GetJointAngles()[0],
                                  st.GetVertices()[GroundModule]->GetJointAngles()[1],
                                  st.GetVertices()[GroundModule]->GetJointAngles()[2]);
    FTransform BaseTransform = SuperbotKinematics::computeTransformToDock(mvsGround,GDock);
    vector<ModuleNode*> Mods(st.GetVertices().size());
    for (int i=0; i<st.GetVertices().size(); i++) {Mods[i] = st.GetVertices()[i];}
    vector<FTransform> Ts = GetTransformsOfModulesForJointAngles(Mods, P.GetPosition());
    ModuleMotorVector mvsFinal = ModuleMotorVector(P.GetPosition()[3*SelectedEndEffector + 0],
                                       P.GetPosition()[3*SelectedEndEffector + 1],
                                       P.GetPosition()[3*SelectedEndEffector + 2]);
    FTransform FinalFKActorTrans = SuperbotKinematics::computeTransformToDock(mvsFinal,GetEndEffectorDockFace())*
    Ts[SelectedEndEffector]*BaseTransform;
    
    FTransform FullTargetTransform;
    FullTargetTransform = ModuleBaseToGroundTransform*BaseTransform;
    if (GDock == DOCK_1 || GDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0,1,0), M_PI))*FullTargetTransform;
    }
    FullTargetTransform = FTransform(FVector(0,0,350))*FTransform(FRotator(0,0,TargetYaw))*FullTargetTransform;
    if (GDock == DOCK_1 || GDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0,1,0), -M_PI))*FullTargetTransform;
    }
    if (EEDock == DOCK_0) {
        FullTargetTransform = FTransform(FQuat(FVector(0,1,0),M_PI),FVector(0,0,0))*FullTargetTransform;
    }
    FRotator DiffRot = FRotator(FullTargetTransform.GetRotation()) - FRotator(FinalFKActorTrans.GetRotation());
    FVector OrientVec = FVector(/*DiffRot.Roll*/0, DiffRot.Pitch, DiffRot.Yaw);
    FVector DiffPos = FullTargetTransform.GetLocation() - FinalFKActorTrans.GetLocation();
    FVector DiffVec2D(0,DiffPos.Y, DiffPos.Z);
    return DiffPos.Size() + OrientVec.Size() + 100*IsInSelfCollision(P.GetPosition()) +
    100*IsInCollisionWithGround(P.GetPosition());
    
}
/**
 * @brief get am i end effector
 * @return am I an end effector
 */
bool FKIKBehavior::GetAmIEndEffector() {
    return this->AmIEndEffector;
}
/**
 * @brief get am i connected to ground
 * @return am I connected to ground
 */
bool FKIKBehavior::GetAmIConnectedToGround() {
    return this->AmIEngagedToGround;
}
/**
 * @brief collision function
 * @param point point to check
 * @return collision (true) or not (false)
 */
bool FKIKBehavior::CollisionFunction(std::vector<float> point) {
    return IsInCollisionWithGround(point) || IsInSelfCollision(point);
}
/**
 * @brief get best transforms found by IK process
 * @return best transforms
 */
std::vector<FTransform> FKIKBehavior::GetBestTransforms() {
    return BestTransformsFound;
}
/**
 * @brief get best (solution) position
 * @return best (solution) position
 */
std::vector<float> FKIKBehavior::GetSolutionPos() {
    return SolutionPos;
}
/**
 * @brief step function of behavior
 * @param jointVals superbot sensor values
 * @param desiredVals desired sensor values
 * @return action values
 */
void FKIKBehavior::Tick(ModuleModel model) {
    ClearAllActions();
    this->CurrentModel = model;
    UpdateCurrentAngles(); /** update current joint angles of this module */
    UpdateDockEngagedStatus(); /** update dock engaged statuses for each dock of this module */
    UpdateDockEngagedToGroundStatus(); /**< update dock engaged statuses for each dock of this module */
    UpdateEngagedToGround(); /**< update engaged to ground */
    UpdateEndEffectorStatus(); /**< update end effector status */
    std::vector<RangedMessage> rms = model.GetCurrentState().GetRangedMessages();
    std::vector<Message> ms = model.GetCurrentState().GetMessages();
    std::vector<KinematicsMessage> kms = model.GetCurrentState().GetKinematicsMessages();
    std::vector<TreeMessage> tms = model.GetCurrentState().GetTreeMessages();
    
    
    int diffTotalDocks = 0;
    for (int i=0; i<6; i++) {
        diffTotalDocks += abs(CDockDiffs[i]);
    }
    int diffTotalDocksToGround = 0;
    for (int i=0; i<6; i++) {
        diffTotalDocksToGround += abs(CDockToGroundDiffs[i]);
    }
    
    if (diffTotalDocksToGround > 0) {
        //cout<<"Change of Base: "<<this->CurrentModel.GetCurrentState().GetIDNumber()<<endl;
    }
    
    if ((fabs(CAngleDiffs[0]) > 1.0 || fabs(CAngleDiffs[1]) > 1.0 || fabs(CAngleDiffs[2]) > 1.0 || abs(diffTotalDocks) > 0) ||
        abs(diffTotalDocksToGround)) {
        CAngleDiffs[0] = 0.0;
        CAngleDiffs[1] = 0.0;
        CAngleDiffs[2] = 0.0;
        CDockDiffs[0] = 0;
        CDockDiffs[1] = 0;
        CDockDiffs[2] = 0;
        CDockDiffs[3] = 0;
        CDockDiffs[4] = 0;
        CDockDiffs[5] = 0;
        CDockToGroundDiffs[0] = 0;
        CDockToGroundDiffs[1] = 0;
        CDockToGroundDiffs[2] = 0;
        CDockToGroundDiffs[3] = 0;
        CDockToGroundDiffs[4] = 0;
        CDockToGroundDiffs[5] = 0;
        if (diffTotalDocksToGround > 0) {
            this->ProgramCounter = 1;
        }
        TreeMessage tm = TreeMessage("Reset",st.GetVertices().size(),0);
        for (int j=0; j<6; j++) {
            if (CurrentDockEngagedStatus[j]) {
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)j),tm));
            }
        }
        this->ShouldSetTreeDirty = true;
        
    }
    
    if (!HasBeenInitialized && (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1])) {
        InitializeKinematicTree();
    }
    
    ProcessMessages(tms);
    
    if (CanSendMessage && (CurrentDockEngagedToGroundStatus[0] || CurrentDockEngagedToGroundStatus[1])) {
        if (st.GetQueueSize() > 0) {
            DiscoverKinematicStructure();
        } else if (ShouldSetTreeDirty) {
            st.ResetCenterOfMassTotal();
            this->ShouldSetTreeDirty = false;
            this->CanSendMessage = true;
            for (int i=0; i<st.GetVertices().size(); i++) {
                ModuleNode *smn = st.GetVertices()[i];
                if (smn) delete smn;
            }
            InitializeKinematicTree();
        } else if (!HaveInitiatedSelectTarget) {
            HaveInitiatedSelectTarget = true;
        } else if (!HaveSelectedTarget) {
            HaveSelectedTarget = true;
        } else if (!HaveSetJointsTo0) {
            HaveSetJointsTo0 = true;
        } else if (!HaveInitiatedIK) {
            if (this->ProgramCounter > 300) {InitiateIK();}
        } else if (!HaveCompletedIK) {
            HaveCompletedIK = PSOWorker->IsFinished();
            GEngine->AddOnScreenDebugMessage(IKErrorKey,5.f, FColor::Red,
            FString::Printf(TEXT("IK Current Error: %f"), PSOWorker->GetCurrentUpperBound()));
            GEngine->AddOnScreenDebugMessage(IKPartitionsKey,5.f, FColor::Red,
            FString::Printf(TEXT("Get Num Active Partitions: %d"), PSOWorker->GetNumActivePartitions()));
            if (HaveCompletedIK) {
                GEngine->AddOnScreenDebugMessage(IKDoneKey,5.f, FColor::Green, FString(TEXT("Done With IK")));
                PSOWorker->Stop();
                PSOWorker->Shutdown();
                GEngine->AddOnScreenDebugMessage(PPDoneKey,5.f, FColor::Green,
                                                 FString::Printf(TEXT("Planning Path To Goal Angles")));
                PlanPathToGoal();
            }
        } else if (!HaveCompletedPP) {
            HaveCompletedPP = PASOWorker->IsFinished();
            if (HaveCompletedPP) {
                Path0ToGoal.push_back(SolutionPos);
                PASOWorker->Stop();
                PASOWorker->Shutdown();
                if (PathTo0.size() == 0) {
                    GEngine->AddOnScreenDebugMessage(PPDoneKey,5.f, FColor::Green,
                    FString::Printf(TEXT("Planning Path To 0 Angles")));
                    HaveCompletedPP = false;
                    PlanPathTo0();
                } else {
                    std::vector<float> goal(3*st.GetVertices().size());
                    for (int i=0; i<goal.size(); i++) {
                        goal[i] = 0;
                    }
                    PathTo0.push_back(goal);
                    Path.reserve(PathTo0.size() + Path0ToGoal.size());
                    Path.insert(Path.end(), PathTo0.begin(), PathTo0.end());
                    Path.insert(Path.end(), Path0ToGoal.begin(), Path0ToGoal.end());
                    GEngine->AddOnScreenDebugMessage(PPDoneKey,5.f, FColor::Green,
                    FString::Printf(TEXT("PP Done: %i, Size of Path: %d"), Path.size(), PASOWorker->DidConverge()));
                    CurrentPathElement = 0;
                    WaitCounter = 20;
                    HaveSetJointAngles = false;
                }
            }
        } else if (!HaveSetJointAngles && WaitCounter <= 0 && Path.size() > 0) {
            SetJointAnglesDistributed(Path[CurrentPathElement]);
            WaitCounter = 20;
            GEngine->AddOnScreenDebugMessage(PPProgressKey,5.f, FColor::Blue,
            FString::Printf(TEXT("Remaining Path Size: %d"), Path.size() - CurrentPathElement));
            CurrentlyMoving = true;
            CurrentPathElement++;
            if (CurrentPathElement >= Path.size()) {
                HaveSetJointAngles = true;
                WaitCounter = 500;
                CurrentlyMoving = false;
            }
        } else if (HaveSetJointAngles && WaitCounter <=0) {
            if (GDock == DOCK_1) {
                AddDockAction(std::pair<ModuleAction,bool>(ENGAGE_BACK_DOCK_TO_GROUND, false));
            } else if (GDock == DOCK_0) {
                AddDockAction(std::pair<ModuleAction,bool>(ENGAGE_FRONT_DOCK_TO_GROUND, false));
            }
            HaveInitiatedSelectTarget = false;
            HaveSelectedTarget = false;
            HaveInitiatedIK = false;
            HaveCompletedIK = false;
            HaveCompletedPP = false;
            HaveSetJointAngles = false;
            HaveSetJointsTo0 = false;
            WaitCounter = 0;
            Path.clear();
            PathTo0.clear();
            Path0ToGoal.clear();
            BestTransformsFound.clear();
            CurrentPathElement = 0;
            ConnectNewEffector();
        } else {
            WaitCounter--;
        }
        
    }
    this->ProgramCounter++;
}
