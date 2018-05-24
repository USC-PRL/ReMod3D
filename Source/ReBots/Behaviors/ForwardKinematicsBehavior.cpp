// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ForwardKinematicsBehavior.h"

/**
 * @brief constructor
 */
ForwardKinematicsBehavior::ForwardKinematicsBehavior() {
    Init();
    this->Name = "FK";
}
/**
 * @brief destructor
 */
ForwardKinematicsBehavior::~ForwardKinematicsBehavior(){}
/**
 * @brief initialize kinematic tree
 * @param aEE am i end effector?
 * @param cTG connected to ground?
 */
void ForwardKinematicsBehavior::InitializeKinematicTree() {
    ModuleNode *rootNode = new ModuleNode(CurrentAngles,0,FTransform(FVector(0,0,0)));
    rootNode->SetDiscoveredLevel(0 );
    rootNode->SetDiscoveredDock(-1);
    rootNode->SetDiscoveringNode(NULL);
    rootNode->SetAmIEndEffector(false);
    rootNode->SetConnectedToGround(false);
    st.InitializeTree(rootNode);
    st.AddNodeToBFSQueue(rootNode);
    HasBeenInitialized = true;
    this->CanSendMessage = true;
}
/**
 * @brief discover kinematic structure
 */
void ForwardKinematicsBehavior::DiscoverKinematicStructure() {
    ModuleNode *cNode = st.GetQueueFront();
    TreeMessage tm = TreeMessage("U",st.GetVertices().size(),this->NeighborNum);
    if (CurrentModel.GetCurrentState().GetIDNumber() == 0 && ShouldPrintDiscovery) {
        cout<<"Module Num: 0"<<endl;
        cout<<cNode->GetName()<<endl;
        cout<<cNode->GetCurrentDock();
        cout<<endl<<endl;
    }
    if (st.GetQueueSize() > 0 && cNode->GetCurrentDock() < 6) {
        tm.N = cNode;
        if (cNode->GetDockFacePath().size() > 0) {
            tm.Command = "UI";
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
void ForwardKinematicsBehavior::ProcessMessages(vector<TreeMessage> messages) {
    for (int i=0; i<messages.size(); i++) {
        TreeMessage mes = messages[i];
        if (mes.Command.compare("UJ") == 0) {
            
        } else if (mes.Command.compare("Reset") == 0) {
            TreeMessage tm = TreeMessage("Reset",st.GetVertices().size(),0);
            for (int j=0; j<6; j++) {
                if (CurrentDockEngagedStatus[j] && ((ModuleDockFace)j) != mes.GetReceivingDock().GetDockFace()) {
                    AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)j),tm));
                }
            }
            Init();
        } else if (mes.Command.compare("UJI") == 0) {

        } else if (mes.Command.compare("U") == 0) {
            mes.MV.push_back(ModuleMotorVector(CurrentAngles[0],CurrentAngles[1],CurrentAngles[2]));
            mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(),0));
            mes.CurrentPathElement = mes.DockFacePath.size() - 1;
            mes.Command = "R";
            if (mes.N->GetDockFacePath().size() > 0) {mes.Command = "RI";}
            AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()),mes));
        } else if (mes.Command.compare("UI") == 0) {
            mes.CurrentPathElement += 2;
            ModuleDockFace d;
            if (mes.CurrentPathElement < mes.N->GetDockFacePath().size()) {
                mes.Command = "UI";
                d = mes.N->GetDockFacePath()[mes.CurrentPathElement].first;
            } else {
                mes.Command = "U";
                d = (ModuleDockFace)mes.N->GetCurrentDock();
            }
            
            if (CurrentDockEngagedStatus[d] && d != mes.GetReceivingDock().GetDockFace()) {
                mes.MV.push_back(ModuleMotorVector(CurrentAngles[0],CurrentAngles[1],CurrentAngles[2]));
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(),0));
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>((ModuleDockFace)d,0));
                if (mes.Command.compare("U") == 0) {
                    mes.N->SetDiscoveredDock(mes.N->GetCurrentDock());
                }
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(d),mes));
            } else {
                mes.DockFacePath.push_back(std::pair<ModuleDockFace, int>(mes.GetReceivingDock().GetDockFace(),0));
                mes.CurrentPathElement = mes.DockFacePath.size() - 1;
                if (mes.CurrentPathElement > 1) {
                    mes.Command = "RFI";
                } else {
                    mes.Command = "RF";
                }
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(mes.GetReceivingDock().GetDockFace()),mes));
            }
        } else if (mes.Command.compare("RI") == 0) {
            mes.CurrentPathElement -= 2;
            if (mes.CurrentPathElement <= 1) {
                mes.Command = "R";
            } else {
                mes.Command = "RI";
            }
            AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(mes.N->GetDockFacePath()[mes.CurrentPathElement].first),mes));
        } else if (mes.Command.compare("RJI") == 0) {
            mes.CurrentPathElement -= 2;
            if (mes.CurrentPathElement <= 1) {
                mes.Command = "RJ";
            } else {
                mes.Command = "RJI";
            }
            AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(mes.N->GetDockFacePath()[mes.CurrentPathElement].first),mes));
        } else if (mes.Command.compare("RJ") == 0) {
            this->CanSendMessage = true;
        } else if (mes.Command.compare("R") == 0) {
            this->CanSendMessage = true;
            std::vector<float> angles = std::vector<float>(3);
            angles[0] = CurrentAngles[0];angles[1] = CurrentAngles[1];angles[2] = CurrentAngles[2];
            FTransform CurrentTransform = FTransform(FVector(0,0,0));
            ModuleMotorVector mv = ModuleMotorVector(angles[0],angles[1],angles[2]);
            int dockCounter = 0;
            for (int j=0; j<mes.MV.size(); j++) {
                ModuleDockFace d1 = mes.DockFacePath[dockCounter++].first;
                ModuleDockFace d2 = mes.DockFacePath[dockCounter++].first;
                FTransform trans1 = SuperbotKinematics::computeTransformToDock(mv, d1);
                angles[0] = mes.MV[j].Motor0Angle;angles[1] = mes.MV[j].Motor1Angle;angles[2] = mes.MV[j].Motor2Angle;
                mv = ModuleMotorVector(angles[0],angles[1],angles[2]);
                FTransform trans2 = SuperbotKinematics::computeTransformFromDock(mv,d2);
                CurrentTransform = trans2*GetCorrectiveDockingTransform(d1,d2)*trans1*CurrentTransform;
            }
            this->NeighborNum++;
            mes.N->IncrementCurrentDock();
            ModuleNode *n = new ModuleNode(angles, this->NeighborNum, CurrentTransform);
            n->SetDiscoveredLevel(mes.DockFacePath.size()/2);
            n->SetDockFacePath(mes.DockFacePath);
            n->SetDiscoveredDock(mes.N->GetDiscoveredDock());
            n->SetDiscoveringNode(mes.N);
            n->SetJointAngles(angles);
            n->SetAmIEndEffector(mes.AmIEndEffector);
            n->SetConnectedToGround(mes.ConnectedToGround);
            st.AddEdge(mes.N->GetName(),n->GetName(), mes.DockFacePath[mes.DockFacePath.size() - 2].first,mes.DockFacePath[mes.DockFacePath.size() - 1].first);
            st.AddNodeToBFSQueue(n);
            st.AddVertex(n);
        } else if (mes.Command.compare("RF") == 0) {
            this->CanSendMessage = true;
            mes.N->IncrementCurrentDock();
        } else if (mes.Command.compare("RFI") == 0) {
            mes.CurrentPathElement -= 2;
            ModuleDockFace d = (ModuleDockFace)mes.DockFacePath[mes.CurrentPathElement].first;
            if (mes.CurrentPathElement <= 1) {
                mes.Command = "RF";
            } else {
                mes.Command = "RFI";
            }
            AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock(d),mes));
        } else if (mes.Command.compare("D") == 0) {
            TreeMessage tm = TreeMessage("D",st.GetVertices().size(),this->NeighborNum);
            ShouldSetTreeDirty = true;
            for (int j=0; j<6; j++) {
                if (CurrentDockEngagedStatus[j] && j != mes.GetReceivingDock().GetDockFace()) {
                    AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)j),tm));
                }
            }
        }
    }
}
/**
 * @brief update the current joint angles
 */
