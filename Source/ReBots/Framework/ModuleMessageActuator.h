// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ModuleMessage.h"
#include "ModuleActuator.h"
class ASuperBotModule;
/**
 * 
 */
class REBOTS_API ModuleMessageActuator : public ModuleActuator
{
private:
	int Name; /**< name of the actuator*/
public:
	/**
	* @brief set actuator value
	* @param val actuator value
	*/
	virtual void SetMessageValue(ASuperBotModule* M, ModuleMessage Val) {};
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
	ModuleMessageActuator();
	/**
	* @brief constructor
	* @param name actuator name
	*/
	ModuleMessageActuator(int name);
	/**
	* @brief destructur
	*/
	~ModuleMessageActuator();
};
