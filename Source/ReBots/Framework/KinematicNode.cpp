 
#include "KinematicNode.h"
/**
 * @brief get module name
 * @return module name
 */
int KinematicNode::GetName() {return this->Name;}
/**
 * @brief get module transform
 * @return module transform
 */
FTransform KinematicNode::GetModuleTransform() {return this->Trans;}
/**
 * @brief get angles
 * @return angles
 */
std::vector<float> KinematicNode::GetAngles() {return this->Angles;}
/**
 * @brief set name
 * @param name name of node
 */
void KinematicNode::SetName(int name) {this->Name = name;}
/**
 * @brief set name
 * @param name name of node
 */
void KinematicNode::SetModuleTransfrom(FTransform t) {this->Trans = t;}
/**
 * @brief set angles
 * @param a module angles
 */
void KinematicNode::SetAngles(std::vector<float> a) {this->Angles = a;}
/**
 * @brief constructor
 */
KinematicNode::KinematicNode() {}
/**
 * @brief constructor
 * @param name name of module
 * @param trans transform of module
 * @param angles module angles
 */
KinematicNode::KinematicNode(int name, FTransform trans, std::vector<float> angles) {
    this->Name = name;
    this->Trans = trans;
    this->Angles = angles;
}
