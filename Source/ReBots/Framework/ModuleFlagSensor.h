// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include "ModuleDockFace.h"
#include "ModuleSensor.h"
class ASuperBotModule;
/**
 * 
 */
class REBOTS_API ModuleFlagSensor : public ModuleSensor
{
private:
	int Name; /**< name of sensor */
public:
	/**
	* @brief get the current  value of the sensor
	* @return current floating point value of the sensor
	*/
	virtual std::vector<bool> GetFlagValue(ASuperBotModule* M) { return std::vector<bool> {false}; };
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
	ModuleFlagSensor(int name);
	/**
	* @brief constructor
	*/
	ModuleFlagSensor();
	/**
	* @brief detructor
	*/
	virtual ~ModuleFlagSensor();
};
