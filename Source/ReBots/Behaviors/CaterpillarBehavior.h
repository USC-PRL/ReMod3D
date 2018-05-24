#pragma once
#include "Framework/RobotModuleBehavior.h"
#include <sstream>
using namespace std;
/**
 *@class TwistBehavior
 *@brief represents a twist behavior attached to a module
 *@date 05/20/2015
 *@author Thomas Collins
 */
class REBOTS_API CaterpillarBehavior : public RobotModuleBehavior
{
private:
    std::vector<float> desJoints; /**< desired joints */
    float twistAngle; /**< twist angle of behavior */
    float amplitude; /**< amplitude of sine wave */
    int stateCounter; /**< state counter */
    int stateMax; /**< maximum number of states */
    bool hasReceivedMessageFromInBack; /**< have received message from in front */
    bool hasReceivedMessageFromInFront; /**< have received message from in back */
    bool hasSentMessageBack; /**< have sent message back */
    bool hasHeardGo; /**< have I heard GO? */
    bool hasSentMessageForward; /**< have I sent message forward */
    int period; /**< period of sine wave */
    int periodStep; /**< period step of sine wave */
    int programCounter; /**< program counter */
    int counterLimit; /**< counter limit */
public:
    /**
     * @brief constructor
     * @param cMax counter max
     * @param amp amplitude of sine wave
     * @param sMax state max
     * @param p period
     * @param pS period step
     */
    CaterpillarBehavior(int cMax, float amp, int sMax, int p, int pS);
    /**
     * @brief constructor
     * @param startState starting state for behavior
     */
    CaterpillarBehavior(int startState);
    /**
     * @brief destructor
     */
    virtual ~CaterpillarBehavior();
    /**
     * @brief step function
     * @param jointVals sensor values
     * @param desiredVals desired values
     * @param tolerances tolerances in sensor values
     * @return action values
     */
    virtual void Tick(ModuleModel model);
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
