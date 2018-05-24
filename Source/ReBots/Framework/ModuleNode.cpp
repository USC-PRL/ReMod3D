 
#include "ModuleNode.h"
/**
 * @brief default constructor
 */
ModuleNode::ModuleNode() {
    this->NodeName = -1;
    this->Transform = FTransform(FVector(0,0,0));
    this->CurrentDock = 0;
    this->DiscoveredLevel = 0;
    this->DockFacePathSet = false;
    this->DiscoveredDock = -1;
    this->CurrentPathElement = 0;
    this->ConnectedToGround = false;
	this->AmIConnectedToObject = false;
    this->DiscoveringNode = NULL;
};
/**
 * @brief constructor with arguments
 * @param s state vector
 * @param f is in free space
 * @param n name
 */
ModuleNode::ModuleNode(std::vector<float>& j, int n, FTransform t) {
    this->JointAngles = j;
    this->NodeName = n;
    this->Transform = t;
    this->CurrentDock = 0;
    this->DiscoveredLevel = 0;
    this->DockFacePathSet = false;
    this->DiscoveredDock = -1;
    this->CurrentPathElement = 0;
    this->ConnectedToGround = false;
	this->AmIConnectedToObject = false;
    this->DiscoveringNode = NULL;
}
/**
* @brief set module reference
* @param Ref module reference
*/
void ModuleNode::SetModuleReference(AModularRobot* Ref) {
	this->ModuleRef = Ref;
}
/**
* @brief get module reference
* @return Ref module reference
*/
AModularRobot* ModuleNode::GetModuleReference() {
	return this->ModuleRef;
}
/**
 * @brief set dock face connected to ground
 * @param D dock face
 */
void ModuleNode::SetDockFaceConnectedToGround(ModuleDockFace D) {
    this->DockFaceConnectedToGround = D;
}
/**
 * @brief get dock face connected to ground
 * @return return dock face connected to ground
 */
ModuleDockFace ModuleNode::GetDockFaceConnectedToGround() {
    if (this->ConnectedToGround) {
        return this->DockFaceConnectedToGround;
    } else {
        return DOCK_6;
    }
}
/**
 * @brief set discovering node
 * @return n discovering node
 */
void ModuleNode::SetDiscoveringNode(ModuleNode* n) {
    this->DiscoveringNode = n;
}
/**
 * @brief get module path
 * @return module path
 */
std::vector<int> ModuleNode::GetModulePath() {
    return this->ModulePathToNode;
}
/**
 * @brief get discovering node
 * @return discovering node
 */
ModuleNode* ModuleNode::GetDiscoveringNode() {
    return this->DiscoveringNode;
}
/**
* @brief set am i connected to object
* @param bool amc
*/
void ModuleNode::SetAmIConnectedToObject(bool amc) {
	this->AmIConnectedToObject = amc;
}
/**
* @brief get am i connected to object
* @return am i connected to object
*/
bool ModuleNode::GetAmIConnectedToObject() {
	return this->AmIConnectedToObject;
}
/**
 * @brief set am i end effector
 * @param ame whether or not am an end effector
 */
void ModuleNode::SetAmIEndEffector(bool ame) {
    this->AmIEndEffector = ame;
}
/**
 * @brief get am i end effector
 * @return whether or not am an end effector
 */
bool ModuleNode::GetAmIEndEffector() {
    return this->AmIEndEffector;
}
/**
 * @brief set connected to ground
 * @param c connected to ground?
 */
void ModuleNode::SetConnectedToGround(bool c) {
    this->ConnectedToGround = c;
}
/**
 * @brief get connected to ground
 * @return connected to ground?
 */
bool ModuleNode::GetConnectedToGround() {
    return this->ConnectedToGround;
}
/**
 * @brief set current path element
 * @param i path element
 */
void ModuleNode::SetCurrentPathElement(int i) {
    this->CurrentPathElement = i;
}
/**
 * @brief get current path element
 * @return current path element
 */
int ModuleNode::GetCurrentPathElement() {
    return this->CurrentPathElement;
}
/**
 * @brief set discovered dock
 * @param d discovered dock
 */
void ModuleNode::SetDiscoveredDock(int d) {
    this->DiscoveredDock = d;
}
/**
 * @brief get discovered dock
 * @return discovered dock
 */
int ModuleNode::GetDiscoveredDock() {
    return this->DiscoveredDock;
}
/**
 * @brief set path set
 * @param d dock face path set or not
 */
void ModuleNode::SetPathSet(bool d) {
    this->DockFacePathSet = d;
}
/**
 * @brief add face to dock face path
 * @param d dock face
 */
void ModuleNode::AddModuleToModulePath(int d) {
    this->ModulePathToNode.push_back(d);
}
/**
 * @brief set path set
 * @return dock face path set or not
 */
bool ModuleNode::GetPathSet() {
    return this->DockFacePathSet;
}
/**
 * @brief set discovered level
 * @param l level
 */
void ModuleNode::SetDiscoveredLevel(int l) {
    this->DiscoveredLevel = l;
}
/**
 * @brief get discovered level
 * @return discovered level
 */
int ModuleNode::GetDiscoveredLevel() {
    return this->DiscoveredLevel;
}
/**
 * @brief set current dock
 * @param d dock
 */
void ModuleNode::SetCurrentDock(int d) {
    this->CurrentDock = d;
}
/**
 * @brief get current dock
 * @return dock
 */
int ModuleNode::GetCurrentDock() {
    return CurrentDock;
}
/**
 * @brief increment current dock
 */
void ModuleNode::IncrementCurrentDock() {
    this->CurrentDock = this->CurrentDock + 1;
}
/**
 * @brief set dock face path
 * @param dpath dock face path
 */
void ModuleNode::SetDockFacePath(std::vector<std::pair<ModuleDockFace, int> > dpath) {
    this->DockFacePathToNode = dpath;
}
/**
 * @brief get dock face path
 * @return dock face path
 */
std::vector<std::pair<ModuleDockFace, int> > ModuleNode::GetDockFacePath() {
    return this->DockFacePathToNode;
}
/**
 * @brief add face to dock face path
 * @param d dock face
 */
void ModuleNode::AddFaceToDockFacePath(std::pair<ModuleDockFace, int> d) {
    DockFacePathToNode.push_back(d);
}
/**
 * @brief setter for state
 * @param s state vector
 */
void ModuleNode::SetJointAngles(const std::vector<float>& j) {
    this->JointAngles = j;
}
/**
 * @brief setter for name
 * @param n name
 */
void ModuleNode::SetName(const int n) {
    this->NodeName = n;
}
/**
 * @brief set transform of module
 * @param t transform
 */
void ModuleNode::SetTransform(FTransform t) {
    this->Transform = t;
}
/**
 * @brief set dock engaged statuses
 * @param DE dock engaged statuses
 */
void ModuleNode::SetDockEngagedStatuses(std::vector<bool> DE) {
    this->DockStatuses = DE;
}
/**
 * @brief get dock engaged statuses
 * @return dock engaged statuses
 */
std::vector<bool> ModuleNode::GetDockEngagedStatuses() {
    return this->DockStatuses;
}
/**
 * @brief get transform
 * @return transform of module
 */
FTransform ModuleNode::GetTransform() {
    return this->Transform;
}
/**
 * @brief getter for state
 * @return state values
 */
std::vector<float>& ModuleNode::GetJointAngles() {
    return this->JointAngles;
}
/**
 * @brief getter for name
 * @return name
 */
int ModuleNode::GetName() {
    return this->NodeName;
}
