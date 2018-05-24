#pragma once
#include "Framework/KinematicGraph.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/RobotModuleBehavior.h"
#include "SuperBot/SuperBotKinematics.h"
#include "PSO/PSOParticleSwarm.h"
#include "Framework/ModuleTree.h"
#include "CustomActors/DirectionActor.h"
#include "CustomActors/ManipulatorObjectActor.h"
#include "CustomActors/StackableObjectActor.h"
#include "CustomActors/StackableObjectTargetActor.h"
#include <vector>
#include <random>
#include <chrono>
#include <map>
#include "MessageEndpoint.h"
#include "BBPSO/BranchBoundParticleSwarm.h"
#include "BBPSO/BranchBoundParticle.h"
#include "BBPSO/FBBPSOWorker.h"
#include "RORT/FRORTWorker.h"
#include "MessageEndpointBuilder.h"
#include "PASO/PASO.h"
#include "PASO/FPASOWorker.h"
#include "Framework/ModuleModel.h"
#include "RRT/RRTTree.h"
#include <sstream>
#include <functional>
#include "RRT/FRRTWorker.h"
#include "PhysXIncludes.h"
#include "PhysicsPublic.h"  //FPhysScene
#include "PhysXPublic.h"    //PtoU conversions
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
class ASuperBotModule;
using namespace std;
///TODO: Add object to collision detection mechanism
///TODO: Add object to collision detection prediction
class REBOTS_API StackToPlaneBehavior : public RobotModuleBehavior
{
    ///Basic behavior data
    int ProgramCounter = 0; /**< current program counter */
    ModuleModel CurrentModel; /**< current model */
    UWorld* World; /**< world */
    std::string ModuleName; /**< name of module */
    ASuperBotModule* SModule; /**< superbot module */
    FVector ObjectExtents; /**< object extents */
    float CurrentX; /**< current x coordinate of base */
    std::vector<AStackableObjectActor*> StackableObs; /**< vector of stackable objects */
	std::vector<AStackableObjectTargetActor*> StackableTargets; /**< vector of stackable object target */
    ///Basic flags and data for kinematic discovery
    bool SentRecursiveMessage = false; /**< sent recursive message */
    bool ShouldPrintDiscovery = false; /**< should print discovery information */
    bool ShouldPrintMessageIDs = true; /**< should print message ids */
    bool ShouldCalibrateKinematics = true; /**< should calibrate kinematics */
    bool HasBeenInitialized = false; /**< has the tree been initialized ?*/
    bool CanSendMessage = true; /**< can send message */
    vector<bool> HasReturned = vector<bool>(6); /**< has returned vector */
    bool ShouldSetTreeDirty = true; /**< does tree need to be rebuilt */
    std::vector<std::vector<float> > NeighborAngles; /**< angles of neighbor modules */
    std::vector<float> CurrentAngles; /**< current angles */
    std::vector<float> CAngleDiffs; /**< differences between current angles and previous angles */
    std::vector<int> CDockDiffs; /**< dock engaged differences */
    std::vector<int> CDockToGroundDiffs; /**< dock engaged to ground differences */
    std::vector<int> CDockToObjectDiffs; /**< dock engaged to object differences */
    std::vector<bool> CurrentDockEngagedStatus; /**< dock engaged status */
    std::vector<bool> CurrentDockEngagedToGroundStatus; /**< dock engaged to ground status */
    std::vector<bool> CurrentDockEngagedToObjectStatus; /**< dock engaged to object status */
    std::map<int, ModuleNode*> ModNodes; /**< module nodes */
	FTransform AttachmentOffSet; /**< attachment to object offset */
	FTransform AttachmentOffSetPutDown; /**< attachment to object offset for putting it down */
	float AOffsetAngle1 = 0.0; /**< angle 1 */
	float AOffsetAngle2 = 0.0; /**< angle 2 */
	float TotalOffsetAngle = 0.0; /**< total offset angle */
	int AttachmentKey = 1249; /**< key for attachment debugging*/
	FTransform TargetOnGround; /**< target on ground transform */
	FTransform ObjectOnGround; /**< object on ground transform */
    
    
    ///Basic PP data and flags
    int CurrentPathElement = 0; /**< current path element */
    int ObjectIKCounter = 0; /**< object ik counter */
    int PPCounter = 0; /**< path planning counter */
    int PECounter = 0; /**< path execution counter */
    int EWCounter = 0; /**< execute wait counter */
    int WaitCounter = 0; /**< wait counter */
    int SwitchIKCounter = 0; /**< ik counter for swtich */
    int IKCounter = 0; /**< ik counter for ground */
    int WalkingStepCount = 0; /**< number of steps taken */
    bool HaveInitiatedIK = false; /**< have we initiated ik?*/
    bool HaveCompletedIK = false; /**< have we completed ik*/
    bool HaveCompletedPP = false; /**< have completed pp */
    bool HaveSetJointAngles = false; /**< have set joint angles */
    bool HaveSelectedTarget = false; /**< have selected target */
    bool HaveInitiatedPP = false; /**< have initiated pp */
    bool HaveFoundObjectAngles = false; /**< have we found object angles with ik */
    bool HavePlannedObjectPath = false; /**< have we planned an object path */
    bool HaveExecutedObjectPath = false; /**< have we executed a path to the object */
    bool HaveExecutedObjectReturnPath = false; /**< have we executed a path to the object */
    bool HavePlannedObjectReturnPath = false; /**< have we planned a return path from object */
    bool HaveConnectedObjectToEffector = false; /**< have we connected object to effector */
    bool HaveFoundSwitchAngles = false; /**< have we found switch angles */
    bool HavePlannedSwitchPath = false; /**< have we planned switch path */
    bool HaveExecutedSwitchPath = false; /**< have we executed swtich path */
    bool HavePlannedSwitchReturnPath = false; /**< have we planned switch return path */
    bool HaveExecutedSwitchReturnPath = false; /**< have we executed switch return path*/
    bool HaveExecutedWait1 = false; /**< have we executed wait 1*/
    bool HaveExecutedWait2 = false; /**< have we executed wait 2*/
    bool HaveExecutedWait3 = false;/**< have we executed wait 3*/
    bool HaveExecutedWait4 = false;/**< have we executed wait 4*/
    bool HaveExecutedWait5 = false;/**< have we executed wait 5*/
    bool HaveSwitchedHands = false; /**< have we swtiched hands */
    bool HaveWaited = false; /**< have waited */
    bool HaveWaitedGround1 = false; /**< have waited connect to ground 1*/
    bool HaveWaitedGround2 = false; /**< have waited connect to ground 2*/
    bool HaveWaitedGround3 = false; /**< have waited 3 */
    bool HaveWaitedGround4 = false; /**< have waited ground 4*/
    bool HaveConnectedToGround = false; /**< have connected to ground */
    bool HaveFoundAnglesToGround = false; /**< have found angles to ground */
    bool HavePlannedIKToGround = false; /**< have we planned ik to ground */
    bool HaveExecutedIKToGround = false; /**< have executed ik to ground */
    bool HavePlannedIKToGroundReturn = false; /**< have planned ik to ground return */
    bool HaveExecutedIKToGroundReturn = false; /**< have executed ik to ground return */
    bool HavePlannedPostWalkReturnTo0 = false; /**< have planned post walk return to 0 */
    bool HaveExecutedPostWalkReturnTo0 = false; /**< have executed post walk return to 0 */
    bool HaveDoneIKPostWalkSwitch = false; /**< have planned post walk switch */
    bool HaveExecutedPostWalkSwitchPlan = false; /**< have executed plan for post walk switch */
    bool HavePlannedPostWalkSwitchPath = false; /**< have planned post walk switch plan */
    bool HavePostWalkWaited1 = false; /**< post walk wait 1 */
    bool HavePostWalkWaited2 = false; /**< post walk  wait 2 */
    bool HavePostWalkWaited3 = false; /**< post walk wait 3 */
    bool HavePostWalkWaited4 = false; /**< post walk wait 4*/
    bool HavePostWalkSwitched = false; /**< post walk switch */
    bool HavePostWalkPostSwitchPlanned = false; /**< post walk post switch plan */
    bool HavePostWalkPostSwitchExecuted = false; /**< post walk post switch execute */
    bool HavePostWalkPostSwitchFindAngles = false; /**< post walk post switch find angles */
    bool HavePostWalkPostSwitchPlannedToSetDown = false; /**< post walk post switch plan to set down */
    bool HavePostWalkPostSwitchExecutedSetDown = false; /**< execute set down */
    bool HaveWaitedReconnect1 = false; /**< wait to reconnect 1 */
    bool HaveWaitedReconnect2 = false; /**< wait to reconnect 2 */
    bool HaveReconnected = false; /**< have we reconnected object to ground */
    bool HavePlannedPostReconnectTo0 = false; /**< have we planned back to 0 */
    bool HaveExecutedPostReconnectTo0 = false; /**< have we executed plan to 0 after reconnect */
    bool HaveWaitedFinal = false; /**< final wait */
    bool HavePlannedTo0Final = false; /**< final plan to 0 */
    bool HaveExecutedFinal = false; /**< have executed final */
	bool CloseEnoughToTarget = false; /**< Am i close enough to the target to pick it up*/
	bool HaveSetStackableDown = false; /**< Have I set the stackable object down*/
	bool HaveFoundReorientAngles = false;
	bool HavePlannedReorient = false;
	bool HaveExecutedReorient = false;
	bool HaveWaitedPreReorient = false;
	ModuleTree st; /**< tree of superbot modules from this modules vantage point */
    PSOParticleSwarm *PS; /**< particle swarm for inverse kinematics */
    std::vector<std::vector<float> > Path0ToGoal; /**< path */
    std::vector<std::vector<float> > PathTo0; /**< path to 0*/
    std::vector<std::vector<float> > Path; /**< total path */
	std::vector<std::vector<float> > FootPath;
    PASO PASOPP; /**< paso path planning */
	bool CloseEnoughToObject = false; /**< close enough to object ?*/
    

