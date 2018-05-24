// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Framework/Message.h"
#include "Framework/RangedMessage.h"
#include "SuperBot/SuperbotModule.h"
#include "Framework/ModuleDock.h"
#include "Framework/ConstraintMonitor.h"
#include "CustomActors/FloorCollisionActor.h"
#include "Framework/KinematicsMessage.h"
#include "PSO/PSOParticleSwarm.h"
#include "Framework/TreeMessage.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include <map>
#include <iostream>
#include <vector>
#include <utility>
#include "StarCellGameMode.generated.h"
using namespace std;
/**
 * @class AStarCellGameMode
 * @brief star cell game mode
 */
UCLASS()
class REBOTS_API AStarCellGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
    vector<ModuleDock> docksToMonitor; /**< docks for the experiment to moonitor */
    float errorPositionDock = 0.05; /**< position error for docking */
    float errorOrientationDock = 0.05; /**< orientation error for docking */
    vector<pair<int, ModuleDockFace> > deleteQueue; /**< queue of docks to delete from monitor */
    vector<ModuleDock> addQueue; /**< docks to add to the monitor */
    map<int, map<ModuleDockFace, ModuleDock> > connections; /**< connections between modules */
    map<int, vector<KinematicsMessage> > messageRoomKinematics; /**< kinematic message room */
    map<int, vector<Message> > messageRoom; /**< message boxes for modules (by name) */
    map<int, vector<RangedMessage> > messageRoomRanged; /**< message boxes for ranged messages for modules (by name) */
    map<int, vector<TreeMessage> > messageRoomSuperBotTree; /**< message boxes for super bot tree messages */
    vector<ASuperBotModule*> modules; /**< vector of modules in simulation */
    map<ASuperBotModule*,int> modsToIDs; /**< modules to ids */
    bool FirstTick = true; /**< is this the first tick of the game mode */
    ConstraintMonitor CMonitor; /**< constraint monitor */
    bool DockDebug = true; /**< dock debug output */
    bool FirstMove = true; /**< first move? */
    int waitCounter = 30; /**< wait counter */
    AReferenceFrameActor* EndEffectorFrame; /**< end effector reference frame */
    FTransform CurrentEndEffector; /**< current end effector transform */
    FTransform GoalEndEffector; /**< goal end effector transform */
    AStaticMeshActor* Floor; /**< floor actor */
    AReferenceFrameActor* GoalEndEffectorFrame; /**< goal end effector reference frame */
    FTransform ToGroundTransform; /**< to ground transform */
    AReferenceFrameActor* ToGroundFrame; /**< to ground frame */
    unsigned Seed; /**< seed value */
    std::mt19937 Generator; /**< generator for random nums */
    bool HaveInitiatedIK = false; /**< have initiated inverse kinematics */
    PSOParticleSwarm *PS; /**< particle swarm */
    std::vector<float> CurrentMotorAngles; /**< vector of current motor angles */
    int CurrentLockSize = 0; /**< current lock size */
public:
    /**
     * @brief game mode constructor
     * @param ObjectInitializer initializer
     */
    AStarCellGameMode(const FObjectInitializer& ObjectInitializer);
    /**
     * @brief advance the simulation
     * @param DeltaSeconds fraction of a second by which to advance simulation
     */
    virtual void Tick( float DeltaSeconds ) override;
    /**
     * @brief get transform of end effector for joint angles
     * @param JAngles joint angles
     * @return transform of End effector
     */
    FTransform GetTransformOfEndEffector(std::vector<ModuleMotorVector> JAngles, bool ToMaster);
    /**
     * @brief fitness function
     * @param P particle
     * @return particle fitness
     */
    float Fitness(PSOParticle P, std::vector<float> st, std::vector<float> tar);
    /**
     * @brief fitness function
     * @param P particle
     * @return particle fitness
     */
    float FitnessSequence(PSOParticle P, std::vector<float> st, std::vector<float> tar);
    /**
     * @brief get sequence of joint angle changes to move end effector to new pose
     */
    void GetSequenceOfJointAngles();
