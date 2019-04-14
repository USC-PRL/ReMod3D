// Fill out your copyright notice in the Description page of Project Settings.

 
#include "GoToAnglesBehavior.h"
#include <math.h>

/**
 * @brief constructor
 * @param dj desired joints
 */
GoToAnglesBehavior::GoToAnglesBehavior(std::vector<float> dj){
    desJoints = dj;
}
/**
 * @brief destructor
 */
GoToAnglesBehavior::~GoToAnglesBehavior(){}
/**
 * @brief step function of behavior
 * @param sensorVals superbot sensor values
 * @param desiredVals desired sensor values
 * @param tolerances tolerances in sensor error
 * @return action values
 */
std::vector<float> GoToAnglesBehavior::Tick(std::vector<float> sensorVals, std::vector<float> desiredVals,
                                       std::vector<float> tolerances) {
    std::vector<float> returnVals(sensorVals.size());
    for (int i=0; i<sensorVals.size(); i++) {
        returnVals[i] = desJoints[i];
    }
    return returnVals;
}
/**
 * @brief are current joint angles close to desired ones
 * @param sensorVals sensor values
 * @param desiredVals desired sensor values
 * @param tolerances tolerances
 * @return true if desired and current angles "same", false otherwise.
 */
bool GoToAnglesBehavior::areCurrentSensorsDesired(std::vector<float> sensorVals, std::vector<float> desiredVals,
                                             std::vector<float> tolerances) {
    for (int i=0; i<sensorVals.size(); i++) {
        if (fabs(sensorVals[i] - desiredVals[i]) > tolerances[i]) {
            return false;
        }
    }
    return true;
}
