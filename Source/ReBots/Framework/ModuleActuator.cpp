 
#include "ModuleActuator.h"
/**
* @brief set actuator name
* @param name name of actuator
*/
void ModuleActuator::SetName(int name) { this->Name = name; }
/**
* @brief get the name of the actuator
* @return actuator name
*/
int ModuleActuator::GetName() { return this->Name; }
/**
* @brief set actuator type
* @param T actuator type
*/
void ModuleActuator::SetType(ActuatorType T) { this->Type = T; }
/**
* @brief get type
* @return type of actuator
*/
ActuatorType ModuleActuator::GetType() { return this->Type; }
/**
* @brief constructor
*/
ModuleActuator::ModuleActuator() { this->Name = -1; }
/**
* @brief constructor
* @param name name of actuator
*/
ModuleActuator::ModuleActuator(int name) { this->Name = name;}
/**
* @brief constructor
* @param T actuator type
*/
ModuleActuator::ModuleActuator(ActuatorType T) { this->Type = T; }
/**
* @brief destructor
*/
ModuleActuator::~ModuleActuator(){}
