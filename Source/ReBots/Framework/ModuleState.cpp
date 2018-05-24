 
#include "ModuleState.h"
/**
 * @brief set id number
 */
void ModuleState::SetIDNumber(int idn) {
    this->IDNumber = idn;
}
/**
 * @brief get id number
 */
int ModuleState::GetIDNumber() {
    return this->IDNumber;
}
/**
 * @brief set messages
 * @param m messages
 */
void ModuleState::SetMessages(std::vector<Message> m) {
    this->messages = m;
}
/**
 * @brief set messages
 * @param rm messages
 */
void ModuleState::SetRangedMessages(std::vector<RangedMessage> rm) {
    this->rangedMessages = rm;
}
/**
 * @brief get tree messages
 * @return get tree messages
 */
std::vector<TreeMessage> ModuleState::GetTreeMessages() {
    return this->treeMessages;
}
/**
 * @brief get ranged messages
 * @return ranged  messages
 */
std::vector<KinematicsMessage> ModuleState::GetKinematicsMessages() {
    return this->kinematicsMessages;
}
/**
 * @brief set messages
 * @param rm messages
 */
void ModuleState::SetKinematicsMessages(std::vector<KinematicsMessage> kms) {
    this->kinematicsMessages = kms;
}
/**
 * @brief set tree messages
 * @param tms tree messages
 */
void ModuleState::SetTreeMessages(std::vector<TreeMessage> tms) {
    this->treeMessages = tms;
}
/**
 * @brief get messages
 * @return messages
 */
std::vector<Message> ModuleState::GetMessages() {
    return this->messages;
}
/**
 * @brief get ranged messages
 * @return ranged  messages
 */
std::vector<RangedMessage> ModuleState::GetRangedMessages() {
    return this->rangedMessages;
}
/**
 * @brief set joint angles
 * @param mv motor angles
 */
void ModuleState::SetJointAngles(ModuleMotorVector mv) {
    this->smv = mv;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
void ModuleState::SetDocksEnabledStatus(std::vector<bool> docksEna) {
    this->DocksEnabledStatus = docksEna;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
void ModuleState::SetDocksEngagedStatus(std::vector<bool> docksEng) {
    this->DocksEngagedStatus = docksEng;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
void ModuleState::SetDocksEnabledToGroundStatus(std::vector<bool> docksEna) {
    this->DocksEnabledToGroundStatus = docksEna;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
void ModuleState::SetDocksEngagedToGroundStatus(std::vector<bool> docksEng) {
    this->DocksEngagedToGroundStatus = docksEng;
}
/**
* @brief set docks enabled
* @param docksEna docks enabled
*/
void ModuleState::SetDocksEnabledToObjectStatus(std::vector<bool> docksEna) {
	this->DocksEnabledToObjectStatus = docksEna;
}
/**
* @brief set docks enabled
* @param docksEna docks enabled
*/
void ModuleState::SetDocksEngagedToObjectStatus(std::vector<bool> docksEng) {
	this->DocksEngagedToObjectStatus = docksEng;
}
/**
 
 * @brief set joint angles
 * @param mv motor angles
 */
ModuleMotorVector ModuleState::GetJointAngles() {
    return this->smv;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
std::vector<bool> ModuleState::GetDocksEnabledStatus() {
    return this->DocksEnabledStatus;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
std::vector<bool> ModuleState::GetDocksEngagedStatus() {
    return this->DocksEngagedStatus;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
std::vector<bool> ModuleState::GetDocksEnabledToGroundStatus() {
    return this->DocksEnabledToGroundStatus;
}
/**
 * @brief set docks enabled
 * @param docksEna docks enabled
 */
std::vector<bool> ModuleState::GetDocksEngagedToGroundStatus() {
    return this->DocksEngagedToGroundStatus;
}
/**
* @brief set docks enabled
* @param docksEna docks enabled
*/
std::vector<bool> ModuleState::GetDocksEnabledToObjectStatus() {
	return this->DocksEnabledToObjectStatus;
}
/**
* @brief set docks enabled
* @param docksEna docks enabled
*/
std::vector<bool> ModuleState::GetDocksEngagedToObjectStatus() {
	return this->DocksEngagedToObjectStatus;
}
/**
 * @brief constructor
 */
ModuleState::ModuleState(){}
