#pragma once
#include "Framework/KinematicGraph.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/RobotModuleBehavior.h"
#include "SuperBot/SuperbotKinematics.h"
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
class REBOTS_API DistributedKinematicsBehavior : public RobotModuleBehavior
{
	///Basic behavior data
	int ProgramCounter = 0; /**< current program counter */
	ModuleModel CurrentModel; /**< current model */
	UWorld* World; /**< world */
	std::string ModuleName; /**< name of module */
	ASuperBotModule* SModule; /**< superbot module */
	bool SentRecursiveMessage = false; /**< sent recursive message */
	bool ShouldPrintDiscovery = false; /**< should print discovery information */
	bool ShouldPrintMessageIDs = true; /**< should print message ids */
	bool ShouldCalibrateKinematics = true; /**< should calibrate kinematics */
	bool HasBeenInitialized = false; /**< has the tree been initialized ?*/
	bool CanSendMessage = true; /**< can send message */
	std::vector<std::vector<float> > NeighborAngles; /**< angles of neighbor modules */
	std::vector<float> CurrentAngles; /**< current angles */
	std::vector<float> CAngleDiffs; /**< differences between current angles and previous angles */
	std::vector<int> CDockDiffs; /**< dock engaged differences */
	std::vector<int> CDockToGroundDiffs; /**< dock engaged to ground differences */
	std::vector<int> CDockToObjectDiffs; /**< dock engaged to object differences */
	std::vector<bool> CurrentDockEngagedStatus; /**< dock engaged status */
	std::vector<bool> CurrentDockEngagedToGroundStatus; /**< dock engaged to ground status */
	std::vector<bool> CurrentDockEngagedToObjectStatus; /**< dock engaged to object status */
	FTransform CurrentTransform; /**< Current transform of module relative to foot module */
	std::vector<ModuleDockFace> CurrentPathToFoot; /**< current path of docks to foot module */
	std::vector<FTransform> EETransforms; /**< end effector transforms */
	FTransform TransformOfGround; /**< ground transform */
	///Module role flags and data
	bool AmIEngagedToGround; /**< Am I engaged to ground */
	bool AmIEndEffector; /**< Am I an end effector */
	bool AmIConnectedToObject; /**< am I connected to object */
	bool AmILeader; /**< am I the leader? */
	int SelectedEndEffector = -1; /**< End effector selected for manipulation */
	ModuleDockFace EEDock; /**<end effector dock */
	int GroundModule = -1; /**< ground module */
	ModuleDockFace GDock; /**< dock connected to ground */
	bool CanSendDFKMessage = true; /**< can we send a DFK message?*/
	vector<bool> HasReturned; /**< tracking messages returned to docks */
	vector<bool> HasReturnedDFK; /**< has returned DFK */
	int NumEndEffectors = 0; /**< numbers of end effectors */
	int NumModuleConnectors; /**< number of  connectors in the module*/
public:
	/**
	* @brief find pose relative to foot and update number of end effectors
	* @return true if completed, false otherwise
	*/
	bool FindPoseToFootAndEndEffectors();
	/**
	* @brief get end-effector transforms
	* @return end-effector transforms
	*/
	std::vector<FTransform> GetEndEffectorTransforms();
	/**
	* @brief get transform of ground
	* @return transform of ground
	*/
	FTransform GetTransformOfGround();

	///Constructors and destructors
	/**
	* @brief constructor
	*/
	DistributedKinematicsBehavior();
	/**
	* @brief constructor
	* @param W world
	* @param NameOfModule name of module
	*/
	DistributedKinematicsBehavior(UWorld* W, std::string NameOfModule);
	/**
	* @brief set am i the leader
	* @param l am i the leader
	*/
	void SetAmILeader(bool l);
	/**
	* @brief get am i the leader
	* @return am i the leader
	*/
	bool GetAmILeader();
	/**
	* @brief destructor
	*/
	virtual ~DistributedKinematicsBehavior();
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
	* @brief get transform
	* @return transform
	*/
	FTransform GetTransform();
	/**
	* @brief get corrective docking transform
	* @param d1 dock 1
	* @param d2 dock 2
	*/
	FTransform GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2);
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
	/**
	* @brief get tree action for dock face
	*/
	ModuleAction GetTreeActionForDockFace(ModuleDockFace d);





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
