// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Framework/Message.h"
#include "Framework/RangedMessage.h"
#include "Framework/ModuleMessage.h"
#include "SuperBot/SuperBotModule.h"
#include "Framework/ModuleDock.h"
#include "Framework/ConstraintMonitor.h"
#include "CustomActors/FloorCollisionActor.h"
#include "CustomActors/BoundingSphere.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/ModuleConnector.h"
#include "CustomActors/ManipulatorObjectActor.h"
#include "Framework/TreeMessage.h"
#include "CustomActors/BoundingBoxActor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include <map>
#include <iostream>
#include <vector>
#include <utility>
#include "ReBotsSimulatorGameMode.generated.h"
using namespace std;
/**
 * 
 */
UCLASS()
class REBOTS_API AReBotsSimulatorGameMode : public AGameMode
{
	GENERATED_BODY()
private:
    vector<ModuleDock> docksToMonitor; /**< docks for the experiment to moonitor */
	vector<ModuleConnector> connectorsToMonitor;/**<connectors for the experiment to monitor */
    float errorPositionDock = 0.05; /**< position error for docking */
    float errorOrientationDock = 0.05; /**< orientation error for docking */
    vector<pair<int, ModuleDockFace> > deleteQueue; /**< queue of docks to delete from monitor */
    vector<ModuleDock> addQueue; /**< docks to add to the monitor */
	vector<pair<int, ModuleDockFace> > rmQueue; /**< remove queue */
	vector<ModuleConnector> addConnectorQueue;/**< add connector queue */
    map<int, map<ModuleDockFace, ModuleDock> > connections; /**< connections between modules */
	map<int, map<ModuleDockFace, ModuleConnector> > moduleConnections; /**< module connections */
    map<int, vector<KinematicsMessage> > messageRoomKinematics; /**< kinematic message room */
    map<int, vector<Message> > messageRoom; /**< message boxes for modules (by name) */
    map<int, vector<RangedMessage> > messageRoomRanged; /**< message boxes for ranged messages for modules (by name) */
    map<int, vector<TreeMessage> > messageRoomSuperBotTree; /**< message boxes for super bot tree messages */
	map<std::pair<ASuperBotModule*, ModuleDockFace>, APhysicsConstraintActor*> InterModuleConstraints; /**< message boxes for super bot tree messages */
	map<int, vector<ModuleMessage> > moduleMessageRoom; /**< module message room */
    bool FirstTick = true; /**< is this the first tick of the game mode */
    ConstraintMonitor CMonitor; /**< constraint monitor */
    bool DockDebug = true; /**< dock debug output */
    bool FirstMove = true; /**< first move? */
    int waitCounter = 30; /**< wait counter */
    AStaticMeshActor* Floor; /**< floor actor */
	AManipulatorObjectActor* ManipObject; /**< manipulator object actor*/
	APhysicsConstraintActor* ManipConstraintToGround; /**< manipulator constraint to ground */
    map<int, ASuperBotModule*> modulesMap; /**< in order map of modules to integers */
    map<ASuperBotModule*,int> modsToIDs; /**< modules to ids */
    bool DockBackToGroundInitially = true; /**< dock back dock of first module to ground initially */
    bool DockFrontToGroundInitially = false; /**< dock front dock of first module to ground initially */
    AReferenceFrameActor* FinalFKActor = NULL; /**< final fk of manipulator */
    AReferenceFrameActor* BaseTransformActor = NULL; /**< render base transform */
    AReferenceFrameActor* TargetTransformActor = NULL; /**< target transform */
	AReferenceFrameActor* TargetFootActor2 = NULL;
	AReferenceFrameActor* ManipObjectTransformActor = NULL; /**< manip object transform actor */
    vector<AReferenceFrameActor*> BestTransformsFound; /**< best transforms found */
    AReferenceFrameActor* TargetFootActor = NULL; /**< target foot placement */
    vector<ABoundingBoxActor*> BoundingBoxes; /**< bounding box ee actor */
	vector<AReferenceFrameActor*> TargetTransformActors; /**< target transform actors*/
	vector<AReferenceFrameActor*> EEActors; /**< end effector actors*/
    vector<vector<ABoundingBoxActor*> > BoundingBoxesSpecific; /**< bbs */
    ABoundingBoxActor* BoundingBoxGround = NULL; /**< bounding box ground */
    vector<ABoundingSphere*> BoundingSpheres; /**< bounding sphers */
    AReferenceFrameActor* ActualGroundFromModule = NULL; /**< actual ground location from base module frame */
public:
	/**
	* @brief get manipulator object
	* @return manipulator object
	*/
	AManipulatorObjectActor* GetManipObject();
	/**
	* @brief get constraint between floor and object
	*/
	APhysicsConstraintActor* GetManipConstraint();
    /**
     * @brief game mode constructor
     * @param ObjectInitializer initializer
     */
    AReBotsSimulatorGameMode(const FObjectInitializer& ObjectInitializer);
    /**
     * @brief advance the simulation
     * @param DeltaSeconds fraction of a second by which to advance simulation
     */
    virtual void Tick( float DeltaSeconds ) override;
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
	* @brief send module message to dock face
	* @param sendingModule sending module
	* @param Face module dock face
	* @param Mes message
	*/
	void sendModuleMessageToDock(ASuperBotModule *sendingModule, ModuleDockFace Face, std::string Mes);
    /**
     *	@brief	retrieves the last message sent to the module with the given name
     *	@param 	module 	name of module
     *	@return	most recent message in module's queue of messages
     */
    Message getLastMessage(int module);
	/**
	*	@brief	retrieves the last message sent to the module with the given name
	*	@param 	module 	name of module
	*	@return	most recent message in module's queue of messages
	*/
	ModuleMessage getLastModuleMessage(int module);
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
	* @brief get module messages
	* @param module module name
	* @return module messages
	*/
	vector<ModuleMessage> getModuleMessages(int module);
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
	* @brief undock two modules
	* @param sm1 superbot module 1
	* @param sm2 superbot module 2
	* @param d1 dock face of module 1
	* @param d2 dock face of module 2
	*/
	void UnDockTwoModules(ASuperBotModule* sm1, ASuperBotModule* sm2, ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief dock two modules together
     * @param sm1 superbot module 1
     * @param sm2 superbot module 2
     * @param d1 dock face of module 1
     * @param d2 dock face of module 2
     */
    void DockModuleToGround(ASuperBotModule* sm1, ModuleDockFace d1);
	/**
	* @brief dock object to ground
	* @param a manipulator object actor
	*/
	void DockObjectToGround(AManipulatorObjectActor* a);
	/**
	* @brief dock two modules together
	* @param sm1 superbot module 1
	* @param d1 superbot module 1 dock face
	* @param actor manipulator actor to which to connect
	*/
	void DockModuleToObject(ASuperBotModule* sm1, ModuleDockFace d1, AManipulatorObjectActor* actor);
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
	/**
	 * @brief render behavior-specific stuff
	 * @param Mod superbot module
	 * @param EngagedToGround is module engaged to ground?
	 * @param D dock face connected to ground
	 */
	void RenderBehaviorData(ASuperBotModule *Mod, bool EngagedToGround, ModuleDockFace D);
    
};
