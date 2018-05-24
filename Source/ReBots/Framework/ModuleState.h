#pragma once
#include <vector>
#include "Framework/Message.h"
#include "Framework/RangedMessage.h"
#include "Framework/KinematicsMessage.h"
#include "Framework/TreeMessage.h"
#include "Framework/ModuleMotorVector.h"
/**
 * @class ModuleState
 * @brief superbot state
 */
class REBOTS_API ModuleState {
private:
    ModuleMotorVector smv; /**< joint angles */
    int IDNumber; /**< module ID Number */
    std::vector<bool> DocksEnabledStatus; /**< docks enabled status */
    std::vector<bool> DocksEngagedStatus; /** docks engaged status */
    std::vector<bool> DocksEnabledToGroundStatus; /**< docks enabled to ground status */
    std::vector<bool> DocksEngagedToGroundStatus; /**< docks engaged to ground status */
	std::vector<bool> DocksEnabledToObjectStatus; /**< docks enabled to object status*/
	std::vector<bool> DocksEngagedToObjectStatus; /**< docks engaged to object status */
    std::vector<Message> messages; /**< dock messages */
    std::vector<RangedMessage> rangedMessages; /**< ranged messages */
    std::vector<KinematicsMessage> kinematicsMessages; /**< Kinematics messages */
    std::vector<TreeMessage> treeMessages; /**< tree messages */
public:
    /**
     * @brief set messages
     * @param m messages
     */
    void SetMessages(std::vector<Message> m);
    /**
     * @brief set messages
     * @param rm messages
     */
    void SetRangedMessages(std::vector<RangedMessage> rm);
    /**
     * @brief get messages
     * @return messages
     */
    std::vector<Message> GetMessages();
    /**
     * @brief get ranged messages
     * @return ranged  messages
     */
    std::vector<RangedMessage> GetRangedMessages();
    /**
     * @brief get ranged messages
     * @return ranged  messages
     */
    std::vector<KinematicsMessage> GetKinematicsMessages();
    /**
     * @brief get tree messages
     * @return get tree messages
     */
    std::vector<TreeMessage> GetTreeMessages();
    /**
     * @brief set messages
     * @param rm messages
     */
    void SetKinematicsMessages(std::vector<KinematicsMessage> kms);
    /**
     * @brief set tree messages
     * @param tms tree messages
     */
    void SetTreeMessages(std::vector<TreeMessage> tms);
    /**
     * @brief set joint angles
     * @param mv motor angles
     */
    void SetJointAngles(ModuleMotorVector mv);
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    void SetDocksEnabledStatus(std::vector<bool> docksEna);
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    void SetDocksEngagedStatus(std::vector<bool> docksEng);
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    void SetDocksEnabledToGroundStatus(std::vector<bool> docksEna);
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    void SetDocksEngagedToGroundStatus(std::vector<bool> docksEng);
	/**
	* @brief set docks enabled
	* @param docksEna docks enabled
	*/
	void SetDocksEnabledToObjectStatus(std::vector<bool> docksEna);
	/**
	* @brief set docks enabled
	* @param docksEna docks enabled
	*/
	void SetDocksEngagedToObjectStatus(std::vector<bool> docksEng);
    /**
     * @brief set joint angles
     * @param mv motor angles
     */
    ModuleMotorVector GetJointAngles();
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    std::vector<bool> GetDocksEnabledStatus();
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    std::vector<bool> GetDocksEngagedStatus();
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    std::vector<bool> GetDocksEnabledToGroundStatus();
    /**
     * @brief set docks enabled
     * @param docksEna docks enabled
     */
    std::vector<bool> GetDocksEngagedToGroundStatus();
	/**
	* @brief set docks enabled
	* @param docksEna docks enabled
	*/
	std::vector<bool> GetDocksEnabledToObjectStatus();
	/**
	* @brief set docks enabled
	* @param docksEna docks enabled
	*/
	std::vector<bool> GetDocksEngagedToObjectStatus();
    /**
     * @brief set id number
     */
    void SetIDNumber(int idn);
    /**
     * @brief get id number
     */
    int GetIDNumber();
    /**
     * @brief constructor
     */
    ModuleState();
    
};
