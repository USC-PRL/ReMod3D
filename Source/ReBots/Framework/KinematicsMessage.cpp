 
#include "KinematicsMessage.h"
/**
 * @brief constructor
 */
KinematicsMessage::KinematicsMessage() {
    this->Command = "";
    this->LifeTime = 0;
    this->CurrentMCV = 0;
    this->MV = vector<ModuleMotorVector>(0);
    this->ForwardDirection = true;
}
/**
 * @brief constructor
 * @param c string message
 */
KinematicsMessage::KinematicsMessage(std::string c) {
    this->Command = c;
    this->LifeTime = 0;
    this->CurrentMCV = 0;
    this->MV = vector<ModuleMotorVector>(0);
    this->ForwardDirection = true;
}
/**
 * @brief constructor
 * @param c string message
 * @param sendingDock sending dock of message
 * @param receivingDock receiving dock of message
 */
KinematicsMessage::KinematicsMessage(std::string c, ModuleDock sDock, ModuleDock rDock) {
    this->Command = c;
    this->LifeTime = 0;
    this->CurrentMCV = 0;
    this->MV = vector<ModuleMotorVector>(0);
    this->ForwardDirection = true;
    this->sendingDock = sDock;
    this->receivingDock = rDock;
    
}
/**
 * @brief set sending dock
 * @param sDock sending dock
 */
void KinematicsMessage::SetSendingDock(ModuleDock sDock) {
    this->sendingDock = sDock;
}
/**
 * @brief set receiving dock
 * @param rDock receiving dock
 */
void KinematicsMessage::SetReceivingDock(ModuleDock rDock) {
    this->receivingDock = rDock;
}
/**
 * @brief get sending dock
 * @return sending dock
 */
ModuleDock KinematicsMessage::GetSendingDock() {
    return this->sendingDock;
}
/**
 * @brief get receiving dock
 * @return receiving dock
 */
ModuleDock KinematicsMessage::GetReceivingDock() {
    return this->receivingDock;
}