//#pragma mark -
//#pragma mark Messaging Functionality
    /**
     *	@brief	Sends a message from module to the module connected to dock
     *	@param 	module 	sending module
     *	@param 	dock 	dock out which message is sent
     *	@param 	message 	message contents
     */
    void sendMessageToDock(ASuperBotModule *module, ModuleDock dock, std::string message);
    /**
     *	@brief	Sends a wireless message out from sendingModule's center of mass. The range of the message is a sphere
     *          centered at sendingModule's center of mass with a radius of range.
     *	@param 	sendingModule 	module sending the message
     *	@param 	range 	range of the message
     *	@param 	message 	message contents
     */
    void sendRangedMessage(ASuperBotModule *sendingModule, float range, string message);
    /**
     *	@brief	Sends a kinematics message out on dock
     *	@param 	sendingModule 	module sending the message
     * @param dock dock send ing message
     *	@param 	mes 	message contents
     */
    void sendKinematicsMessageToDock(ASuperBotModule *sendingModule, ModuleDock dock, KinematicsMessage mes);
    /**
     *	@brief	Sends a kinematics message out on dock
     *	@param 	sendingModule 	module sending the message
     * @param dock dock send ing message
     *	@param 	mes 	message contents
     */
    void sendTreeMessageToDock(ASuperBotModule *sendingModule, ModuleDock dock, TreeMessage mes);
    
    /**
     *	@brief	retrieves the last message sent to the module with the given name
     *	@param 	module 	name of module
     *	@return	most recent message in module's queue of messages
     */
    Message getLastMessage(int module);
    /**
     *	@brief	retrieves the last ranged message sent to the module with the given name
     *	@param 	module 	name of module
     *	@return	most recent ranged message in module's queue of ranged messages
     */
    RangedMessage getLastRangedMessage(int module);
    /**
     *	@brief	retrieves the ranged messages for a given module
     *	@param 	module 	name of module
     *	@return	messages from modules ranged message queue
     */
    vector<RangedMessage> getRangedMessages(int module);
    /**
     *	@brief	retrieves messages for a given module
     *	@param 	module 	name of module
     *	@return	messages fromm module's message queue
     */
    vector<Message> getMessages(int module);
    
    /**
     *	@brief	retrieves the last message sent to the module with the given name
     *	@param 	module 	name of module
     *	@return	most recent message in module's queue of messages
     */
    KinematicsMessage getLastKinematicsMessage(int module);
    
    /**
     *	@brief	retrieves messages for a given module
     *	@param 	module 	name of module
     *	@return	messages fromm module's message queue
     */
    vector<KinematicsMessage> getKinematicsMessages(int module);
    /**
     *	@brief	retrieves the last message sent to the module with the given name
     *	@param 	module 	name of module
     *	@return	most recent message in module's queue of messages
     */
    TreeMessage getLastTreeMessage(int module);
    
    /**
     *	@brief	retrieves messages for a given module
     *	@param 	module 	name of module
     *	@return	messages fromm module's message queue
     */
    vector<TreeMessage> getTreeMessages(int module);
    /**
     * @brief dock two modules together
     * @param sm1 superbot module 1
     * @param sm2 superbot module 2
     * @param d1 dock face of module 1
     * @param d2 dock face of module 2
     */
    void DockTwoModules(ASuperBotModule* sm1, ASuperBotModule* sm2, ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief dock two modules together
     * @param sm1 superbot module 1
     * @param sm2 superbot module 2
     * @param d1 dock face of module 1
     * @param d2 dock face of module 2
     */
    void DockModuleToGround(ASuperBotModule* sm1, ModuleDockFace d1);
    /**
     * @brief get corrective docking transform
     * @param d1 dock 1
     * @param d2 dock 2
     */
    FTransform GetCorrectiveDockingTransform(ModuleDockFace d1, ModuleDockFace d2);
    /**
     *	@brief	Clears (deletes) the messages of a module with the given name
     *	@param 	module 	name of the module
     */
    void clearMessages(int module);
};
