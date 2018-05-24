#pragma once
#include "Framework/RobotModuleBehavior.h"

/**
 *@class TwistBehavior
 *@brief represents a twist behavior attached to a module
 *@date 05/20/2015
 *@author Thomas Collins
 */
class REBOTS_API TwistBehavior : public RobotModuleBehavior
{
private:
private:
    float TwistAngle; /**< twist angle of behavior */
    int ProgramCounter = 0; /**< counter for the program */
public:
    /**
     * @brief constructor
     */
    TwistBehavior();
    /**
     * @brief constructor
     */
    TwistBehavior(float tAngle);
    /**
     * @brief destructor
     */
    virtual ~TwistBehavior();
    /**
     * @brief step function
     * @param jointVals sensor values
     * @param desiredVals desired values
     * @param tolerances tolerances in sensor values
     * @return action values
     */
    virtual void Tick(ModuleModel model);
};
