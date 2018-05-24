#pragma once
#include "Framework/KinematicGraph.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/RobotModuleBehavior.h"
#include "SuperBot/SuperBotKinematics.h"
#include "PSO/PSOParticleSwarm.h"
#include "Framework/ModuleTree.h"
#include "CustomActors/DirectionActor.h"
#include "CustomActors/ManipulatorObjectActor.h"
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
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
#include "RRT/FRRTWorker.h"
#include "PhysXIncludes.h"
#include "PhysicsPublic.h"  //FPhysScene
#include "PhysXPublic.h"    //PtoU conversions
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
using namespace std;

struct IKTestResultReconf {
	float FinalError;
	float ElapsedTime;
	int NumPartitions;
};
class REBOTS_API ReconfIKBehavior : public RobotModuleBehavior
{
	///Basic behavior data
	int ProgramCounter = 0; /**< current program counter */
	ModuleModel CurrentModel; /**< current model */
	UWorld* World; /**< world */
	std::string ModuleName; /**< name of module */
	ASuperBotModule* SModule; /**< superbot module */
	FVector ObjectExtents; /**< object extents */
	float CurrentX; /**< current x coordinate of base */


					///Basic flags and data for kinematic discovery
	bool SentRecursiveMessage = false; /**< sent recursive message */
	bool ShouldPrintDiscovery = false; /**< should print discovery information */
	bool ShouldPrintMessageIDs = true; /**< should print message ids */
	bool ShouldCalibrateKinematics = true; /**< should calibrate kinematics */
	bool HasBeenInitialized = false; /**< has the tree been initialized ?*/
	bool CanSendMessage = true; /**< can send message */
	vector<bool> HasReturned = vector<bool>(6); /**< has returned vector */
	bool ShouldSetTreeDirty = true; /**< does tree need to be rebuilt */
	std::vector<std::pair<int, ModuleDockFace> > TargetEffectors; /**< target effector transforms */
	std::vector<FTransform> TargetTransforms; /**< target transforms */
	std::vector<float> TargetAngles; /**< target angles */
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





												 ///Basic PP data and flags
	int CurrentPathElement = 0; /**< current path element */
	int ObjectIKCounter = 0; /**< object ik counter */
	int PPCounter = 0; /**< path planning counter */
	int PECounter = 0; /**< path execution counter */
	int EWCounter = 0; /**< execute wait counter */
	int WaitCounter = 0; /**< wait counter */
	int SwitchIKCounter = 0; /**< ik counter for swtich */
	int IKCounter = 0; /**< ik counter for ground */
	int ReconfCounter = 0; /**< reconf counter */
	int WalkingStepCount = 0; /**< number of steps taken */
	bool HaveInitiatedIK = false; /**< have we initiated ik?*/
	bool HaveCompletedIK = false; /**< have we completed ik*/
	bool HaveCompletedPP = false; /**< have completed pp */
	bool HaveSetJointAngles = false; /**< have set joint angles */
	bool HaveSelectedTarget = false; /**< have selected target */
	bool HaveInitiatedPP = false; /**< have initiated pp */
	bool HavePlannedTo0 = false; /**< have planned to 0*/
	bool HaveExecutedTo0 = false; /**< have executed to 0*/
	bool HaveFoundIKAngles = false;/**< Have found ik angles */
	bool HavePlannedIKAngles = false; /**< have planned ik angles */
	bool HaveExecutedIKAngles = false; /**< have*/
	bool HaveWaited1 = false; /**< have waited 1*/
	bool HaveWaited2 = false; /**< have waited 2*/
	bool HaveWrittenToFile = false; /**< have we written to file */
	int NumTests = 1; /**< number of tests */
	bool PosAndOrient = true; /**< position and orientation error? */
	bool OverrideSelectedEndEffector = false; /**< should we ovverride the selected end effector*/
	int TestNumKey = 2500;
	vector<IKTestResultReconf> IKTestResultVec; /**< vector of ik test results */
	ModuleTree st; /**< tree of superbot modules from this modules vantage point */
	PSOParticleSwarm *PS; /**< particle swarm for inverse kinematics */
	std::vector<std::vector<float> > Path0ToGoal; /**< path */
	std::vector<std::vector<float> > PathTo0; /**< path to 0*/
	std::vector<std::vector<float> > Path; /**< total path */
	PASO PASOPP; /**< paso path planning */




				 ///Module role flags and data
	bool AmIEngagedToGround; /**< Am I engaged to ground */
	bool AmIEndEffector; /**< Am I an end effector */
	bool AmIConnectedToObject; /**< am I connected to object */
	int SelectedEndEffector = -1; /**< End effector selected for manipulation */
	ModuleDockFace EEDock; /**<end effector dock */
	int GroundModule = -1; /**< ground module */
	ModuleDockFace GDock; /**< dock connected to ground */

