#pragma once
#include "Framework/KinematicGraph.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/RobotModuleBehavior.h"
#include "SuperBot/SuperbotKinematics.h"
#include "PSO/PSOParticleSwarm.h"
#include "Framework/ModuleTree.h"
#include "CustomActors/DirectionActor.h"
#include <vector>
#include <random>
#include <chrono>
#include <map>
#include "MessageEndpoint.h"
#include "BBPSO/BranchBoundParticleSwarm.h"
#include "BBPSO/BranchBoundParticle.h"
#include "BBPSO/FBBPSOWorker.h"
#include "MessageEndpointBuilder.h"
#include "PASO/PASO.h"
#include "PASO/FPASOWorker.h"
#include "Framework/ModuleModel.h"
#include "RRT/RRTTree.h"
#include <sstream>
#include "RRT/FRRTWorker.h"
#include "PhysXIncludes.h"
#include "PhysicsPublic.h"  //FPhysScene
#include "PhysXPublic.h"    //PtoU conversions
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
using namespace std;
/**
 * TODO : On timeout of message, reinit tree, just in case using reset command
 * TODO : When change in tree size detected, ignore return messages and reinit tree of all modules.
 */
class REBOTS_API FKIKBehavior : public RobotModuleBehavior
{
    bool SentRecursiveMessage = false; /**< sent recursive message */
    bool ShouldPrintDiscovery = false; /**< should print discovery information */
    bool ShouldPrintMessageIDs = true; /**< should print message ids */
    bool ShouldCalibrateKinematics = true; /**< should calibrate kinematics */
    bool HasBeenInitialized = false; /**< has the tree been initialized ?*/
    int CurrentPathElement = 0; /**< current path element */
    int WaitCounter = 0; /**< wait counter */
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
    ModuleTree st; /**< tree of superbot modules from this modules vantage point */
    PSOParticleSwarm *PS; /**< particle swarm for inverse kinematics */
    std::vector<std::vector<float> > Path0ToGoal; /**< path */
    std::vector<std::vector<float> > PathTo0; /**< path to 0*/
    std::vector<std::vector<float> > Path; /**< total path */
    bool AmIEngagedToGround; /**< Am I engaged to ground */
    bool AmIEndEffector; /**< Am I an end effector */
    int SelectedEndEffector = -1; /**< End effector selected for manipulation */
    int CurrentRootModule = 0; /**< Current root module */
    ModuleDockFace EEDock; /**<end effector dock */
    int GroundModule = -1; /**< ground module */
    ModuleDockFace GDock; /**< dock connected to ground */
    bool HaveInitiatedIK = false; /**< have we initiated ik?*/
    bool HaveCompletedIK = false; /**< have we completed ik*/
    bool HaveCompletedPP1 = false; /**< have initaited pp1 */
    bool HaveCompletedPP = false; /**< have completed pp */
    bool HaveCompletedPP2 = false; /**< have completed pp */
    bool HaveSetJointsTo0 = false; /**< have set joint angles back to 0*/
    bool HaveInitiatedSetJointsTo0 = false;
    bool HavePlannedSetJointsTo0 = false;
    std::map<int, ModuleNode*> ModNodes; /**< module nodes */
    float TargetYaw = 0.0;
    unsigned Seed; /**< r seed value */
    std::mt19937 Generator; /**< random number generator */
    FTransform TargetTransform; /**< random target */
    std::vector<float> SolutionPos; /**< PSO solution position */
    float SolutionFitness; /**< PSO solution fitness */
    FBBPSOWorker *PSOWorker; /**< PSO Worker */
    FPASOWorker *PASOWorker; /**< PASO Worker */
    FRRTWorker* RRTWorker; /**< RRT Worker */
    UWorld* World; /**< world */
    std::vector<FTransform> BestTransformsFound; /**< Best transform found */
    bool HaveSetJointAngles = false; /**< have set joint angles */
    bool HaveSelectedTarget = false; /**< have selected target */
    bool HaveInitiatedSelectTarget = false; /**< have initiated select target */
    bool HaveShownMessage = false; /**< have shown done PP message */
    bool ShouldSetAnglesTo90 = false; /**< should set angles to 90 */
    bool CurrentlyMoving = false; /**< currently moving? */
    PASO PASOPP; /**< paso path planning */
    int IKErrorKey = 500; /**< message key for ik error */
    int IKPartitionsKey = 900; /**< message key for ik partition number */
    int PPProgressKey = 800; /**< pp progress key */
    int IKDoneKey = 600;/**< ik done key */
    int PPDoneKey = 700; /**< pp done key */
    int CurrentVertexKey = -1; /**< current vertex key */
    std::string ModuleName; /**< name of module */
    AStaticMeshActor* Floor; /**< floor actor */
    ASuperBotModule* SModule; /**< superbot module */
    FTransform ModuleBaseToGroundTransform; /**< module to ground transform */
    FTransform ActualGroundTransform; /**< actual transform of ground */
    FVector TargetRandVector;
public:
    /**
     * @brief get module base to ground transform 
     * @return module base to ground transform
     */
    FTransform GetModuleBaseToGroundTransform();
    /**
     * @brief constructor
     */
    FKIKBehavior();
    /**
     * @brief constructor
     * @param W world
     */
    FKIKBehavior(UWorld* W, std::string NameOfModule);
    /**
     * @brief Get master inner transform of module associated with this program
     * @return master inner transform
     */
    FTransform GetMasterInnerTransformForBaseModule();
    /**
     * @brief connect new end effector
     */
    void ConnectNewEffector();
    /**
     * @brief collision function
     * @param point point to check
     * @return collision (true) or not (false)
     */
    bool CollisionFunction(std::vector<float> point);
    /**
     * @brief compute distance between point1 and point2
     * @param point1 point number 1
     * @param point2 point number 2
     * @return euclidean distance between point1 and point2
     */
    float Distance(std::vector<float> point1, std::vector<float> point2);
    /**
     * @brief get best transforms found
     * @return best transforms
     */
    std::vector<FTransform> GetBestTransforms();
    /**
     * @brief get solution position
     * @return solution position
     */
    std::vector<float> GetSolutionPos();
    /**
     * @brief state valid
     * @param point point to check
     * @return true if state valid false otherwise
     */
    bool StateValid(std::vector<float> point);
    /**
     * @brief set joints distributed
     * @param JAngles joint angles
     */
    void SetJointAnglesDistributed(std::vector<float> JAngles);
    /**
     * @brief get the transforms of modules for joint angles 
     * @param Mods modules
     * @param JAngles joint angles
     * @return transform of modules in tree
     */
    vector<FTransform> GetTransformsOfModulesForJointAngles(std::vector<ModuleNode*> Mods, std::vector<float> JAngles);
    /**
     * @brief get kinematic graph
     * @return get kinematic graph
     */
    KinematicGraph GetKinematicGraph();
    /**
     * @brief fitness function for IK
     * @param P particle
     * @param tar target
     * @return fitness value
     */
    float Fitness(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);
    /**
     * @brief fitness for PASO
     * @param P PSO particle
     * @param st start vector
     * @param tar target vector
     */
    float FitnessPSO(PSOParticle P, std::vector<float> start, std::vector<float> target);
    /**
     * @brief detect self collision
     * @param point point to check
     * @return is position in self collision
     */
    bool IsInSelfCollision(std::vector<float> point);
    /**
     * @brief detect ground collision
     * @param point point to check
     * @return is position in collision with ground
     */
    bool IsInCollisionWithGround(std::vector<float> point);
    /**
     * @brief get superbot module tree
     */
    ModuleTree GetSuperBotTree();
    /**
     * @brief get the selected end effector
     */
    int GetSelectedEndEffector();
    /**
     * @brief get the selected end effector
     */
    ModuleDockFace GetEndEffectorDockFace();
    /**
     * @brief get the selected end effector
     */
    int GetGroundModule();
    /**
     * @brief get the selected end effector
     */
    ModuleDockFace GetGroundDockFace();
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
     * @brief get am i end effector
     * @return am I an end effector
     */
    bool GetAmIEndEffector();
    /**
     * @brief get target transform
     * @return target transform
     */
    FTransform GetTargetTransform();
    /**
     * @brief get am i connected to ground
     * @return am I connected to ground
     */
    bool GetAmIConnectedToGround();
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
     * @brief update engaged to ground
     */
    void UpdateEngagedToGround();
    /**
     * @brief update whether or not I am end effector
     */
    void UpdateEndEffectorStatus();
    /**
     * @brief initiate inverse kinematics
     */
    void InitiateIK();
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
     * @brief plan path to 0
     */
    void PlanPathTo0();
    /**
     * @brief plan path to goal
     */
    void PlanPathToGoal();
    /**
     * @brief discover kinematic structure
     */
    void DiscoverKinematicStructure();
    /**
     * @brief destructor
     */
    virtual ~FKIKBehavior();
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
    /**
     * @brief get path to root from node
     * @param n superbot module node
     * @return path
     */
    std::vector<int> GetPathToRootFromNode(ModuleNode* n);
};

