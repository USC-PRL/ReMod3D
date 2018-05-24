// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ModuleMessage.h"
#include "ModuleSensor.h"
/**
 * 
 */
class REBOTS_API ModuleMessageSensor : public ModuleSensor
{
private:
	int Name; /**< name of sensor */
public:
	/**
	* @brief get the current  value of the sensor
	* @return current floating point value of the sensor
	*/
	virtual std::vector<ModuleMessage> GetMessageValue(ASuperBotModule* M) { return std::vector<ModuleMessage>{}; };
	/**
	* @brief set sensor name
	* @param name sensor name
	*/
	void SetName(int name);
	/**
	* @brief get sensor name
	* @return sensor name
	*/
	int GetName();
	/**
	* @brief constructor
	* @param name name of sensor
	*/
	ModuleMessageSensor(int name);
	/**
	* @brief constructor
	*/
	ModuleMessageSensor();
	/**
	* @brief detructor
	*/
	virtual ~ModuleMessageSensor();
};
