 
#include "TreeMessage.h"
/**
 * @brief constructor
 */
TreeMessage::TreeMessage() {
    this->Command = "";
    this->CurrentPathElement = 0;
    this->CurrentDock = 0;
    this->NumTreeNodes = 0;
}
/**
 * @brief constructor
 */
TreeMessage::TreeMessage(std::string c, int NTN, int NNID) {
    this->Command = c;
    this->CurrentPathElement = 0;
    this->CurrentDock = 0;
    this->NumTreeNodes = NTN;
    this->NeighborNumID = NNID;
}
/**
 * @brief set neighbor number id
 * @param NNID neighbor id
 */
void TreeMessage::SetNeighborNumID(int NNID) {
    this->NeighborNumID = NNID;
}
/**
 * @brief get neighbor num id
 * @return neighbor num id
 */
int TreeMessage::GetNeighborNumID() {
    return this->NeighborNumID;
}
/**
 * @brief set tree node size
 * @param ntn number of tree nodes
 */
void TreeMessage::SetNumTreeNodes(int NTN) {
    this->NumTreeNodes = NTN;
}
/**
 * @brief get tree node size
 * @return number of tree nodes
 */
int TreeMessage::GetNumTreeNodes() {
    return this->NumTreeNodes;
}
/**
 * @brief set sending dock
 * @param sDock sending dock
 */
void TreeMessage::SetSendingDock(ModuleDock sDock) {
    this->sendingDock = sDock;
}
/**
 * @brief set receiving dock
 * @param rDock receiving dock
 */
void TreeMessage::SetReceivingDock(ModuleDock rDock) {
    this->receivingDock = rDock;
}
/**
 * @brief get sending dock
 * @return sending dock
 */
ModuleDock TreeMessage::GetSendingDock() {
    return this->sendingDock;
}
/**
 * @brief get receiving dock
 * @return receiving dock
 */
ModuleDock TreeMessage::GetReceivingDock() {
    return this->receivingDock;
}
