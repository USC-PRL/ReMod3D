// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleFlagActuator.h"

/**
* @brief set actuator name
* @param name name of actuator
*/
void ModuleFlagActuator::SetName(int name) { this->Name = name; }
/**
* @brief get the name of the actuator
* @return actuator name
*/
int ModuleFlagActuator::GetName() { return this->Name; }
/**
* @brief constructor
*/
ModuleFlagActuator::ModuleFlagActuator() { this->Name = -1; this->Type = FLAG_ACTUATOR; }
/**
* @brief constructor
* @param name name of actuator
*/
ModuleFlagActuator::ModuleFlagActuator(int name) { this->Name = name; this->Type = FLAG_ACTUATOR; }
/**
* @brief destructor
*/
ModuleFlagActuator::~ModuleFlagActuator() {}
