#pragma once
#include <vector>
#include "Framework/ModuleNode.h"
#include "Framework/ModuleDock.h"
#include "Framework/RobotMessage.h"
#include "Framework/ModuleMotorVector.h"
#include <stack>
/**
 * @enum TreeMessage
 * @brief superbot message
 */
class REBOTS_API TreeMessage : public RobotMessage {
public:
    std::string Command; /**< message command */
    std::vector<float> CommandAngles; /**< angles command */
    std::vector<bool> DockConnectedStatuses; /**< dock connected statuses */
    std::vector<ModuleMotorVector> MV; /**< motor command vector */
	bool TerminalIsEndEffector = false; /**< is the terminal point an end-effector*/
	bool TerminalIsGroundEffector = false; /**< is the terminal point attached to ground*/
    int NumTreeNodes; /**< number of tree nodes when message is sent */
    int NeighborNumID; /**< id of neighbor to which this message corresponds */
    ModuleNode *N; /**< node associated with message */
    FTransform Transform; /**< transform */
    std::vector<std::pair<ModuleDockFace, int> > DockFacePath; /**< path of dock faces */
    std::stack<ModuleDockFace> DockStack; /**< stack of dock faces */
    std::vector<int> ModulePathToNode; /**< module path to node */
	AModularRobot* SM1;
	AModularRobot* SM2;
	ModuleDockFace D1;
	ModuleDockFace D2;
    int CurrentPathElement; /**< current path element */
    int CurrentDock; /**< current dock */
    bool AmIEndEffector; /**< am i end effector */
    bool ConnectedToGround; /**< connected to ground */
	bool ConnectedToObject; /**< connected to object */
    ModuleDock sendingDock; /**< sending dock */
    ModuleDock receivingDock; /**< receiving dock */
	AModularRobot* ModuleRef; /**< module ref */
	float OffsetAngle;
	int ProgramMode;
	int CurrentOb;
    /**
     * @brief constructor
     */
    TreeMessage();
    /**
     * @brief constructor
     */
    TreeMessage(std::string c, int NTN, int NNID);
    /**
     * @brief set neighbor number id
     * @param NNID neighbor id
     */
    void SetNeighborNumID(int NNID);
    /**
     * @brief get neighbor num id
     * @return neighbor num id
     */
    int GetNeighborNumID();
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
     * @brief set tree node size
     * @param ntn number of tree nodes
     */
    void SetNumTreeNodes(int NTN);
    /**
     * @brief get tree node size
     * @return number of tree nodes
     */
    int GetNumTreeNodes();
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
