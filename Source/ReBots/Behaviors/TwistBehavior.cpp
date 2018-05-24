 
#include "TwistBehavior.h"
/**
 * @brief constructor
 */
TwistBehavior::TwistBehavior(){this->TwistAngle = 45.0; this->Name = "Twist";}
/**
 * @brief constructor
 */
TwistBehavior::TwistBehavior(float tAngle){this->TwistAngle = tAngle;}
/**
 * @brief destructor
 */
TwistBehavior::~TwistBehavior(){}
/**
 * @brief step function of behavior
 * @param sensorVals superbot sensor values
 * @param desiredVals desired sensor values
 * @param tolerances tolerances in sensor error
 * @return action values
 */
void TwistBehavior::Tick(ModuleModel model) {
    ClearAllActions();
    if (this->ProgramCounter == 0) {
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_P_GAIN_MOTOR_0, 40000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_P_GAIN_MOTOR_1, 40000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_P_GAIN_MOTOR_2, 40000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_D_GAIN_MOTOR_0, 10000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_D_GAIN_MOTOR_1, 10000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_D_GAIN_MOTOR_2, 10000.0));
    }
    AddAngleAction(std::pair<ModuleAction,float>(SET_MOTOR_0, TwistAngle));
    AddAngleAction(std::pair<ModuleAction,float>(SET_MOTOR_1, TwistAngle));
    AddAngleAction(std::pair<ModuleAction,float>(SET_MOTOR_2, TwistAngle));
    AddDelayAction(std::pair<ModuleAction,int>(DELAY_ACTION, 100));
    TwistAngle = -TwistAngle;
    this->ProgramCounter++;
}
