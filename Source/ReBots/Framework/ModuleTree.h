#pragma once
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include "Framework/ModuleNode.h"
#include "Framework/ModuleEdge.h"
using namespace std;
/**
 * @class ModuleTree
 * @brief Class representing a tree for path planning
 * @author Thomas Collins
 * @version 1.0
 * @date 04/11/2015
 * Contact: collinst@usc.edu
 * Created on: 04/11/2015
 */
class REBOTS_API ModuleTree {
private:
    std::map<int,ModuleNode*> Vertices; /**< vertices of tree */
    std::vector<ModuleEdge> Edges; /**< edges of tree */
    std::map<int,ModuleNode*> NodeNameMap; /**< map of node names to nodes */
    std::queue<ModuleNode*> BfsQueue; /**< queue for tree discovery */
    FVector CenterOfMassPoint; /**< center of mass point */
    FVector CenterOfMassTotal; /**< center of mass total */
    bool TreeIsDirty; /**< tree is dirty and needs to be rebuilt? */
    FTransform TargetTransform; /**< target transform */
    std::vector<std::vector<float> > GoalAngles; /**< goal angles */
public:
    FTransform Frame0;
    FTransform Frame2;
    /**
     * @brief default constructor
     */
    ModuleTree();
    /**
     * @brief initialize tree with node
     * @param n node to initialize tree with
     */
    void InitializeTree(ModuleNode* n);
    /**
     * @brief set goal angles
     * @param ga goal angles
     */
    void SetGoalAngles(std::vector<std::vector<float> > ga);
    /**
     * @brief get goal angles
     * @return goal angles
     */
    std::vector<std::vector<float> > GetGoalAngles();
    /**
     * @brief set target transform
     * @param t target transform
     */
    void SetTarget(FTransform t);
    /**
     * @brief get target transform
     * @return target transform
     */
    FTransform GetTarget();
    /**
     * @brief set center of mass
     * @param com center of mass point
     */
    void SetCenterOfMass(FVector com);
    /**
     * @brief get center of mass point
     * @return center of mass
     */
    FVector GetCenterOfMass();
    /**
     * @brief reset center of mass total
     */
    void ResetCenterOfMassTotal();
    /**
     * @brief set center of mass
     * @param com center of mass point
     */
    void AddCenterOfMassTotal(FVector com);
    /**
     * @brief get center of mass point
     * @return center of mass
     */
    FVector GetCenterOfMassTotal();
    /**
     * @brief add vertex to tree
     * @param n node (vertex)
     */
    void AddVertex(ModuleNode* n);
    /**
     * @brief set tree dirty state
     * @param dirty whether or not (true/false) tree is dirty
     */
    void SetTreeDirtyState(bool dirty);
    /**
     * @brief get tree dirty state
     * @return tree is dirty or not
     */
    bool GetTreeDirtyState();
    /**
     * @brief add edge to tree
     * @param n1 node 1
     * @param n2 node 2
     */
    void AddEdge(const int n1, const int n2, ModuleDockFace d1, ModuleDockFace d2);
    /**
     * @brief clear vertices and edges
     */
    void ClearVerticesAndEdges();
    /**
     * @brief get queue front
     * @return front of queue
     */
    ModuleNode* GetQueueFront();
    /**
     * @brief get queue size
     * @return queue size
     */
    int GetQueueSize();
    /**
     * @brief add node to bfs queue
     * @parman smn node
     */
    void AddNodeToBFSQueue(ModuleNode* smn);
    /**
     * @brief pop bfs queue
     */
    void PopBFSQueue();
    /**
     * @brief getter for vertices
     * @return vertices of tree
     */
    std::map<int,ModuleNode*>& GetVertices();
    /**
     * @brief getter for edges
     * @return edges of tree
     */
    std::vector<ModuleEdge>& GetEdges();
    /**
     * @brief retrieve the node with the given name
     * @param i name of node
     * @return node with given name
     */
    ModuleNode* GetNodeForName(const int i);
};
