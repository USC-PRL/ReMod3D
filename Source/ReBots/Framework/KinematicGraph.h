#pragma once
#include <iostream>
#include <map>
#include <utility>
#include "KinematicNode.h"
#include "KinematicEdge.h"
#include <vector>

using namespace std;
/**
 * @class KinematicGraph
 * @brief graph of kinematic data
 */
class REBOTS_API KinematicGraph {
private:
    std::map<int,KinematicNode> Nodes; /**< nodes of kinematic tree */
    std::map<std::pair<int,int>, KinematicEdge> Edges; /**< edges of kinematic tree */
public:
    /**
     * @brief clear tree
     */
    void ClearTree();
    /**
     * @brief kinematic tree constructor
     */
    KinematicGraph();
    /**
     * @brief get the edges
     * @return edges of tree
     */
    std::map<std::pair<int,int>, KinematicEdge> GetEdges();
    /**
     * @brief get nodes
     * @return nodes of graph
     */
    std::map<int,KinematicNode> GetNodes();
    /**
     * @brief add an edge
     * @param edge edge to add
     */
    void AddEdge(KinematicEdge e);
    /**
     * @brief add edge
     * @param edgePair pair associated with edge
     * @param edgeTransform transform associated with edge
     */
    void AddEdge(std::pair<int,int> edgePair, FTransform edgeTransform);
    /**
     * @brief add node
     * @param node kinematic node
     */
    void AddNode(KinematicNode node);
    /**
     * @brief add node
     * @param name name of module
     * @param trans transform of module
     * @param angs angles of module
     * @param sc scale of module
     */
    void AddNode(int name, FTransform trans, std::vector<float> angs);
    /**
     * @brief update node
     * @param name node name
     * @param t transform
     * @param angs angles
     */
    void UpdateNode(int name, FTransform t, std::vector<float> angs);
};
