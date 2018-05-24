// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleDock.h"
/**
 * @brief constructor
 * @param df Dock face
 * @param dc dock component
 * @param m module
 */
ModuleDock::ModuleDock(ModuleDockFace df, UStaticMeshComponent* dc, AModularRobot* m) {
    this->Face = df;
    this->DockComponent  = dc;
    this->Module = m;
    this->DockEnabled = true;
    this->DockEngaged = false;
}
/**
 * @brief constructor
 */
ModuleDock::ModuleDock()
{
    this->Face = DOCK_6;
    this->DockComponent = NULL;
    this->Module = NULL;
    this->DockEnabled = true;
    this->DockEngaged = false;
}
/**
 * @brief destructor
 */
ModuleDock::~ModuleDock(){}
/**
 * @brief set dock face
 * @param df dock face
 */
void ModuleDock::SetFace(ModuleDockFace df) {this->Face = df;}
/**
 * @brief set dock component
 * @param dc dock component
 */
void ModuleDock::SetDockComponent(UStaticMeshComponent* mc) {this->DockComponent = mc;}
/**
 * @brief set dock module
 * @param m dock module
 */
void ModuleDock::SetModule(AModularRobot* m) {this->Module = m;}
/**
 * @brief set dock engaged
 * @param dengaged dock engaged
 */
void ModuleDock::SetDockEngaged(bool dengaged) {this->DockEngaged = dengaged;}
/**
 * @brief set dock enabled
 * @param denabled dock enabled
 */
void ModuleDock::SetDockEnabled(bool denabled) {this->DockEnabled = denabled;}
/**
 * @brief set dock enabled to ground
 * @param etg enabled to ground
 */
void ModuleDock::SetDockEnabledToGround(bool etg) {this->DockEnabledToGround = etg;}
/**
 * @brief set dock engaged to ground
 * @param etg engaged to ground
 */
void ModuleDock::SetDockEngagedToGround(bool etg) {this->DockEngagedToGround = etg;}
/**
* @brief set dock enabled to ground
* @param etg enabled to ground
*/
void ModuleDock::SetDockEnabledToObject(bool eto) { this->DockEnabledToObject = eto; }
/**
* @brief set dock engaged to ground
* @param etg engaged to ground
*/
void ModuleDock::SetDockEngagedToObject(bool eto) { this->DockEngagedToObject = eto; }
/**
 * @brief get dock face
 * @return dock face
 */
ModuleDockFace ModuleDock::GetDockFace() {return this->Face;}
/**
 * @brief get dock component
 * @return dock component
 */
UStaticMeshComponent* ModuleDock::GetDockComponent() {return this->DockComponent;}
/**
 * @brief get dock module
 * @return dock module
 */
AModularRobot* ModuleDock::GetModule() {return this->Module;}
/**
 * @brief get dock engaged
 * @return dock engaged
 */
bool ModuleDock::GetDockEngaged() {return this->DockEngaged;}
/**
 * @brief get dock enabled
 * @return dock enabled
 */
bool ModuleDock::GetDockEnabled() {return this->DockEnabled;}
/**
 * @brief get dock enabled to ground
 * @return dock enabled to ground
 */
bool ModuleDock::GetDockEnabledToGround() {return this->DockEnabledToGround;}
/**
 * @brief get dock engaged to ground
 * @return dock engaged to ground
 */
bool ModuleDock::GetDockEngagedToGround() {return this->DockEngagedToGround;}
/**
* @brief get dock enabled to ground
* @return dock enabled to ground
*/
bool ModuleDock::GetDockEnabledToObject() { return this->DockEnabledToObject;}
/**
* @brief get dock engaged to ground
* @return dock engaged to ground
*/
bool ModuleDock::GetDockEngagedToObject() { return this->DockEngagedToObject; }
