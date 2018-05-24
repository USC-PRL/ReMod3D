#pragma once
#include "JointBehavior.h"

/**
 *@class GoToAnglesBehavior
 *@brief represents a go to angles behavior behavior attached to a module
 *@date 05/20/2015
 *@author Thomas Collins
 */
class REBOTS_API GoToAnglesBehavior : public JointBehavior
{
private:
    std::vector<float> desJoints; /**< desired joints */
public:
    /**
     * @brief constructor
     * @param dj desired joints
     */
    GoToAnglesBehavior(std::vector<float> dj);
    /**
     * @brief destructor
     */
    virtual ~GoToAnglesBehavior();
    /**
     * @brief step function
     * @param jointVals sensor values
     * @param desiredVals desired values
     * @param tolerances tolerances in sensor values
     * @return action values
     */
    virtual std::vector<float> Tick(std::vector<float> jointVals, std::vector<float> desiredVals,
                                    std::vector<float> tolerances);
    /**
     * @brief are current joint angles close to desired ones
     * @param jointVals sensor values
     * @param desiredVals desired sensor values
     * @param tolerances tolerances
     * @return true if desired and current angles "same", false otherwise.
     */
    bool areCurrentSensorsDesired(std::vector<float> jointVals, std::vector<float> desiredVals,
                                  std::vector<float> tolerances);
};
