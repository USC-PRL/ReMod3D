// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleFlagSensor.h"

/**
* @brief set sensor name
* @param name sensor name
*/
void ModuleFlagSensor::SetName(int name) { this->Name = name; }
/**
* @brief get sensor name
* @return sensor name
*/
int ModuleFlagSensor::GetName() { return this->Name; }
/**
* @brief constructor
* @param name name of sensor
*/
ModuleFlagSensor::ModuleFlagSensor(int name) { this->Name = name; this->Type = FLAG_SENSOR; }
/**
* @brief constructor
*/
ModuleFlagSensor::ModuleFlagSensor() { this->Name = -1; this->Type = FLAG_SENSOR; };
/**
* @brief detructor
*/
ModuleFlagSensor::~ModuleFlagSensor() {}
