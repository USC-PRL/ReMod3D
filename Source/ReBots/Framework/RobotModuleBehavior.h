#pragma once
#include <vector>
#include <utility>
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Framework/ModuleModel.h"
#include "Framework/ModuleConnectionPair.h"
/**
 * @enum ModuleAction
 * @brief superbot action
 */
enum ModuleAction {
    SET_MOTOR_0 = 0,
    SET_MOTOR_1,
    SET_MOTOR_2,
    SET_FRONT_DOCK_ENABLED,
    SET_FRONT_DOCK_ENGAGED,
    SET_BACK_DOCK_ENABLED,
    SET_BACK_DOCK_ENGAGED,
    SET_LEFT_DOCK_ENABLED,
    SET_LEFT_DOCK_ENGAGED,
    SET_RIGHT_DOCK_ENABLED,
    SET_RIGHT_DOCK_ENGAGED,
    SET_UP_DOCK_ENABLED,
    SET_UP_DOCK_ENGAGED,
    SET_DOWN_DOCK_ENABLED,
    SET_DOWN_DOCK_ENGAGED,
    SEND_MESSAGE_FRONT_DOCK,
    SEND_MESSAGE_BACK_DOCK,
    SEND_MESSAGE_LEFT_DOCK,
    SEND_MESSAGE_RIGHT_DOCK,
    SEND_MESSAGE_UP_DOCK,
    SEND_MESSAGE_DOWN_DOCK,
    SEND_RANGED_MESSAGE,
    SEND_KINEMATICS_MESSAGE_FRONT_DOCK,
    SEND_KINEMATICS_MESSAGE_BACK_DOCK,
    SEND_KINEMATICS_MESSAGE_LEFT_DOCK,
    SEND_KINEMATICS_MESSAGE_RIGHT_DOCK,
    SEND_KINEMATICS_MESSAGE_UP_DOCK,
    SEND_KINEMATICS_MESSAGE_DOWN_DOCK,
    SEND_TREE_MESSAGE_FRONT_DOCK,
    SEND_TREE_MESSAGE_BACK_DOCK,
    SEND_TREE_MESSAGE_LEFT_DOCK,
    SEND_TREE_MESSAGE_RIGHT_DOCK,
    SEND_TREE_MESSAGE_UP_DOCK,
    SEND_TREE_MESSAGE_DOWN_DOCK,
    CHANGE_P_GAIN_MOTOR_0,
    CHANGE_P_GAIN_MOTOR_1,
    CHANGE_P_GAIN_MOTOR_2,
    CHANGE_D_GAIN_MOTOR_0,
    CHANGE_D_GAIN_MOTOR_1,
    CHANGE_D_GAIN_MOTOR_2,
    DELAY_ACTION,
    SET_FRONT_DOCK_ENGAGED_TO_GROUND,
    SET_BACK_DOCK_ENGAGED_TO_GROUND,
    ENGAGE_FRONT_DOCK_TO_GROUND,
    ENGAGE_BACK_DOCK_TO_GROUND,
	SET_FRONT_DOCK_ENGAGED_TO_OBJECT,
	SET_BACK_DOCK_ENGAGED_TO_OBJECT,
	ENGAGE_FRONT_DOCK_TO_OBJECT,
	ENGAGE_BACK_DOCK_TO_OBJECT,
    ENGAGE_FRONT_DOCK_TO_STACKABLE,
    ENGAGE_BACK_DOCK_TO_STACKABLE,
	ENGAGE_OBJECT_TO_GROUND,
	CONNECT_MODULES,
    ENGAGE_STACKABLE_OBJECT_TO_GROUND
};
/**
 *@class Behavior
 *@brief represents a behavior attached to a module
 *@date 05/20/2015
 *@author Thomas Collins
 */
class REBOTS_API RobotModuleBehavior
{
protected:
    std::vector<std::pair<ModuleAction,float> > AngleActions; /**< angle actions */
    std::vector<std::pair<ModuleAction, float> > GainChangeActions; /**< gain change actions */
    std::vector<std::pair<ModuleAction,bool> > DockActions; /**< dock actions */
    std::vector<std::pair<ModuleAction,std::string> > MessageActions; /**< message actions */
    std::vector<std::pair<ModuleAction,KinematicsMessage> > KinematicsMessageActions; /**< kinematics message action */
    std::vector<std::pair<ModuleAction,TreeMessage> > TreeMessageActions; /**< tree actions */
    std::vector<std::pair<ModuleAction,int> > DelayActions; /**< have program "rest" */
	std::vector < std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> > > ConnectionActions; /**< connection actions */
    ModuleState goalState; /**< goal superbot state */
    std::string Name; /**< name of behavior */
public:
    /**
     * @brief get name of behavior
     * @return name
     */
    std::string GetName();
    /**
     * @brief set behavior name
     */
    void SetName(std::string n);
    /**
     * @brief clear all actions
     */
    void ClearAllActions();
    /**
     * @brief add angle action
     */
    void AddAngleAction(std::pair<ModuleAction,float> action);
    /**
     * @brief add dock action
     */
    void AddDockAction(std::pair<ModuleAction,bool> action);
    /**
     * @brief add gain change action
     */
    void AddGainChangeAction(std::pair<ModuleAction,float> action);
    /**
     * @brief add dock action
     */
    void AddMessageAction(std::pair<ModuleAction,std::string> action);
    /**
     * @brief add dock action
     */
    void AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage> action);
	/**
	* @brief add connection message
	*/
	void AddConnectionAction(std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> > action);
    /**
     * @brief add dock action
     */
    void AddTreeMessageAction(std::pair<ModuleAction,TreeMessage> action);
    /**
     * @brief add delay action
     */
    void AddDelayAction(std::pair<ModuleAction,int> action);
    /**
     * @brief get angle actions
     * @return angle actions
     */
    std::vector<std::pair<ModuleAction, float> > GetAngleActions();
    /**
     * @brief get dock actions
     * @return dock actions
     */
    std::vector<std::pair<ModuleAction, bool> > GetDockActions();
    /**
     * @brief get message actions
     * @return message actions
     */
    std::vector<std::pair<ModuleAction, std::string> > GetMessageActions();
    /**
     * @brief get kinematics message actions
     * @return kinematics message actions
     */
    std::vector<std::pair<ModuleAction, KinematicsMessage> > GetKinematicsMessageActions();
    /**
     * @brief get kinematics message actions
     * @return kinematics message actions
     */
    std::vector<std::pair<ModuleAction, TreeMessage> > GetTreeMessageActions();
	/**
	* @brief get connection actions
	* @return connection actions
	*/
	std::vector < std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> > > GetConnectionActions();
    /**
     * @brief get delay actions
     */
    std::vector<std::pair<ModuleAction,int> > GetDelayActions();
    /**
     * @brief get gain change actions
     * @return gain change actions
     */
    std::vector<std::pair<ModuleAction, float> > GetGainChangeActions();
    /**
     * @brief constructor
     */
    RobotModuleBehavior();
    /**
     * @brief destructor
     */
    virtual ~RobotModuleBehavior();
    /**
     * @brief step function of behavior
     * @param jointVals superbot sensor values
     * @param desiredVals desired sensor values
     * @return action values
     */
    virtual void Tick(ModuleModel model) = 0;
};
