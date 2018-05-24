#pragma once
#include <utility>
#include <vector>
#include "Framework/ModuleDock.h"
/**
 * @class ModuleEdge
 * @brief superbot module edge
 */
class REBOTS_API ModuleEdge {
private:
    std::pair<int,int> EdgePair; /**< edge pair */
    std::pair<ModuleDockFace,ModuleDockFace> DockFacePair; /**< dock face pair */
public:
    /**
     * @brief  constructor
     */
    ModuleEdge();
    /**
     * @brief constructor
     * @param n1 node 1 name
     * @param n2 node 2 name
     * @param d1 dock face 1
     * @param d2 dock face 2
     */
    ModuleEdge(int n1, int n2, ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief set edge pair
     * @param int n1 node 1 name
     * @param int n2 node 2 name
     */
    void SetEdgePair(int n1, int n2);
    /**
     * @brief get edge pair
     * @return edge pair
     */
    std::pair<int,int> GetEdgePair();
    /**
     * @brief set dock face pair
     * @param d1 dock 1
     * @param d2 dock 2
     */
    void SetDockFacePair(ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief get dock face pair
     * @return dock face pair
     */
    std::pair<ModuleDockFace,ModuleDockFace> GetDockFacePair();
};
