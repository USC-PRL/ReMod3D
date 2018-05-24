// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include "ModuleActuator.h"
class ASuperBotModule;

/**
 * @class ModuleFlagActuator
 * @brief module flag actuator
 */
class REBOTS_API ModuleFlagActuator : public ModuleActuator
{
private:
	int Name; /**< name of the actuator*/
public:
	/**
	* @brief set actuator value
	* @param val actuator value
	*/
	virtual void SetFlagValue(ASuperBotModule* M, std::vector<bool>& val) {};
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
	* @brief constructor
	*/
	ModuleFlagActuator();
	/**
	* @brief constructor
	* @param name actuator name
	*/
	ModuleFlagActuator(int name);
	/**
	* @brief destructur
	*/
	~ModuleFlagActuator();
};
