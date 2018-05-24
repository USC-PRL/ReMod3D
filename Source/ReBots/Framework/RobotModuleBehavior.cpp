 
#include "RobotModuleBehavior.h"
/**
 * @brief clear all actions
 */
void RobotModuleBehavior::ClearAllActions() {
    MessageActions.clear();
    AngleActions.clear();
    DockActions.clear();
    KinematicsMessageActions.clear();
    TreeMessageActions.clear();
    GainChangeActions.clear();
    DelayActions.clear();
	ConnectionActions.clear();
}
/**
 * @brief add angle action
 */
void RobotModuleBehavior::AddAngleAction(std::pair<ModuleAction,float> action) {
    AngleActions.push_back(action);
}
/**
 * @brief add dock action
 */
void RobotModuleBehavior::AddDockAction(std::pair<ModuleAction,bool> action) {
    DockActions.push_back(action);
}
/**
 * @brief add dock action
 */
void RobotModuleBehavior::AddMessageAction(std::pair<ModuleAction,std::string> action) {
    MessageActions.push_back(action);
}
/**
 * @brief add delay action
 */
void RobotModuleBehavior::AddDelayAction(std::pair<ModuleAction, int> action) {
    DelayActions.push_back(action);
}
/**
 * @brief add dock action
 * @param action action to add
 */
void RobotModuleBehavior::AddKinematicsMessageAction(std::pair<ModuleAction,KinematicsMessage> action) {
    KinematicsMessageActions.push_back(action);
}
/**
 * @brief add dock action
 */
void RobotModuleBehavior::AddTreeMessageAction(std::pair<ModuleAction,TreeMessage> action) {
    TreeMessageActions.push_back(action);
}
/**
 * @brief add gain change action
 */
void RobotModuleBehavior::AddGainChangeAction(std::pair<ModuleAction,float> action) {
    GainChangeActions.push_back(action);
}
/**
* @brief add connection message
*/
void RobotModuleBehavior::AddConnectionAction(std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> > action) {
	ConnectionActions.push_back(action);
}

/**
 * @brief get kinematics message actions
 * @return kinematics message actions
 */
std::vector<std::pair<ModuleAction, KinematicsMessage> > RobotModuleBehavior::GetKinematicsMessageActions() {
    return this->KinematicsMessageActions;
}
/**
 * @brief get delay actions
 */
std::vector<std::pair<ModuleAction,int> > RobotModuleBehavior::GetDelayActions() {
    return this->DelayActions;
}
/**
 * @brief get angle actions
 * @return angle actions
 */
std::vector<std::pair<ModuleAction, float> > RobotModuleBehavior::GetAngleActions() {
    return this->AngleActions;
}
/**
 * @brief get dock actions
 * @return dock actions
 */
std::vector<std::pair<ModuleAction, bool> > RobotModuleBehavior::GetDockActions() {
    return this->DockActions;
}
/**
* @brief get connection actions
* @return connection actions
*/
std::vector < std::pair<ModuleAction, std::pair<ModuleConnectionPair, bool> > > RobotModuleBehavior::GetConnectionActions() {
	return this->ConnectionActions;
}
/**
 * @brief get message actions
 * @return message actions
 */
std::vector<std::pair<ModuleAction, std::string> > RobotModuleBehavior::GetMessageActions() {
    return this->MessageActions;
}
/**
 * @brief get kinematics message actions
 * @return kinematics message actions
 */
std::vector<std::pair<ModuleAction, TreeMessage> > RobotModuleBehavior::GetTreeMessageActions() {
    return this->TreeMessageActions;
}
/**
 * @brief get gain change actions
 * @return gain change actions
 */
std::vector<std::pair<ModuleAction, float> > RobotModuleBehavior::GetGainChangeActions() {
    return this->GainChangeActions;
}
/**
 * @brief get name of behavior
 * @return name
 */
std::string RobotModuleBehavior::GetName() {
    return this->Name;
}
/**
 * @brief set behavior name
 */
void RobotModuleBehavior::SetName(std::string n) {
    this->Name = n;
}
/**
 * @brief constructor
 */
RobotModuleBehavior::RobotModuleBehavior(){}
/**
 * @brief destructor
 */
RobotModuleBehavior::~RobotModuleBehavior(){}

