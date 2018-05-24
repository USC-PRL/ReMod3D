// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Framework/ModuleDock.h"
class AModularRobot;

/**
 * @class ModuleConnectionPair
 * @brief information about the connection to be made
 */
class REBOTS_API ModuleConnectionPair
{
private:
	AModularRobot* SM1; /**< superbot module 1*/
	AModularRobot* SM2; /**< superbot module 2 */
	ModuleDockFace D1; /**< dock face 1 */
	ModuleDockFace D2; /**< dock face 2 */
public:
	/**
	* @brief constructor
	*/
	ModuleConnectionPair();
	/**
	* @brief constructor
	* @param s1 superbot module 1
	* @param s2 superbot module 2;
	* @param d1 dock face 1
	* @param d2 dock face 2
	*/
	ModuleConnectionPair(AModularRobot* s1, AModularRobot* s2, ModuleDockFace d1, ModuleDockFace d2);
	/**
	* @brief set superbot module 1
	* @param s1
	*/
	void SetSM1(AModularRobot* s1);
	/**
	* @brief set  superbot module 2
	* @param s2
	*/
	void SetSM2(AModularRobot* s2);
	/**
	* @brief get superbot module 1
	* @return superbot module 1
	*/
	AModularRobot* GetSM1();
	/**
	* @brief get  superbot module 2
	* @param superbot module 2
	*/
	AModularRobot* GetSM2();
	/**
	* @brief set dock face 1
	* @param d1
	*/
	void SetD1(ModuleDockFace d1);
	/**
	* @brief set dock face 2
	* @param d2
	*/
	void SetD2(ModuleDockFace d2);
	/**
	* @brief get dock face 1
	* @return dock face 1
	*/
	ModuleDockFace GetD1();
	/**
	* @brief get dock face 2
	* @return dock face 2
	*/
	ModuleDockFace GetD2();
	/**
	* @brief destructor
	*/
	~ModuleConnectionPair();
};
