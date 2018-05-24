// Fill out your copyright notice in the Description page of Project Settings.

 
#include "SuperBotDistKinematicsChain.h"
/**
 * @brief constructor
 */
SuperBotDistKinematicsChain::SuperBotDistKinematicsChain() {
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
    
    this->CurrentAngles = std::vector<float>(3);
    this->CurrentDockEngagedStatus = std::vector<bool>(6);
    for (int i=0; i<6; i++) {
        this->CurrentDockEngagedStatus[i] = false;
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
    for (int i=0; i<6; i++) {
        this->CDockDiffs[i] = 0;
    }
    this->CAngleDiffs[0] = 0.0;
    this->CAngleDiffs[1] = 0.0;
    this->CAngleDiffs[2] = 0.0;
}
/**
 * @brief destructor
 */
SuperBotDistKinematicsChain::~SuperBotDistKinematicsChain(){}
/**
 * @brief update the current joint angles
 */
void SuperBotDistKinematicsChain::UpdateCurrentAngles() {
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
void SuperBotDistKinematicsChain::UpdateDockEngagedStatus() {
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
 * @brief get kinematics action for dock face
 * @param d dock face
 * @return Superbot action
 */
ModuleAction SuperBotDistKinematicsChain::GetKinematicsActionForDock(ModuleDockFace d) {
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
 * @brief set up joint motion
 */
void SuperBotDistKinematicsChain::SetUpJointMotion() {
    if (this->ProgramCounter % 100 == 0) {
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_0,10.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_1,10.0));
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
FTransform SuperBotDistKinematicsChain::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
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
 * @brief get kinematic graph
 * @return get kinematic graph
 */
KinematicGraph SuperBotDistKinematicsChain::GetKinematicGraph() {
    return this->KG;
}
/**
 * @brief step function of behavior
 * @param jointVals superbot sensor values
 * @param desiredVals desired sensor values
 * @return action values
 */
void SuperBotDistKinematicsChain::Tick(ModuleModel model) {
    ClearAllActions();
    this->CurrentModel = model;
    UpdateCurrentAngles(); /** update current joint angles of this module */
    UpdateDockEngagedStatus(); /** update dock engaged statuses for each dock of this module */
    std::vector<RangedMessage> rms = model.GetCurrentState().GetRangedMessages();
    std::vector<Message> ms = model.GetCurrentState().GetMessages();
    std::vector<KinematicsMessage> kms = model.GetCurrentState().GetKinematicsMessages();
    
    
    for (int i=0; i<kms.size(); i++) {
        KinematicsMessage mes = kms[i];
        if (mes.Command.compare("QJoints") == 0) {
            bool sentRecursiveMessage = false;
            if (mes.ForwardDirection) {
                mes.MV.push_back(ModuleMotorVector(CurrentAngles[0],CurrentAngles[1],CurrentAngles[2]));
                mes.DockFaceStackToSource.push(mes.GetReceivingDock().GetDockFace());
                mes.DockFacePath.push_back(mes.GetSendingDock().GetDockFace());
                mes.DockFacePath.push_back(mes.GetReceivingDock().GetDockFace());
                if (mes.GetReceivingDock().GetDockFace() != DOCK_0 && CurrentDockEngagedStatus[DOCK_0]) {
                    SentRecursiveMessage = true;
                    AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage>(GetKinematicsActionForDock(DOCK_0),mes));
                }
                if (mes.GetReceivingDock().GetDockFace() != DOCK_1 && CurrentDockEngagedStatus[DOCK_1]) {
                    SentRecursiveMessage = true;
                    AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage>(GetKinematicsActionForDock(DOCK_1),mes));
                }
            }
            if (!SentRecursiveMessage || !mes.ForwardDirection) {
                mes.ForwardDirection = false;
                ModuleDockFace d = mes.DockFaceStackToSource.top();
                mes.DockFaceStackToSource.pop();
                if (mes.DockFaceStackToSource.size() == 0) {mes.Command = "RJoints";}
                AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage>(GetKinematicsActionForDock(d),mes));
            }
        } else if (mes.Command.compare("RJoints") == 0) {
            HasReturned[mes.StartingDock] = true;
            FTransform currentTransform = FTransform(FVector(0,0,0));
            vector<float> angles(3);
            angles[0] = CurrentAngles[0]; angles[1] = CurrentAngles[1]; angles[2] = CurrentAngles[2];
            KG.AddNode(0,FTransform(FVector(0,0,0)),CurrentAngles);
            ModuleMotorVector mv(angles[0],angles[1],angles[2]);
            int dockCounter = 0;
            for (int j=0; j<mes.MV.size(); j++) {
                ModuleDockFace d1 = mes.DockFacePath[dockCounter++];
                ModuleDockFace d2 = mes.DockFacePath[dockCounter++];
                FTransform trans1 = SuperbotKinematics::computeTransformToDock(mv, d1);
                angles[0] = mes.MV[j].Motor0Angle; angles[1] = mes.MV[j].Motor1Angle; angles[2] = mes.MV[j].Motor2Angle;
                mv.Motor0Angle = angles[0]; mv.Motor1Angle = angles[1]; mv.Motor2Angle = angles[2];
                FTransform trans2 = SuperbotKinematics::computeTransformFromDock(mv,d2);
                currentTransform = trans2*GetCorrectiveDockingTransform(d1,d2)*trans1*currentTransform;
                neighborNum++;
                KG.AddNode(neighborNum, currentTransform, angles);
                KinematicEdge e = KinematicEdge(0,neighborNum,currentTransform);
                e.SetAngles(angles);
                KG.AddEdge(e);
            }
        }
    }
    
    if (CurrentModel.GetCurrentState().GetIDNumber() != -1) {
        if (HasReturned[0] && HasReturned[1]) {
            ShouldCalibrateKinematics = true;
            this->neighborNum = 0;
        } else {
            ShouldCalibrateKinematics = false;
        }
        std::string qjointString = "QJoints";
        KinematicsMessage kFront = KinematicsMessage(qjointString);
        kFront.ForwardDirection = true;
        KinematicsMessage kBack = KinematicsMessage(qjointString);
        kBack.ForwardDirection = true;
        if (CurrentDockEngagedStatus[DOCK_0] && ShouldCalibrateKinematics) {
            HasReturned[DOCK_0] = false;
            kFront.StartingDock = DOCK_0;
            AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage>(GetKinematicsActionForDock(DOCK_0),kFront));
        }
        if (CurrentDockEngagedStatus[DOCK_1] && ShouldCalibrateKinematics) {
            HasReturned[DOCK_1] = false;
            kBack.StartingDock = DOCK_1;
            AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage>(GetKinematicsActionForDock(DOCK_1),kBack));
        }
        SetUpJointMotion();
    }
    this->ProgramCounter++;
}
