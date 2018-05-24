// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleFloatSensor.h"
/**
* @brief set sensor name
* @param name sensor name
*/
void ModuleFloatSensor::SetName(int name) { this->Name = name; }
/**
* @brief get sensor name
* @return sensor name
*/
int ModuleFloatSensor::GetName() { return this->Name; }
/**
* @brief constructor
* @param name name of sensor
*/
ModuleFloatSensor::ModuleFloatSensor(int name) { this->Name = name; this->Type = FLOAT_SENSOR; }
/**
* @brief constructor
*/
ModuleFloatSensor::ModuleFloatSensor() { this->Name = -1; this->Type = FLOAT_SENSOR; };
/**
* @brief detructor
*/
ModuleFloatSensor::~ModuleFloatSensor() {}
