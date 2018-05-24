#pragma once
#include <vector>
/**
 *@class JointBehavior
 *@brief represents a joint behavior attached to a module
 *@date 05/20/2015
 *@author Thomas Collins
 */
class REBOTS_API JointBehavior
{
public:
    /**
     * @brief constructor
     */
	JointBehavior();
    /**
     * @brief destructor
     */
	virtual ~JointBehavior();
    /**
     * @brief step function of behavior
     * @param jointVals superbot sensor values
     * @param desiredVals desired sensor values
     * @return action values
     */
    virtual std::vector<float> Tick(std::vector<float> jointVals, std::vector<float> desiredVals,
                                    std::vector<float> tolerances) = 0;
};
