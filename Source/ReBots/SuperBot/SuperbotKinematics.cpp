// Fill out your copyright notice in the Description page of Project Settings.

 
#include "SuperbotKinematics.h"

/**
 * @brief computing transform to dock
 * @param mod Superbot module
 * @param dock Superbot dock face
 * @return transform from Superbot module to dock
 */
FTransform SuperbotKinematics::computeTransformToDock(ModuleMotorVector mv, ModuleDockFace dock) {
    if (dock == DOCK_0) {
        FTransform t = FTransform(FVector(ASuperBotModule::SuperbotToOuterJoint,0,0));
        t = FTransform(FQuat(FVector(0,0,1), (PxPi/180.0)*mv.Motor0Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        return t;
    } else if (dock == DOCK_1) {
        FTransform t = FTransform(FQuat(FVector(1,0,0),(PxPi/180.0)*mv.Motor1Angle),
                                  FVector(0,0,0));
        t = FTransform(FVector(-ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        t = FTransform(FQuat(FVector(0,0,-1), (PxPi/180.0)*mv.Motor2Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        return t;
    } else if (dock == DOCK_2) {
        FTransform t = FTransform(FVector(ASuperBotModule::SuperbotToOuterJoint,0,0));
        t = FTransform(FQuat(FVector(0,0,1), (PxPi/180.0)*mv.Motor0Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock + 15.0,0,0))*t;
        t = FTransform(FVector(0,0,32+8+12))*t;
        return t;
    } else if (dock == DOCK_3) {
        FTransform t = FTransform(FVector(ASuperBotModule::SuperbotToOuterJoint,0,0));
        t = FTransform(FQuat(FVector(0,0,1), (PxPi/180.0)*mv.Motor0Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock + 15.0,0,0))*t;
        t = FTransform(FVector(0,0,-32-8-12))*t;
        return t;
    } else if (dock == DOCK_4) {
        FTransform t = FTransform(FQuat(FVector(1,0,0),(PxPi/180.0)*mv.Motor1Angle),
                                  FVector(0,0,0));
        t = FTransform(FVector(-ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        t = FTransform(FQuat(FVector(0,0,-1), (PxPi/180.0)*mv.Motor2Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock - 15.0,0,0))*t;
        t = FTransform(FVector(0,0,32+8+12))*t;
        return t;
    } else if (dock == DOCK_5) {
        FTransform t = FTransform(FQuat(FVector(1,0,0),(PxPi/180.0)*mv.Motor1Angle),
                                  FVector(0,0,0));
        t = FTransform(FVector(-ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        t = FTransform(FQuat(FVector(0,0,-1), (PxPi/180.0)*mv.Motor2Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock - 15.0,0,0))*t;
        t = FTransform(FVector(0,0,-32-8-12))*t;
        return t;
    }
    return FTransform(FVector(0,0,0));
}
/**
 * @brief computing transform to dock
 * @param mod Superbot module
 * @param dock Superbot dock face
 * @return transform from Superbot dock to module
 */
FTransform SuperbotKinematics::computeTransformFromDock(ModuleMotorVector mv, ModuleDockFace dock) {
    if (dock == DOCK_0) {
        FTransform t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock,0,0));
        t = FTransform(FQuat(FVector(0,0,-1), (PxPi/180.0)*mv.Motor0Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        return t;
    } else if (dock == DOCK_1) {
        FTransform t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock,0,0));
        t = FTransform(FQuat(FVector(0,0,1), (PxPi/180.0)*mv.Motor2Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        t = FTransform(FQuat(FVector(-1,0,0),(PxPi/180.0)*mv.Motor1Angle),
                                  FVector(0,0,0))*t;
        return t;
        
    } else if (dock == DOCK_2) {
        FTransform t = FTransform(FVector(0,0,-32-8-12));
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock - 15.0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FQuat(FVector(0,0,-1), (PxPi/180.0)*mv.Motor0Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        return t;
    } else if (dock == DOCK_3) {
        FTransform t = FTransform(FVector(0,0,32+8+12));
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock - 15.0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FQuat(FVector(0,0,-1), (PxPi/180.0)*mv.Motor0Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(-ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        return t;
    } else if (dock == DOCK_4) {
        FTransform t = FTransform(FVector(0,0,-32-8-12));
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock + 15.0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FQuat(FVector(0,0,1), (PxPi/180.0)*mv.Motor2Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        t = FTransform(FQuat(FVector(-1,0,0),(PxPi/180.0)*mv.Motor1Angle),
                                  FVector(0,0,0))*t;
        return t;

    } else if (dock == DOCK_5) {
        FTransform t = FTransform(FVector(0,0,32+8+12));
        t = FTransform(FVector(-ASuperBotModule::SuperbotOuterJointToOuterDock + 15.0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotOuterJointToOuterDock,0,0))*t;
        t = FTransform(FQuat(FVector(0,0,1), (PxPi/180.0)*mv.Motor2Angle),FVector(0,0,0))*t;
        t = FTransform(FVector(ASuperBotModule::SuperbotToOuterJoint,0,0))*t;
        t = FTransform(FQuat(FVector(-1,0,0),(PxPi/180.0)*mv.Motor1Angle),
                       FVector(0,0,0))*t;
        return t;
    }
    return FTransform(FVector(0,0,0));
}
