 
#include "ModuleModel.h"
/**
 * @brief set current state
 * @param cs current state
 */
void ModuleModel::SetCurrentState(ModuleState cs) {
    this->currentState = cs;
}
/**
 * @brief set desired state
 * @param cs desired state
 */
void ModuleModel::SetDesiredState(ModuleState ds) {
    this->desiredState = ds;
}
/**
 * @brief get current state
 * @return current state
 */
ModuleState ModuleModel::GetCurrentState() {
    return this->currentState;
}
/**
 * @brief get desired state
 * @return desired state
 */
ModuleState ModuleModel::GetDesiredState() {
    return this->desiredState;
}
/**
 * @brief  constructor
 * @param mv motor vector (joint angles)
 * @param de docks enabled
 * @param deng docks engaged
 */
ModuleModel::ModuleModel(ModuleState cs, ModuleState ds) {
    this->currentState = cs;
    this->desiredState = ds;
}
/**
 * @brief constructor
 */
ModuleModel::ModuleModel(){}