	int RandDock = 0;
	int lastPartition = -1;
	std::ofstream ikerrorstream;


					///Inverse kinematics data, random numbers, etc.
	FVector TargetRandVector; /**< target random vector*/
	float TargetYaw = 0.0; /**< yaw of random vector for ik */
	unsigned Seed; /**< r seed value */
	std::mt19937 Generator; /**< random number generator */
	FTransform TargetTransform; /**< random target */
	std::vector<float> SolutionPos; /**< PSO solution position */
	float SolutionFitness; /**< PSO solution fitness */
	std::vector<FTransform> BestTransformsFound; /**< Best transform found */
	int SE1;
	int SE2;





												 ///Multithreading workers
	FBBPSOWorker *PSOWorker; /**< PSO Worker */
	FPASOWorker *PASOWorker; /**< PASO Worker */
	FRRTWorker *RRTWorker; /**< RRT Worker */
	FRORTWorker *RORTWorker; /**< RORT Worker */




							 ///Onscreen message keys
	int IKErrorKey = 500; /**< message key for ik error */
	int IKPartitionsKey = 900; /**< message key for ik partition number */
	int PPProgressKey = 800; /**< pp progress key */
	int IKDoneKey = 600;/**< ik done key */
	int PPDoneKey = 700; /**< pp done key */
	int ObjectChangeKey = 400; /**< object change key */
	int ProgramModeKey = 200; /**< program mode key */
	int CurrentXKey = 100; /**< current x of base key */
	int IKRuntimeKey = 300; /**< ik runtime key */


							///Basic actors needed for manipulation and locomotion
	AStaticMeshActor* Floor; /**< floor actor */
	AManipulatorObjectActor* ManipOb; /**< manip object*/





									  ///Transforms for ground and manipulation objects
	FTransform ModuleBaseToGroundTransform; /**< module to ground transform */
	FTransform ActualGroundTransform; /**< actual transform of ground */
	FTransform ModuleBaseToObjectTransform; /**< module to object transform*/
	FTransform ActualObjectTransform; /**< actual transform of object*/
public:
	///Constructors and destructors
	/**
	* @brief constructor
	*/
	ReconfIKBehavior();
	/**
	* @brief constructor
	* @param W world
	* @param NameOfModule name of module
	*/
	ReconfIKBehavior(UWorld* W, std::string NameOfModule);
	/**
	* @brief destructor
	*/
	virtual ~ReconfIKBehavior();
	/**
	* @brief generate random collision-free configurations
	* @param bounds bounds per dimension
	* @return rnadom collision-free configuration
	*/
	std::vector<float> RandomCollisionFreeConfiguration(std::vector<std::pair<float, float> > bounds);
	/**
	* @brief get end effector poses for configuration
	* @param config configuration to get effector  poses for
	* @return random collision-free configuration
	*/
	std::vector<std::pair<int, ModuleDockFace> > Effectors(std::vector<float> config);
	/**
	* @brief get target end effectors
	* @return target end effectors
	*/
	std::vector<std::pair<int, ModuleDockFace> > GetTargetEffectors();
	/**
	* @brief get target transforms
	* @return target transforms
	*/
	std::vector<FTransform> GetTargetTransforms();
	/**
	* @brief get target angles
	* @return target angles
	*/
	std::vector<float> GetTargetAngles();





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











	///Collision detection
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
	* @brief detect ground collision
	* @param point point to check
	* @return is position in collision with ground
	*/
	bool IsInCollisionWithGroundDetailed(std::vector<float> point);
	/**
	* @brief detailed self collision function
	* @param point point to check for self  collision (detailed)
	*/
	bool IsInSelfCollisionDetailed(std::vector<float> point);





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
	* @brief find optimal goal angles for reconfiguration
	* @return true if process completed, false otherwise
	*/
	bool FindGoalAnglesForReconfigure();
	/**
	* @brief find optimal goal angles for reconfiguration
	* @return true if process completed, false otherwise
	*/
	bool FindGoalAnglesForReconfigure1();
	/**
	* @brief find optimal goal angles for reconfiguration
	* @return true if process completed, false otherwise
	*/
	bool FindGoalAnglesForReconfigureMoreThan2();
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
	* @brief fitness for PASO
	* @param P PSO particle
	* @param st start vector
	* @param tar target vector
	*/
	float FitnessReconfigure(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);
	/**
	* @brief fitness for PASO
	* @param P PSO particle
	* @param st start vector
	* @param tar target vector
	*/
	float FitnessReconfigureMoreThan2(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);
	/**
	* @brief fitness for PASO
	* @param P PSO particle
	* @param st start vector
	* @param tar target vector
	*/
	float FitnessReconfigure1(BranchBoundParticle P, std::vector<float> start, std::vector<float> target);


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
	* @brief update object pose
	*/
	void UpdateObjectPose();
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