	bool HaveInitiatedStep = false;
	bool HaveFinishedStep = false;
	int WalkCounter = 0;
    
    
    ///Module role flags and data
    bool AmIEngagedToGround; /**< Am I engaged to ground */
    bool AmIEndEffector; /**< Am I an end effector */
    bool AmIConnectedToObject; /**< am I connected to object */
    int SelectedEndEffector = -1; /**< End effector selected for manipulation */
    ModuleDockFace EEDock; /**<end effector dock */
    int GroundModule = -1; /**< ground module */
    ModuleDockFace GDock; /**< dock connected to ground */
    
	FTransform WalkingTarget; /**< target transform for walking */
    
    
    
    ///Inverse kinematics data, random numbers, etc.
    FVector TargetRandVector; /**< target random vector*/
    float TargetYaw = 0.0; /**< yaw of random vector for ik */
    unsigned Seed; /**< r seed value */
    std::mt19937 Generator; /**< random number generator */
    FTransform TargetTransform; /**< random target */
    std::vector<float> SolutionPos; /**< PSO solution position */
    float SolutionFitness; /**< PSO solution fitness */
    std::vector<FTransform> BestTransformsFound; /**< Best transform found */
	float SolutionFitnessFoot; /**< solution fitness of foot */
	std::vector<float> SolutionPosFoot; /**< solution position of foot transform */
    
    
    