void ForwardKinematicsBehavior::UpdateCurrentAngles() {
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
void ForwardKinematicsBehavior::UpdateDockEngagedStatus() {
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
void ForwardKinematicsBehavior::UpdateDockEngagedToGroundStatus() {
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
ModuleAction ForwardKinematicsBehavior::GetKinematicsActionForDock(ModuleDockFace d) {
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
ModuleAction ForwardKinematicsBehavior::GetTreeActionForDock(ModuleDockFace d) {
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
 * @brief set up joint motion
 */
void ForwardKinematicsBehavior::SetUpJointMotion() {
    if (this->ProgramCounter % 100 == 0) {
        int mFactor = -1;
        if (ProgramCounter %2 == 0) {
            mFactor = 1;
        }
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_0,10.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_1,mFactor*30.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_2,10.0));
        return;
    }
    if (this->ProgramCounter % 200 == 0) {
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_0,0.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_1,0.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_2,0.0));
        return;
    }
}
/**
 * @brief get corrective docking transform
 * @param d1 dock 1
 * @param d2 dock 2
 * @return corrective trnasform
 */
FTransform ForwardKinematicsBehavior::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
    if (d1 == DOCK_0 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI));
    } else if (d1 == DOCK_1 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),M_PI));
    } else if (d1 == DOCK_0 && d2 == DOCK_2) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    } else if (d1 == DOCK_2 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_3 && d2 == DOCK_0) {
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_0 && d2 == DOCK_3) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
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
        return FTransform(FQuat(FVector(0,1,0),M_PI_2));
    } else if (d1 == DOCK_5 && d2 == DOCK_1) {
        return FTransform(FQuat(FVector(0,1,0),-M_PI_2));
    }
    return FTransform(FVector(0,0,0));
}
/**
 * @brief get kinematic graph
 * @return get kinematic graph
 */
