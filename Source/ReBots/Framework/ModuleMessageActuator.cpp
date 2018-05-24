// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleMessageActuator.h"

/**
* @brief set actuator name
* @param name name of actuator
*/
void ModuleMessageActuator::SetName(int name) { this->Name = name; }
/**
* @brief get the name of the actuator
* @return actuator name
*/
int ModuleMessageActuator::GetName() { return this->Name; }
/**
* @brief constructor
*/
ModuleMessageActuator::ModuleMessageActuator() { this->Name = -1; this->Type = MESSAGE_ACTUATOR; }
/**
* @brief constructor
* @param name name of actuator
*/
ModuleMessageActuator::ModuleMessageActuator(int name) { this->Name = name; this->Type = MESSAGE_ACTUATOR; }
/**
* @brief destructor
*/
ModuleMessageActuator::~ModuleMessageActuator() {}

