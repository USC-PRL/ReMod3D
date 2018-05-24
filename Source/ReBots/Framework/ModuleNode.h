#pragma once
#include <vector>
#include <utility>
#include "Framework/ModuleDock.h"
#include "Framework/ModuleDockFace.h"
using namespace std;
class AModularRobot;
/**
 * @class ModuleNode
 * @brief superbot module node
 */
class REBOTS_API ModuleNode {
private:
    int NodeName; /**< name of node */
	AModularRobot* ModuleRef; /**< reference to superbot module */
    int CurrentPathElement; /**< current path element */
    std::vector<float> JointAngles; /**< vector of state values */
    int CurrentDock; /**< current dock */
    FTransform Transform; /**< module transform in reference frame */
    std::vector<std::pair<ModuleDockFace, int> > DockFacePathToNode; /**< path of dock faces to this node */
    std::vector<int> ModulePathToNode; /**< names of modules on the way to node */
    int DiscoveredLevel; /**< discovered level */
    int DiscoveredDock; /**< discovered dock */
    bool DockFacePathSet; /**< dock face path set */
    bool ConnectedToGround; /**< is dock connected to ground */
    bool AmIEndEffector; /**< am i an end effector */
	bool AmIConnectedToObject; /**< am i connected to an object*/
    std::vector<bool> DockStatuses; /**< dock engaged status */
    ModuleNode* DiscoveringNode; /**< node that discovered this node */
    ModuleDockFace DockFaceConnectedToGround; /**< dock face connected to ground */
public:
    /**
     * @brief default constructor
     */
    ModuleNode();
    /**
     * @brief constructor with arguments
     * @param s state vector
     * @param f is in free space
     * @param n name
     */
    ModuleNode(std::vector<float>& j, int n, FTransform t);
	/**
	* @brief set module reference
	* @param Ref module reference
	*/
	void SetModuleReference(AModularRobot* Ref);
	/**
	* @brief get module reference
	* @return Ref module reference
	*/
	AModularRobot* GetModuleReference();
    /**
     * @brief set discovering node
     * @return n discovering node
     */
    void SetDiscoveringNode(ModuleNode* n);
    /**
     * @brief set dock face connected to ground
     * @param D dock face
     */
    void SetDockFaceConnectedToGround(ModuleDockFace D);
    /**
     * @brief set dock engaged statuses
     * @param DE dock engaged statuses
     */
    void SetDockEngagedStatuses(std::vector<bool> DE);
    /**
     * @brief get dock engaged statuses
     * @return dock engaged statuses
     */
    std::vector<bool> GetDockEngagedStatuses();
    /**
     * @brief get dock face connected to ground
     * @return return dock face connected to ground
     */
    ModuleDockFace GetDockFaceConnectedToGround();
    /**
     * @brief get discovering node
     * @return discovering node
     */
    ModuleNode* GetDiscoveringNode();
	/**
	* @brief set am i connected to object
	* @param bool amc
	*/
	void SetAmIConnectedToObject(bool amc);
	/**
	* @brief get am i connected to object
	* @return am i connected to object
	*/
	bool GetAmIConnectedToObject();
    /**
     * @brief set am i end effector
     * @param ame whether or not am an end effector
     */
    void SetAmIEndEffector(bool ame);
    /**
     * @brief get am i end effector
     * @return whether or not am an end effector
     */
    bool GetAmIEndEffector();
    /**
     * @brief set connected to ground
     * @param c connected to ground?
     */
    void SetConnectedToGround(bool c);
    /**
     * @brief get connected to ground
     * @return connected to ground?
     */
    bool GetConnectedToGround();
    /**
     * @brief set current path element
     * @param i path element
     */
    void SetCurrentPathElement(int i);
    /**
     * @brief get current path element
     * @return current path element
     */
    int GetCurrentPathElement();
    /**
     * @brief set discovered dock
     * @param d discovered dock
     */
    void SetDiscoveredDock(int d);
    /**
     * @brief get discovered dock
     * @return discovered dock
     */
    int GetDiscoveredDock();
    /**
     * @brief set path set
     * @param d dock face path set or not
     */
    void SetPathSet(bool d);
    /**
     * @brief set path set
     * @return dock face path set or not
     */
    bool GetPathSet();
    /**
     * @brief set discovered level
     * @param l level
     */
    void SetDiscoveredLevel(int l);
    /**
     * @brief get discovered level
     * @return discovered level
     */
    int GetDiscoveredLevel();
    /**
     * @brief set current dock
     * @param d dock
     */
    void SetCurrentDock(int d);
    /**
     * @brief get current dock
     * @return dock
     */
    int GetCurrentDock();
    /**
     * @brief increment current dock
     */
    void IncrementCurrentDock();
    /**
     * @brief set dock face path
     * @param dpath dock face path
     */
    void SetDockFacePath(std::vector<std::pair<ModuleDockFace, int> > dpath);
    /**
     * @brief get dock face path
     * @return dock face path
     */
    std::vector<std::pair<ModuleDockFace, int> > GetDockFacePath();
    /**
     * @brief get module path
     * @return module path
     */
    std::vector<int> GetModulePath();
    /**
     * @brief add face to dock face path
     * @param d dock face
     */
    void AddFaceToDockFacePath(std::pair<ModuleDockFace, int> d);
    /**
     * @brief add face to dock face path
     * @param d dock face
     */
    void AddModuleToModulePath(int d);
    /**
     * @brief setter for state
     * @param s state vector
     */
    void SetJointAngles(const std::vector<float>& j);
    /**
     * @brief setter for name
     * @param n name
     */
    void SetName(const int n);
    /**
     * @brief set transform of module
     * @param t transform
     */
    void SetTransform(FTransform t);
    /**
     * @brief get transform
     * @return transform of module
     */
    FTransform GetTransform();
    /**
     * @brief getter for state
     * @return state values
     */
    std::vector<float>& GetJointAngles();
    /**
     * @brief getter for name
     * @return name
     */
    int GetName();
};
