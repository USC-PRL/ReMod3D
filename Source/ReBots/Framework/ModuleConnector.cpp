// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleConnector.h"

/**
* @brief set module link
* @param link module link
*/
void ModuleConnector::SetModuleLink(ModuleLink link) { this->Link = link; }
/**
* @brief set dock face
* @param face dock face
*/
void ModuleConnector::SetDockFace( ModuleDockFace d) { this->DockFace = d; }
/**
* @brief set name of bone
* @param BN bone name
*/
void ModuleConnector::SetBoneName(std::string BN) { this->BoneName = BN; }
/**
* @brief get module link
* @return module link reference
*/
ModuleLink ModuleConnector::GetModuleLink() { return this->Link; }
/**
* @brief get dock face
* @return dock face
*/
ModuleDockFace ModuleConnector::GetDockFace() { return this->DockFace; }
/**
* @brief get bone name
* @return bone name
*/
std::string ModuleConnector::GetBoneName() { return this->BoneName; }
/**
* @brief constructor
* @param l module link
* @param d module dock face
* @param b bone name
*/
ModuleConnector::ModuleConnector(ModuleLink l,  ModuleDockFace d, std::string b) {
	this->Link = l;
	this->DockFace = d;
	this->BoneName = b;
}
/**
*  @brief constructor
*/
ModuleConnector::ModuleConnector() {}
/**
* @brief destructor
*/
ModuleConnector::~ModuleConnector() {}
