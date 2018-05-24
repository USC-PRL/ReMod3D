// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleConnectionPair.h"
/**
* @brief constructor
*/
ModuleConnectionPair::ModuleConnectionPair()
{
	this->SM1 = NULL;
	this->SM2 = NULL;
	this->D1 = DOCK_0;
	this->D2 = DOCK_0;
}
/**
* @brief constructor
* @param s1 superbot module 1
* @param s2 superbot module 2;
* @param d1 dock face 1
* @param d2 dock face 2
*/
ModuleConnectionPair::ModuleConnectionPair(AModularRobot* s1, AModularRobot* s2, ModuleDockFace d1, ModuleDockFace d2) {
	this->SM1 = s1;
	this->SM2 = s2;
	this->D1 = d1;
	this->D2 = d2;
}
/**
* @brief set superbot module 1
* @param s1
*/
void ModuleConnectionPair::SetSM1(AModularRobot* s1) {
	this->SM1 = s1;
}
/**
* @brief set  superbot module 2
* @param s2
*/
void ModuleConnectionPair::SetSM2(AModularRobot* s2) {
	this->SM2 = s2;
}
/**
* @brief get superbot module 1
* @return superbot module 1
*/
AModularRobot* ModuleConnectionPair::GetSM1() {
	return this->SM1;
}
/**
* @brief get  superbot module 2
* @param superbot module 2
*/
AModularRobot* ModuleConnectionPair::GetSM2() {
	return this->SM2;
}
/**
* @brief set dock face 1
* @param d1
*/
void ModuleConnectionPair::SetD1(ModuleDockFace d1) {
	this->D1 = d1;
}
/**
* @brief set dock face 2
* @param d2
*/
void ModuleConnectionPair::SetD2(ModuleDockFace d2) {
	this->D2 = d2;
}
/**
* @brief get dock face 1
* @return dock face 1
*/
ModuleDockFace ModuleConnectionPair::GetD1() {
	return this->D1;
}
/**
* @brief get dock face 2
* @return dock face 2
*/
ModuleDockFace ModuleConnectionPair::GetD2() {
	return this->D2;
}
/**
* @brief destructor
*/
ModuleConnectionPair::~ModuleConnectionPair()
{
}
