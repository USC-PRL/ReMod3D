// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleMessageSensor.h"

/**
* @brief set sensor name
* @param name sensor name
*/
void ModuleMessageSensor::SetName(int name) { this->Name = name; }
/**
* @brief get sensor name
* @return sensor name
*/
int ModuleMessageSensor::GetName() { return this->Name; }
/**
* @brief constructor
* @param name name of sensor
*/
ModuleMessageSensor::ModuleMessageSensor(int name) { this->Name = name; this->Type = MESSAGE_SENSOR; }
/**
* @brief constructor
*/
ModuleMessageSensor::ModuleMessageSensor() { this->Name = -1; this->Type = MESSAGE_SENSOR; };
/**
* @brief detructor
*/
ModuleMessageSensor::~ModuleMessageSensor() {}
