#pragma once
#include <iostream>
#include <vector>
#include "Framework/ModuleDock.h"
using namespace std;
/**
 * @class KinematicNode
 * @brief node in a kinematic data structure
 */
class REBOTS_API KinematicNode {
private:
    int Name; /**< name of module */
    FTransform Trans; /**< transform of module */
    std::vector<float> Angles; /**< module angles */
public:
    /**
     * @brief get module name
     * @return module name
     */
    int GetName();
    /**
     * @brief get module transform
     * @return module transform
     */
    FTransform GetModuleTransform();
    /**
     * @brief get angles
     * @return angles
     */
    std::vector<float> GetAngles();
    /**
     * @brief set name
     * @param name name of node
     */
    void SetName(int name);
    /**
     * @brief set name
     * @param name name of node
     */
    void SetModuleTransfrom(FTransform t);
    /**
     * @brief set angles
     * @param a module angles
     */
    void SetAngles(std::vector<float> a);
    /**
     * @brief constructor
     */
    KinematicNode();
    /**
     * @brief constructor
     * @param name name of module
     * @param trans transform of module
     * @param angles module angles
     */
    KinematicNode(int name, FTransform trans, std::vector<float> angles);
};
