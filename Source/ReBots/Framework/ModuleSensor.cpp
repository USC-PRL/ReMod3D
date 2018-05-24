// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleSensor.h"

/**
* @brief set sensor name
* @param name sensor name
*/
void ModuleSensor::SetName(int name) { this->Name = name; }
/**
* @brief get sensor name
* @return sensor name
*/
int ModuleSensor::GetName() { return this->Name; }
/**
* @brief constructor
* @param name name of sensor
*/
ModuleSensor::ModuleSensor(int name) { this->Name = name; }
/**
* @brief constructor
*/
ModuleSensor::ModuleSensor() { this->Name = -1; };
/**
* @brief set type of sensor
* @param T type of sensor
*/
void ModuleSensor::SetType(SensorType T) { this->Type = T; }
/**
* @brief get type of sensor
* @return type of sensor
*/
SensorType ModuleSensor::GetType() { return this->Type; }
/**
* @brief detructor
*/
ModuleSensor::~ModuleSensor() {}
