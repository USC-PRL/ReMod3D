// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include<iostream>
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
/**
 * @class ModuleJoint
 * @brief module joint representation
 */
class REBOTS_API ModuleJoint
{
private:
	std::string ModuleName; /**< name of module */
	std::string JointName; /**< name of the link*/
	UPhysicsConstraintComponent* Joint; /**<representation of the link itself */
public:
	/**
	* @brief set the module name
	* @param name name of module
	*/
	void SetModuleName(std::string name);
	/**
	* @brief set the name of the joint
	* @param name name of joint
	*/
	void SetJointName(std::string name);
	/**
	* @brief set joint reference
	* @param joint joint reference
	*/
	void SetJointReference(UPhysicsConstraintComponent* joint);
	/**
	* @brief get module name
	* @return module name
	*/
	std::string GetModuleName();
	/**
	* @brief get link name
	* @return module name
	*/
	std::string GetJointName();
	/**
	* @brief get joint reference
	* @return joint reference
	*/
	UPhysicsConstraintComponent* GetJointReference();
	/**
	* @brief constructor
	*/
	ModuleJoint();
	/**
	* @brief constructor
	* @param name module name
	* @param cname constraint name
	* @param c constraint reference
	*/
	ModuleJoint(std::string name, std::string cname, UPhysicsConstraintComponent* c);
	/**
	* @brief destructor
	*/
	~ModuleJoint();
};
