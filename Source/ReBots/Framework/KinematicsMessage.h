#pragma once
#include <vector>
#include <stack>
#include "Framework/RobotMessage.h"
#include "Framework/ModuleDockFace.h"
#include "Framework/ModuleDock.h"
#include "Framework/ModuleMotorVector.h"
using namespace std;
/**
 * @class KinematicsMessage
 * @brief message of kinematic data
 */
class REBOTS_API KinematicsMessage: public RobotMessage {
public:
    std::string Command; /**< message command */
    int CurrentMCV; /**< current motor command vector */
    int LifeTime; /**< message life time */
    std::vector<ModuleMotorVector> MV; /**< motor command vector */
    std::stack<ModuleDockFace> DockFaceStackToSource; /**< path of dock faces back to source */
    std::vector<ModuleDockFace> DockFacePath; /**< path of dock faces */
    bool ForwardDirection; /**< message in forward direction? */
    bool HasReturnedToSource; /**< has returned to source */
    ModuleDockFace StartingDock; /**< starting dock of message */
    ModuleDock sendingDock; /**< sending dock */
    ModuleDock receivingDock; /**< receiving dock */
    /**
     * @brief constructor
     */
    KinematicsMessage();
    /**
     * @brief constructor
     * @param c string message
     */
    KinematicsMessage(std::string c);
    /**
     * @brief constructor
     * @param c string message
     * @param sendingDock sending dock of message
     * @param receivingDock receiving dock of message
     */
    KinematicsMessage(std::string c, ModuleDock sendingDock, ModuleDock receivingDock);
    /**
     * @brief set sending dock
     * @param sDock sending dock
     */
    void SetSendingDock(ModuleDock sDock);
    /**
     * @brief set receiving dock
     * @param rDock receiving dock
     */
    void SetReceivingDock(ModuleDock rDock);
    /**
     * @brief get sending dock
     * @return sending dock
     */
    ModuleDock GetSendingDock();
    /**
     * @brief get receiving dock
     * @return receiving dock
     */
    ModuleDock GetReceivingDock();
};
