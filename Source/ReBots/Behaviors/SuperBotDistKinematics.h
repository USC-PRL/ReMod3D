#pragma once
#include "Framework/KinematicGraph.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/RobotModuleBehavior.h"
#include "SuperBot/SuperbotKinematics.h"
#include <vector>
#include "Framework/ModuleModel.h"
/**
 * @class SuperBotDistKinematics
 * @brief distributed kinematics program for Superbot
 * @author Thomas Collins
 * @version 1.0
 * @date 04/18/2014
 * Contact: collinst@usc.edu
 */
class REBOTS_API SuperBotDistKinematics: public RobotModuleBehavior {
protected:
    int ProgramCounter = 0; /**< current program counter */
    int CurrentNodeName; /**< current node name in kinematic graph */
    ModuleModel CurrentModel; /**< current model */
    KinematicGraph KG; /**< kinematic graph associated with this module */
    std::vector<std::vector<float> > NeighborAngles; /**< angles of neighbor modules */
    std::vector<float> CurrentAngles; /**< current angles */
    std::vector<float> CAngleDiffs; /**< differences between current angles and previous angles */
    std::vector<int> CDockDiffs; /**< dock engaged differences */
    std::vector<bool> CurrentDockEngagedStatus; /**< dock engaged status */
    int CurrentDepth; /**< current depth */
    std::vector<std::vector<bool> > MessageReceived; /**< messsage received for dock at depth */
public:
    /**
     * @brief constructor
     */
    SuperBotDistKinematics();
    /**
     * @brief get kinematic graph
     * @return get kinematic graph
     */
    KinematicGraph GetKinematicGraph();
    /**
     * @brief get kinematics action for dock face
     * @param d dock face
     * @return Superbot action
     */
    ModuleAction GetKinematicsActionForDock(ModuleDockFace d);
    /**
     * @brief destructor
     */
    virtual ~SuperBotDistKinematics();
    /**
     * @brief update the current joint angles
     */
    void UpdateCurrentAngles();
    /**
     * @brief update dock engaged status
     */
    virtual void UpdateDockEngagedStatus();
    /**
     * @brief set up joint motion
     */
    virtual void SetUpJointMotion();
    /**
     * @brief get corrective docking transform
     * @param d1 dock 1
     * @param d2 dock 2
     */
    FTransform GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief step function of behavior
     * @param jointVals superbot sensor values
     * @param desiredVals desired sensor values
     * @return action values
     */
    virtual void Tick(ModuleModel model);
};
