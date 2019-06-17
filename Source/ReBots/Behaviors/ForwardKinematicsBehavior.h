#pragma once
#include "Framework/KinematicGraph.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/RobotModuleBehavior.h"
#include "SuperBot/SuperbotKinematics.h"
#include "Framework/ModuleTree.h"
#include <vector>
#include "Framework/ModuleModel.h"
/**
 * @class ForwardKinematicsBehavior
 * @brief forward kinematics behavior
 */
class REBOTS_API ForwardKinematicsBehavior : public RobotModuleBehavior
{
    bool SentRecursiveMessage = false; /**< sent recursive message */
    bool ShouldPrintDiscovery = true; /**< should print discovery information */
    bool ShouldCalibrateKinematics = true; /**< should calibrate kinematics */
    bool HasBeenInitialized = false; /**< has the tree been initialized ?*/
    int NeighborNum = 0; /**< neighbor number */
    bool CanSendMessage = true; /**< can send message */
    vector<bool> HasReturned = vector<bool>(6); /**< has returned vector */
    bool ShouldSetTreeDirty = true; /**< does tree need to be rebuilt */
    int ProgramCounter = 0; /**< current program counter */
    int CurrentNodeName; /**< current node name in kinematic graph */
    ModuleModel CurrentModel; /**< current model */
    KinematicGraph KG; /**< kinematic graph associated with this module */
    std::vector<std::vector<float> > NeighborAngles; /**< angles of neighbor modules */
    std::vector<float> CurrentAngles; /**< current angles */
    std::vector<float> CAngleDiffs; /**< differences between current angles and previous angles */
    std::vector<int> CDockDiffs; /**< dock engaged differences */
    std::vector<int> CDockToGroundDiffs; /**< dock engaged to ground differences */
    std::vector<bool> CurrentDockEngagedStatus; /**< dock engaged status */
    std::vector<bool> CurrentDockEngagedToGroundStatus; /**< dock engaged to ground status */
    int CurrentDepth = 0; /**< current depth */
    std::vector<std::vector<bool> > MessageReceived; /**< messsage received for dock at depth */
    ModuleTree st; /**< tree of superbot modules from this modules vantage point */
    int WaitTick = 0; /**< how many ticks to wait */
public:
    /**
     * @brief constructor
     */
    ForwardKinematicsBehavior();
    /**
     * @brief get kinematic graph
     * @return get kinematic graph
     */
    KinematicGraph GetKinematicGraph();
    /**
     * @brief get superbot module tree
     */
    ModuleTree GetSuperBotTree();
    /**
     * @brief get kinematics action for dock face
     * @param d dock face
     * @return Superbot action
     */
    ModuleAction GetKinematicsActionForDock(ModuleDockFace d);
    /**
     * @brief get tree action for dock face
     * @param d dock face
     * @return Superbot action
     */
    ModuleAction GetTreeActionForDock(ModuleDockFace d);
    /**
     * @brief should reinitialize program ?
     * @return whether or not we need to re init program
     */
    bool ShouldReInit();
    /**
     * @brief init program
     */
    void Init();
    /**
     * @brief process messages
     */
    void ProcessMessages(vector<TreeMessage> messages);
    /**
     * @brief initialize kinematic tree
     * @param aEE am i end effector?
     * @param cTG connected to ground?
     */
    void InitializeKinematicTree();
    /**
     * @brief discover kinematic structure
     */
    void DiscoverKinematicStructure();
    
    /**
     * @brief destructor
     */
    virtual ~ForwardKinematicsBehavior();
    /**
     * @brief update the current joint angles
     */
    void UpdateCurrentAngles();
    /**
     * @brief update dock engaged status
     */
    virtual void UpdateDockEngagedStatus();
    /**
     * @brief update dock engaged status
     */
    virtual void UpdateDockEngagedToGroundStatus();
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
