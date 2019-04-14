#pragma once
#include "Framework/KinematicGraph.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/RobotModuleBehavior.h"
#include "SuperBot/SuperbotKinematics.h"
#include <vector>
#include "Framework/ModuleModel.h"
using namespace std;
/**
 * @class SuperBotDistKinematicsChain
 * @brief distributed kinematics for chain module program
 */
class REBOTS_API SuperBotDistKinematicsChain : public RobotModuleBehavior
{
private:
    bool SentRecursiveMessage = false; /**< has recursive message been sent */
    bool ShouldCalibrateKinematics = true; /**< should kinematics be recalibrated */
    int neighborNum = 0; /**< current neighbor num value */
    vector<bool> HasReturned = vector<bool>(6); /**< have messages returned */
    bool ShouldSetTreeDirty = true; /**< does tree need to be rebuilt */
    int ProgramCounter = 0; /**< current program counter */
    int CurrentNodeName; /**< current node name in kinematic graph */
    ModuleModel CurrentModel; /**< current model */
    KinematicGraph KG; /**< kinematic graph associated with this module */
    std::vector<std::vector<float> > NeighborAngles; /**< angles of neighbor modules */
    std::vector<float> CurrentAngles; /**< current angles */
    std::vector<float> CAngleDiffs; /**< differences between current angles and previous angles */
    std::vector<int> CDockDiffs; /**< dock engaged differences */
    std::vector<bool> CurrentDockEngagedStatus; /**< dock engaged status */
    int CurrentDepth = 0; /**< current depth */
    std::vector<std::vector<bool> > MessageReceived; /**< messsage received for dock at depth */
public:
    /**
     * @brief constructor
     */
    SuperBotDistKinematicsChain();
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
    virtual ~SuperBotDistKinematicsChain();
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