    ///Multithreading workers
    FBBPSOWorker *PSOWorker; /**< PSO Worker */
    FPASOWorker *PASOWorker; /**< PASO Worker */
    FRRTWorker *RRTWorker; /**< RRT Worker */
    FRORTWorker *RORTWorker; /**< RORT Worker */
    
    
	typedef enum {
		PICKING_UP_OBJECT = 0,
		SETTING_DOWN_OBJECT = 1,
		NOTHING = 2
	} STPProgramMode;

	STPProgramMode M = PICKING_UP_OBJECT; /**< program mode */
    
    ///Onscreen message keys
    int IKErrorKey = 500; /**< message key for ik error */
    int IKPartitionsKey = 900; /**< message key for ik partition number */
    int PPProgressKey = 800; /**< pp progress key */
    int IKDoneKey = 600;/**< ik done key */
    int PPDoneKey = 700; /**< pp done key */
    int ObjectChangeKey = 400; /**< object change key */
    int ProgramModeKey = 200; /**< program mode key */
    int CurrentXKey = 100; /**< current x of base key */
	int TargetDistanceKey = 300; /**< distance to target output message */
	int CToBKey = 350; /**< Am I connected to the object */
	int Key1 = 1;
	int Key2 = 2;
	int Key3 = 3;
	int Key4 = 4;

