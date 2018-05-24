 
#include "SuperBotDistKinematics.h"
/**
 * @brief constructor
 */
SuperBotDistKinematics::SuperBotDistKinematics() {
    this->NeighborAngles = std::vector<std::vector<float> >(6);
    for (int i=0; i<6; i++) {
        this->NeighborAngles[i] = std::vector<float>(3);
    }
    for (int i=0; i<6; i++) {
        for (int j=0; j<3; j++) {
            this->NeighborAngles[i][j] = -1000;
        }
    }
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
SuperBotDistKinematics::~SuperBotDistKinematics() {}
/**
 * @brief update the current joint angles
 */
void SuperBotDistKinematics::UpdateCurrentAngles() {
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
void SuperBotDistKinematics::UpdateDockEngagedStatus() {
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
ModuleAction SuperBotDistKinematics::GetKinematicsActionForDock(ModuleDockFace d) {
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
void SuperBotDistKinematics::SetUpJointMotion() {
    if (this->ProgramCounter % 100 == 0) {
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_0,80.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_1,80.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_2,80.0));
        return;
    }
    if (this->ProgramCounter % 200 == 0) {
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_0,90.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_1,90.0));
        AddAngleAction(std::pair<ModuleAction,float>(ModuleAction::SET_MOTOR_2,90.0));
        return;
    }
}
/**
 * @brief get corrective docking transform
 * @param d1 dock 1
 * @param d2 dock 2
 * @return corrective trnasform
 */
FTransform SuperBotDistKinematics::GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2) {
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
KinematicGraph SuperBotDistKinematics::GetKinematicGraph() {
    return this->KG;
}
/**
 * @brief behavior step function
 * @param model Wheelbot's current world model
 */
void SuperBotDistKinematics::Tick(ModuleModel model) {
    this->CurrentModel = model;
    UpdateCurrentAngles(); /** update current joint angles of this module */
    UpdateDockEngagedStatus(); /** update dock engaged statuses for each dock of this module */
    std::vector<RangedMessage> rms = model.GetCurrentState().GetRangedMessages();
    std::vector<Message> ms = model.GetCurrentState().GetMessages();
    std::vector<KinematicsMessage> kms = model.GetCurrentState().GetKinematicsMessages();
    
    int numNeighbors = 0;
    for (int i=0; i<kms.size(); i++) {
        KinematicsMessage mes = kms[i];
        if (mes.Command.compare("QJointsNR") == 0) {
            KinematicsMessage mesR("RJointsNR");
            mesR.MV.push_back(ModuleMotorVector(CurrentAngles[0],CurrentAngles[1],CurrentAngles[2]));
            AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage>(GetKinematicsActionForDock(mes.GetReceivingDock().GetDockFace()),mesR));
        } else if (mes.Command.compare("RJointsNR") == 0) {
            numNeighbors++;
            vector<float> angles(3);
            angles[0] = mes.MV[0].Motor0Angle;
            angles[1] = mes.MV[0].Motor1Angle;
            angles[2] = mes.MV[0].Motor2Angle;
            FTransform trans = SuperbotKinematics::computeTransformFromDock(mes.MV[0],mes.GetSendingDock().GetDockFace());
            KG.AddNode(0,FTransform(FVector(0,0,0)),CurrentAngles);
            ModuleMotorVector mv = ModuleMotorVector(KG.GetNodes()[0].GetAngles()[0],KG.GetNodes()[0].GetAngles()[1],KG.GetNodes()[0].GetAngles()[2]);
            FTransform etrans = SuperbotKinematics::computeTransformToDock(mv, mes.GetReceivingDock().GetDockFace());
            etrans = trans*GetCorrectiveDockingTransform(mes.GetSendingDock().GetDockFace(),
                                                   mes.GetReceivingDock().GetDockFace())*etrans;
            KG.AddNode(numNeighbors, etrans, angles);
            KG.AddEdge(std::pair<int,int>(0,numNeighbors),etrans);
            if (numNeighbors > 1) {
                numNeighbors  = 0;
            }
        }
    }
    
    
    for (int i=0; i<6; i++) {
        std::string qjointString = "QJointsNR";
        KinematicsMessage k = KinematicsMessage(qjointString);
        k.ForwardDirection = true;
        if (CurrentDockEngagedStatus[i]) {
            AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage>(GetKinematicsActionForDock((ModuleDockFace)i), k));
        }
    }
    
    //SetUpJointMotion();
    this->ProgramCounter++;
}
