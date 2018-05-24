#pragma once
#include <vector>
#include "ModuleMessage.h"
class ASuperBotModule;
enum ActuatorType {
	FLOAT_ACTUATOR = 0,
	FLAG_ACTUATOR,
	MESSAGE_ACTUATOR
};
/**
 * @class ModuleActuator
 * @brief representation of a module actuator
 * @author Thomas Collins
 */
class REBOTS_API ModuleActuator
{
protected:
	int Name; /**< name of the actuator*/
	ActuatorType Type; /**< type of actuator */
public:
	/**
	* @brief set actuator value
	* @param val actuator value
	*/
	virtual void SetFloatValue(ASuperBotModule* M, float val) {};
	/**
	* @brief set actuator value
	* @param val actuator value
	*/
	virtual void SetFlagValue(ASuperBotModule* M, std::vector<bool>& val) {};
	/**
	* @brief set actuator value
	* @param val actuator value
	*/
	virtual void SetMessageValue(ASuperBotModule* M, ModuleMessage Mes) {}
	/**
	* @brief set the name of the actuator
	* @param name name of actuator
	*/
	void SetName(int name);
	/**
	* @brief get the name of the actuator
	* @return actuator name
	*/
	int GetName();
	/**
	* @brief set actuator type
	* @param T actuator type
	*/
	void SetType(ActuatorType T);
	/**
	* @brief get type
	* @return type of actuator
	*/
	ActuatorType GetType();
	/**
	* @brief constructor
	*/
	ModuleActuator();
	/**
	* @brief constructor
	* @param name actuator name
	*/
	ModuleActuator(int name);
	/**
	* @brief constructor
	* @param T actuator type
	*/
	ModuleActuator(ActuatorType T);
	/**
	* @brief destructur
	*/
	~ModuleActuator();
};