    ///Basic actors needed for manipulation and locomotion
    AStaticMeshActor* Floor = NULL; /**< floor actor */
    AManipulatorObjectActor* ManipOb = NULL; /**< manip object*/
    
	bool HaveStepped = false; /**< have stepped */
    
    
	float MaxStepSize = 370; /**< max step size for locomotion */
    
	std::vector<APhysicsConstraintActor*> StackConstraints;

    ///Transforms for ground and manipulation objects
    FTransform ModuleBaseToGroundTransform; /**< module to ground transform */
	FTransform ModuleBaseToGroundWithWalkTransform; /**< module to ground transform */
    FTransform ActualGroundTransform; /**< actual transform of ground */
    FTransform ModuleBaseToObjectTransform; /**< module to object transform*/
    FTransform ActualObjectTransform; /**< actual transform of object*/
    vector<FTransform> ModuleBaseToObjectTransforms; /**< transforms of objects */
    vector<FTransform> ActualObjectTransforms; /**< actual transforms of objects */
	FTransform ModuleBaseToGroundWithObjectWalkTransform;
    int CurrentStackableOb = 0; /**< current stackable object */

	int PickCounter = 0;
	int SetCounter = 0;
public:
	/**
	* @brief get transform on ground
	* @return transform on ground representing target
	*/
	FTransform GetTargetOnGroundTransform();
	/**
	* @brief get transform on ground
	* @return transform on ground representing target
	*/
	FTransform GetObjectOnGroundTransform();
	/**
	* @brief compute transform of target on ground
	* @return transform of target on ground
	*/
	FTransform ComputeTargetOnGroundTransform();
	/**
	* @brief get the target for walking
	* @return transform representing target for walking
	*/
	FTransform GetWalkingTarget();
    /**
     * @brief get stackable objects
     * @return stackable objects
     */
    vector<AStackableObjectActor*> GetStackableObs();
    /**
     * @brief get current stackable object index
     * @return current stackable object index
     */
    int GetCurrentStackableObjectIndex();
	/**
	* @brief get current pair of stackable objects
	* @return stackable object pair
	*/
	std::pair<AActor*, AActor*> GetCurrentStackablePair();
	/**
	* @brief walk toward target
	* @return true if completed, false otherwise
	*/
	bool WalkTowardTarget();
	/**
	* @brief walk toward target
	* @return true if completed, false otherwise
	*/
	bool PickUpObject();
	/**
	* @brief walk toward target
	* @return true if completed, false otherwise
	*/
	bool SetDownObject();
    ///Constructors and destructors
    /**
     * @brief constructor
     */
    StackToPlaneBehavior();
    /**
     * @brief constructor
     * @param W world
     * @param NameOfModule name of module
     */
    StackToPlaneBehavior(UWorld* W, std::string NameOfModule);
    /**
     * @brief destructor
     */
    virtual ~StackToPlaneBehavior();
    
    
    
    bool IsInSelfCollisionDetailed(std::vector<float> point);
    
    
    ///Special transforms relating modules to world frame objects
    /**
     * @brief get module base to ground transform
     * @return module base to ground transform
     */
    FTransform GetModuleBaseToGroundTransform();

