// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModulePoseSensor.h"
/**
* @brief set sensor name
* @param name sensor name
*/
void ModulePoseSensor::SetName(int name) { this->Name = name; }
/**
* @brief get sensor name
* @return sensor name
*/
int ModulePoseSensor::GetName() { return this->Name; }
/**
* @brief constructor
* @param name name of sensor
*/
ModulePoseSensor::ModulePoseSensor(int name) { this->Name = name; this->Type = POSE_SENSOR; }
/**
* @brief constructor
*/
ModulePoseSensor::ModulePoseSensor() { this->Name = -1; this->Type = POSE_SENSOR; };
/**
* @brief detructor
*/
ModulePoseSensor::~ModulePoseSensor() {}