KinematicGraph ForwardKinematicsBehavior::GetKinematicGraph() {
    return this->KG;
}
/**
 * @brief get superbot module tree
 */
ModuleTree ForwardKinematicsBehavior::GetSuperBotTree() {
    return this->st;
}
/**
 * @brief should reinitialize program ?
 * @return whether or not we need to re init program
 */
bool ForwardKinematicsBehavior::ShouldReInit() {
    return false;
}
/**
 * @brief reinit program
 */
void ForwardKinematicsBehavior::Init() {
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
    this->MessageReceived = std::vector<std::vector<bool> >(50);
    for (int i=0; i<50; i++) {
        MessageReceived[i] = std::vector<bool>(6);
        for (int j=0; j<6; j++) {
            MessageReceived[i][j] = false;
        }
    }
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
 * @brief step function of behavior
 * @param jointVals superbot sensor values
 * @param desiredVals desired sensor values
 * @return action values
 */
void ForwardKinematicsBehavior::Tick(ModuleModel model) {
    ClearAllActions();
    this->CurrentModel = model;
    UpdateCurrentAngles(); /** update current joint angles of this module */
    UpdateDockEngagedStatus(); /** update dock engaged statuses for each dock of this module */
    UpdateDockEngagedToGroundStatus(); /**< update dock engaged statuses for each dock of this module */
    std::vector<RangedMessage> rms = model.GetCurrentState().GetRangedMessages();
    std::vector<Message> ms = model.GetCurrentState().GetMessages();
    std::vector<KinematicsMessage> kms = model.GetCurrentState().GetKinematicsMessages();
    std::vector<TreeMessage> tms = model.GetCurrentState().GetTreeMessages();
    

    int diffTotal = 0;
    for (int i=0; i<6; i++) {
        diffTotal += abs(CDockDiffs[i]);
    }
    
    if (fabs(CAngleDiffs[0]) > 2.0 || fabs(CAngleDiffs[1]) > 2.0 || fabs(CAngleDiffs[2]) > 2.0 || abs(diffTotal) > 0) {
        ShouldSetTreeDirty = true;
        TreeMessage tm = TreeMessage("D",st.GetVertices().size(),this->NeighborNum);
        for (int i=0; i<6; i++) {
            if (CurrentDockEngagedStatus[i]) {
                AddTreeMessageAction(std::pair<ModuleAction,TreeMessage>(GetTreeActionForDock((ModuleDockFace)i),tm));
            }
        }
        CAngleDiffs[0] = 0.0;
        CAngleDiffs[1] = 0.0;
        CAngleDiffs[2] = 0.0;
    }
    
    if (!HasBeenInitialized) {
        InitializeKinematicTree();
    }
    
    if (HasBeenInitialized) {
        ProcessMessages(tms);
    }
    
    if (CanSendMessage) {
        if (st.GetQueueSize() > 0) {
            DiscoverKinematicStructure();
        } else if (ShouldSetTreeDirty) {
            st.ResetCenterOfMassTotal();
            this->NeighborNum = 0;
            this->ShouldSetTreeDirty = false;
            this->CanSendMessage = true;
            for (int i=0; i<st.GetVertices().size(); i++) {
                ModuleNode *smn = st.GetVertices()[i];
                if (smn) delete smn;
            }
            InitializeKinematicTree();
        }
        
    }
    //SetUpJointMotion();
    this->ProgramCounter++;
}
