 
#include "ModuleEdge.h"
/**
 * @brief  constructor
 */
ModuleEdge::ModuleEdge() {
    EdgePair = std::pair<int,int>(-1,-1);
    DockFacePair = std::pair<ModuleDockFace,ModuleDockFace>(DOCK_0,DOCK_0);
}
/**
 * @brief constructor
 * @param n1 node 1 name
 * @param n2 node 2 name
 * @param d1 dock face 1
 * @param d2 dock face 2
 */
ModuleEdge::ModuleEdge(int n1, int n2, ModuleDockFace d1, ModuleDockFace d2) {
    EdgePair = std::pair<int,int>(n1,n2);
    DockFacePair = std::pair<ModuleDockFace,ModuleDockFace>(d1,d2);
}
/**
 * @brief set edge pair
 * @param int n1 node 1 name
 * @param int n2 node 2 name
 */
void ModuleEdge::SetEdgePair(int n1, int n2) {
    EdgePair = std::pair<int,int>(n1,n2);
}
/**
 * @brief get edge pair
 * @return edge pair
 */
std::pair<int,int> ModuleEdge::GetEdgePair() {
    return this->EdgePair;
}
/**
 * @brief set dock face pair
 * @param d1 dock 1
 * @param d2 dock 2
 */
void ModuleEdge::SetDockFacePair(ModuleDockFace d1, ModuleDockFace d2) {
    this->DockFacePair = std::pair<ModuleDockFace,ModuleDockFace>(d1,d2);
}
/**
 * @brief get dock face pair
 * @return dock face pair
 */
std::pair<ModuleDockFace,ModuleDockFace> ModuleEdge::GetDockFacePair() {
    return this->DockFacePair;
}
