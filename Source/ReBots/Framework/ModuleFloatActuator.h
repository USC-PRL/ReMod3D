// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ModuleActuator.h"
class ASuperBotModule;
/**
 * 
 */
class REBOTS_API ModuleFloatActuator : public ModuleActuator
{
private:
	int Name; /**< name of the actuator*/
public:
	/**
	* @brief set actuator value
	* @param val actuator value
	*/
	virtual void SetFloatValue(ASuperBotModule* M, float Val) {};
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
	ModuleFloatActuator();
	/**
	* @brief constructor
	* @param name actuator name
	*/
	ModuleFloatActuator(int name);
	/**
	* @brief destructur
	*/
	~ModuleFloatActuator();
};