    /**
     * @brief get module base to object transform
     * @return module base to object transform
     */
    FTransform GetModuleBaseToObjectTransform();
    /**
     * @brief Get master inner transform of module associated with this program
     * @return master inner transform
     */
    FTransform GetMasterInnerTransformForBaseModule();
    
    
    
	/**
	* @brief get transform on ground
	* @return transform on ground representing target
	*/
	FTransform ComputeObjectTargetOnGroundTransform();
    
    
    ///Create dynamic constraints
    /**
     * @brief connect new end effector
     */
    void ConnectNewEffector();
    /**
     * @brief connect effector to object
     */
    void ConnectObject();
    /**
     * @brief reconnect object to ground
     */
    void ReconnectObjectToGround();
	/**
	* @brief compute full transform to base
	* @return full transform of base
	*/
	FTransform ComputeFullBaseTransform();
	/**
	* @brief compute local transform to base
	* @return local transform of base
	*/
	FTransform ComputeLocalBaseTransform();
	/**
	* @brief compute local transform to base
	* @return local transform of base
	*/
	FTransform ComputeLocalBaseTransformWithAngles(ModuleMotorVector mv);
    /**
	* @brief compute transformation between target and current foot
	* @param Target target transform
	* @param Foot current foot transform
	*/
	FTransform ComputeTransformTargetToFoot();
    /**
	* @brief update module to ground transform
	* @return module base to ground transform
	*/
	FTransform ComputeModuleToGroundTransform();
	/**
	* @brief compute module to ground with walk transform
	* @return module to ground with walk transform
	*/
	FTransform ComputeModuleToGroundWithWalkTransform();
	/**
	* @brief update object pose
	*/
	FTransform ComputeObjectPose();
    
    
    
    
    ///Collision detection
	/**
	* @brief is in collision with ground for foot
	* @param P point to check
	* @return is in collision with ground (true) or not (false)
	*/
	bool IsInCollisionWithGroundFoot(std::vector<float> P);
	/**
	* @brief collision function for foot placement
	* @param P point to check
	* @return collision (true) or not (false)
	*/
	bool CollisionFunctionFoot(std::vector<float> P);
    /**
     * @brief collision function
     * @param point point to check
     * @return collision (true) or not (false)
     */
    bool CollisionFunction(std::vector<float> point);
    /**
     * @brief state valid
     * @param point point to check
     * @return true if state valid false otherwise
     */
    bool StateValid(std::vector<float> point);
	/**
	* @brief state valid
	* @param point point to check
	* @return true if state valid false otherwise
	*/
	bool StateValidFoot(std::vector<float> point);
    /**
     * @brief detect ground collision
     * @param point point to check
     * @return is position in collision with ground
     */
    bool IsInCollisionWithGroundDetailed(std::vector<float> point);
    //bool IsInSelfCollisionDetailed(std::vector<float> point);
    
    //Foot placement planning
	/**
	* @brief find target foot location
	* @return true if process finished, false otherwise
	*/
	bool FindTargetFootLocation();
	/**
	* @brief plan foot path current foot to target foot
	* @return true when process finished, false otherwise
	*/
	bool PlanFootPathCurrentFootToTargetFoot();
	/**
	* @brief execute foot path
	* @return true when process finished, false otherwise
	*/
	bool ExecuteFootPath();
	/**
	* @brief fitness function for IK
	* @param P particle
	* @param tar target
	* @return fitness value
	*/
	float FitnessFoot(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);


    ///Path planning functionality
    /**
     * @brief plan path from current angles to 0 angles (default)
     * @return true if planning completed, false otherwise
     */
    bool PlanPathCurrentAnglesTo0Angles();
    /**
     * @brief find optimal goals for IK procedure
     * @return true if process completed, false otherwise
     */
    bool FindGoalAnglesWithIK();
    /**
     * @brief find optimal goal angles for picking up object
     * @return true if process completed, false otherwise
     */
    bool FindGoalAnglesForObject();
    /**
     * @brief find optimal goal angles for picking up object
     * @return true if process completed, false otherwise
     */
    bool FindGoalAnglesForObjectSetDown();
    /**
     * @brief plan path from current angles to goal angles
     * @return true if process completed, false otherwise
     */
    bool PlanPathCurrentAnglesToGoalAngles();
    /**
     * @brief execute planned path
     * @return true if process completed, false otherwise
     */
    bool ExecutePath();
    /**
     * @brief execute a wait for a certain number of time steps
     * @param Counter number of time steps to wait
     * @return true if process completed false otherwise
     */
    bool ExecuteWait(int Counter);
    
    
    
    
    
