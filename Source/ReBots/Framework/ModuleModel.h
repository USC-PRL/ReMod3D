#pragma once
#include <iostream>
#include "ModuleState.h"
/**
 * @class ModuleModel
 * @brief superbot model
 */
class REBOTS_API ModuleModel {
private:
    ModuleState currentState; /**< current state */
    ModuleState desiredState; /**< desired state */
public:
    /**
     * @brief set current state
     * @param cs current state
     */
    void SetCurrentState(ModuleState cs); 
    /**
     * @brief set desired state
     * @param cs desired state
     */
    void SetDesiredState(ModuleState ds);
    /**
     * @brief get current state
     * @return current state
     */
    ModuleState GetCurrentState();
    /**
     * @brief get desired state
     * @return desired state
     */
    ModuleState GetDesiredState();
    /**
     * @brief  constructor
     * @param mv motor vector (joint angles)
     * @param de docks enabled
     * @param deng docks engaged
     */
    ModuleModel(ModuleState cs, ModuleState ds);
    /**
     * @brief constructor
     */
    ModuleModel();
    
};
