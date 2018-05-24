 
#include "CaterpillarBehavior.h"
/**
 * @brief constructor
 * @param cMax counter max
 * @param amp amplitude of sine wave
 * @param sMax state max
 * @param p period
 * @param pS period step
 */
CaterpillarBehavior::CaterpillarBehavior(int cMax, float amp, int sMax, int p, int pS) {
    this->counterLimit = cMax;
    this->programCounter = 0;
    this->stateMax = sMax;
    this->stateCounter = 0;
    this->hasReceivedMessageFromInBack = false;
    this->hasReceivedMessageFromInFront = false;
    this->hasSentMessageBack = false;
    this->hasSentMessageForward = false;
    this->hasHeardGo = false;
    this->amplitude = amp;
    this->period = p;
    this->periodStep = pS;
    this->Name = "Caterpillar";
}
/**
 * @brief constructor
 * @param startState starting state of behavior
 */
CaterpillarBehavior::CaterpillarBehavior(int startState) {}
/**
 * @brief destructor
 */
CaterpillarBehavior::~CaterpillarBehavior() {}
/**
 * @brief step function
 * @param jointVals sensor values
 * @param desiredVals desired values
 * @param tolerances tolerances in sensor values
 * @return action values
 */
void CaterpillarBehavior::Tick(ModuleModel model) {
    ClearAllActions();
    ModuleModel desiredModel;
    if (this->programCounter == 0) {
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_P_GAIN_MOTOR_0, 40000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_P_GAIN_MOTOR_1, 40000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_P_GAIN_MOTOR_2, 40000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_D_GAIN_MOTOR_0, 10000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_D_GAIN_MOTOR_1, 10000.0));
        AddGainChangeAction(std::pair<ModuleAction,float>(CHANGE_D_GAIN_MOTOR_2, 10000.0));
    }
    std::vector<RangedMessage> rms = model.GetCurrentState().GetRangedMessages();
    std::vector<Message> ms = model.GetCurrentState().GetMessages();
    bool frontDockEngaged = model.GetCurrentState().GetDocksEngagedStatus()[DOCK_0];
    bool backDockEngaged = model.GetCurrentState().GetDocksEngagedStatus()[DOCK_1];
    if (!frontDockEngaged && this->programCounter > 0 && !hasSentMessageBack && backDockEngaged) {
        hasReceivedMessageFromInFront = true;
        this->hasSentMessageBack = true;
        this->hasSentMessageForward = true;
        this->stateCounter = 0;
        std::stringstream ss;
        ss << 1;
        AddMessageAction(std::pair<ModuleAction, std::string>(SEND_MESSAGE_BACK_DOCK,ss.str()));
    } else if (ms.size() > 0 && !hasReceivedMessageFromInFront && !hasSentMessageBack) {
        string data = ms[0].getMessageData();
        hasReceivedMessageFromInFront = true;
        hasSentMessageBack = true;
        int dataInt = atoi(data.c_str());
        this->stateCounter = (4*dataInt)%20;
        dataInt++;
        stringstream ss;
        ss<<dataInt;
        if (!backDockEngaged) {
            string message = "GO";
            hasHeardGo = true;
            //AddMessageAction(std::pair<ModuleAction,std::string>(SEND_RANGED_MESSAGE,message));
        } else {
            AddMessageAction(std::pair<ModuleAction, std::string>(SEND_MESSAGE_BACK_DOCK,ss.str()));
        }
    } else {
        if (rms.size() > 0 && !hasHeardGo) {
            string data = rms[0].getMessageData();
            if (data.compare("GO") == 0) {
                cout<<"GO"<<endl;
                hasHeardGo = true;
            } else {
                cout<<"Superbot Says: "<<data<<endl;
            }
        }
        if (hasReceivedMessageFromInFront &&
            hasSentMessageBack) {
            double motor_0_angle = (double)(this->amplitude*cosf(((double)((this->stateCounter)%this->stateMax))*PxPi/this->period));
            double motor_1_angle = (double) 0;
            double motor_2_angle = (double)(0+this->amplitude*cosf(((double)((this->stateCounter+this->periodStep)%this->stateMax))*PxPi/this->period));
            AddAngleAction(std::pair<ModuleAction,float>(SET_MOTOR_0,motor_0_angle));
            AddAngleAction(std::pair<ModuleAction,float>(SET_MOTOR_1,motor_1_angle));
            AddAngleAction(std::pair<ModuleAction,float>(SET_MOTOR_2,motor_2_angle));
            AddDelayAction(std::pair<ModuleAction,int>(DELAY_ACTION, 5));
            this->stateCounter++;
            if (this->stateCounter == this->stateMax - 1) {
                this->stateCounter = 0;
            }
        }
        
    }
    
    
    this->programCounter++;
}
/**
 * @brief are current joint angles close to desired ones
 * @param sensorVals sensor values
 * @param desiredVals desired sensor values
 * @param tolerances tolerances
 * @return true if desired and current angles "same", false otherwise.
 */
bool CaterpillarBehavior::areCurrentSensorsDesired(std::vector<float> sensorVals, std::vector<float> desiredVals,
                                             std::vector<float> tolerances) {
    for (int i=0; i<sensorVals.size(); i++) {
        if (fabs(sensorVals[i] - desiredVals[i]) > tolerances[i]) {
            return false;
        }
    }
    return true;
}
