// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleJoint.h"
/**
* @brief set the module name
* @param name name of module
*/
void ModuleJoint::SetModuleName(std::string name) { this->ModuleName = name; }
/**
* @brief set the name of the link
* @param name name of link
*/
void ModuleJoint::SetJointName(std::string name) { this->JointName = name; }
/**
* @brief set joint reference
* @param joint joint reference
*/
void ModuleJoint::SetJointReference(UPhysicsConstraintComponent* joint) { this->Joint = joint; }
/**
* @brief get module name
* @return module name
*/
std::string ModuleJoint::GetModuleName() { return this->ModuleName; }
/**
* @brief get joint name
* @return joint name
*/
std::string ModuleJoint::GetJointName() { return this->JointName; }
/**
* @brief get joint reference
* @return joint reference
*/
UPhysicsConstraintComponent* ModuleJoint::GetJointReference() { return this->Joint; }
/**
* @brief constructor
*/
ModuleJoint::ModuleJoint() {}
/**
* @brief constructor
* @param name module name
* @param cname constraint name
* @param c constraint reference
*/
ModuleJoint::ModuleJoint(std::string name, std::string cname, UPhysicsConstraintComponent* c) {
	this->ModuleName = name;
	this->JointName = cname;
	this->Joint = c;
}
/**
* @brief destructor
*/
ModuleJoint::~ModuleJoint() {}
