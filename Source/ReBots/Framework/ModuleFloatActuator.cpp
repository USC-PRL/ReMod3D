// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleFloatActuator.h"

/**
* @brief set actuator name
* @param name name of actuator
*/
void ModuleFloatActuator::SetName(int name) { this->Name = name; }
/**
* @brief get the name of the actuator
* @return actuator name
*/
int ModuleFloatActuator::GetName() { return this->Name; }
/**
* @brief constructor
*/
ModuleFloatActuator::ModuleFloatActuator() { this->Name = -1; this->Type = FLOAT_ACTUATOR; }
/**
* @brief constructor
* @param name name of actuator
*/
ModuleFloatActuator::ModuleFloatActuator(int name) { this->Name = name; this->Type = FLOAT_ACTUATOR; }
/**
* @brief destructor
*/
ModuleFloatActuator::~ModuleFloatActuator() {}
