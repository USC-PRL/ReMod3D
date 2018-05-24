 
#include "KinematicGraph.h"
/**
 * @brief kinematic tree constructor
 */
KinematicGraph::KinematicGraph() {}
/**
 * @brief get the edges
 * @return edges of tree
 */
std::map<std::pair<int,int>, KinematicEdge> KinematicGraph::GetEdges() {return this->Edges;}
/**
 * @brief get nodes
 * @return nodes of graph
 */
std::map<int,KinematicNode> KinematicGraph::GetNodes() {return this->Nodes;}
/**
 * @brief clear tree
 */
void KinematicGraph::ClearTree() {
    Nodes.clear();
    Edges.clear();
}
/**
 * @brief add an edge
 * @param edge edge to add
 */
void KinematicGraph::AddEdge(KinematicEdge e) {
    Edges[std::pair<int,int>(e.GetModule1(),e.GetModule2())] = e;
}
/**
 * @brief add edge
 * @param edgePair pair associated with edge
 * @param edgeTransform transform associated with edge
 */
void KinematicGraph::AddEdge(std::pair<int,int> edgePair, FTransform edgeTransform) {
    KinematicEdge e(edgePair.first, edgePair.second, edgeTransform);
    Edges[edgePair] = e;
}
/**
 * @brief add node
 * @param node kinematic node
 */
void KinematicGraph::AddNode(KinematicNode node) {
    Nodes[node.GetName()] = node;
}
/**
 * @brief add node
 * @param name name of module
 * @param trans transform of module
 * @param angs angles of module
 * @param sc scale of module
 */
void KinematicGraph::AddNode(int name, FTransform trans, std::vector<float> angs) {
    KinematicNode n(name,trans,angs);
    Nodes[name] = n;
}
/**
 * @brief update node
 * @param name node name
 * @param t transform
 * @param angs angles
 */
void KinematicGraph::UpdateNode(int name, FTransform t, std::vector<float> angs) {
    Nodes[name].SetAngles(angs);
    Nodes[name].SetModuleTransfrom(t);
}