    /**
     * @brief compute distance between point1 and point2
     * @param point1 point number 1
     * @param point2 point number 2
     * @return euclidean distance between point1 and point2
     */
    float Distance(std::vector<float> point1, std::vector<float> point2);
    /**
     * @brief fitness for PASO
     * @param P PSO particle
     * @param st start vector
     * @param tar target vector
     */
    float FitnessPSO(PSOParticle P, std::vector<float> start, std::vector<float> target);
    /**
     * @brief get distance to ground score
     * @param p point
     * @return score of distance to ground
     */
    float GetDistanceToGroundScore(std::vector<float> point);
    ///Inverse kinematics functionality
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
     * @brief get the transforms of modules for joint angles
     * @param Mods modules
     * @param JAngles joint angles
     * @return transform of modules in tree
     */
    vector<FTransform> GetTransformsOfModulesForJointAngles(std::vector<ModuleNode*> Mods, std::vector<float> JAngles);
    /**
     * @brief fitness function for IK
     * @param P particle
     * @param tar target
     * @return fitness value
     */
    float Fitness(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);
    /**
     * @brief fitness function for IK to object
     * @param P particle
     * @param tar target
     * @return fitness value
     */
    float FitnessObject(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);
    /**
     * @brief fitness function for IK to object set down
     * @param P particle
     * @param tar target
     * @return fitness value
     */
    float FitnessObjectSetDown(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);
    /**
     * @brief get target transform
     * @return target transform
     */
    FTransform GetTargetTransform();
    
    
    
    
    ///Kinematic discovery
    /**
     * @brief set joints distributed
     * @param JAngles joint angles
     */
    void SetJointAnglesDistributed(std::vector<float> JAngles);
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
     * @brief process messages
     */
    void ProcessMessages(vector<TreeMessage> messages);
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
     * @brief update dock engaged to object status
     */
    virtual void UpdateDockEngagedToObjectStatus();
    /**
     * @brief update dock diffs
     */
    virtual void UpdateDockDiffs();
    /**
     * @brief update engaged to ground
     */
    void UpdateEngagedToGround();
    /**
     * @brief update whether or not I am end effector
     */
    void UpdateEndEffectorStatus();
    /**
     * @brief update connected to object
     */
    void UpdateConnectedToObject();

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
     * @brief get path to root from node
     * @param n superbot module node
     * @return path
     */
    std::vector<int> GetPathToRootFromNode(ModuleNode* n);
    /**
     * @brief get corrective docking transform
     * @param d1 dock 1
     * @param d2 dock 2
     */
    FTransform GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief get superbot module tree
     */
    ModuleTree GetSuperBotTree();
    /**
     * @brief get the selected end effector
     */
    ModuleDockFace GetEndEffectorDockFace();
    /**
     * @brief get the selected end effector
     */
    int GetSelectedEndEffector();
    /**
     * @brief get the selected end effector
     */
    int GetGroundModule();
    /**
     * @brief get the selected end effector
     */
    ModuleDockFace GetGroundDockFace();
    /**
     * @brief get am i end effector
     * @return am I an end effector
     */
    bool GetAmIEndEffector();
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
    
    
    
    
    
    
    ///Basic program execution functionality
    /**
     * @brief init program
     */
    void Init();
    /**
     * @brief step function of behavior
     * @param jointVals superbot sensor values
     * @param desiredVals desired sensor values
     * @return action values
     */
    virtual void Tick(ModuleModel model);
};