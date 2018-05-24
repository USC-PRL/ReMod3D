 
#include "ModuleTree.h"
/**
 * @brief default constructor
 */
ModuleTree::ModuleTree() {}
/**
 * @brief initialize tree with node
 * @param n node to initialize tree with
 */
void ModuleTree::InitializeTree(ModuleNode* n) {
    Vertices.clear();
    Edges.clear();
    AddVertex(n);
    TreeIsDirty = false;
    CenterOfMassPoint = FVector(0,0,0);
    CenterOfMassTotal = FVector(0,0,0);
    TargetTransform = FTransform(FVector(0,0,0));
    //goalAngles.clear();
}
/**
 * @brief set goal angles
 * @param ga goal angles
 */
void ModuleTree::SetGoalAngles(std::vector<std::vector<float> > ga) {
    this->GoalAngles = ga;
}
/**
 * @brief get goal angles
 * @return goal angles
 */
std::vector<std::vector<float> > ModuleTree::GetGoalAngles() {
    return this->GoalAngles;
}
/**
 * @brief set target transform
 * @param t target transform
 */
void ModuleTree::SetTarget(FTransform t) {
    this->TargetTransform = t;
}
/**
 * @brief get target transform
 * @return target transform
 */
FTransform ModuleTree::GetTarget() {
    return this->TargetTransform;
}
/**
 * @brief set center of mass
 * @param com center of mass point
 */
void ModuleTree::SetCenterOfMass(FVector com) {
    this->CenterOfMassPoint = com;
}
/**
 * @brief get center of mass point
 * @return center of mass
 */
FVector ModuleTree::GetCenterOfMass() {
    return this->CenterOfMassPoint;
}
/**
 * @brief reset center of mass total
 */
void ModuleTree::ResetCenterOfMassTotal() {
    this->CenterOfMassTotal = FVector(0.0);
}
/**
 * @brief set center of mass
 * @param com center of mass point
 */
void ModuleTree::AddCenterOfMassTotal(FVector com) {
    this->CenterOfMassTotal += com;
}
/**
 * @brief get center of mass point
 * @return center of mass
 */
FVector ModuleTree::GetCenterOfMassTotal() {
    return this->CenterOfMassTotal;
}
/**
 * @brief add vertex to tree
 * @param n node (vertex)
 */
void ModuleTree::AddVertex(ModuleNode* n) {
    Vertices[n->GetName()] = n;
    NodeNameMap[n->GetName()] = n;
}
/**
 * @brief set tree dirty state
 * @param dirty whether or not (true/false) tree is dirty
 */
void ModuleTree::SetTreeDirtyState(bool dirty) {
    TreeIsDirty = dirty;
}
/**
 * @brief get tree dirty state
 * @return tree is dirty or not
 */
bool ModuleTree::GetTreeDirtyState() {
    return TreeIsDirty;
}
/**
 * @brief add edge to tree
 * @param n1 node 1
 * @param n2 node 2
 */
void ModuleTree::AddEdge(const int n1, const int n2, ModuleDockFace d1, ModuleDockFace d2) {
    Edges.push_back(ModuleEdge(n1,n2,d1,d2));
    //adjacencyLists[n1].push_back(n2);
}
/**
 * @brief clear vertices and edges
 */
void ModuleTree::ClearVerticesAndEdges() {
    Vertices.clear();
    Edges.clear();
}
/**
 * @brief get queue front
 * @return front of queue
 */
ModuleNode* ModuleTree::GetQueueFront() {
    return BfsQueue.front();
}
/**
 * @brief get queue size
 * @return queue size
 */
int ModuleTree::GetQueueSize() {
    return BfsQueue.size();
}
/**
 * @brief add node to bfs queue
 * @parman smn node
 */
void ModuleTree::AddNodeToBFSQueue(ModuleNode* smn) {
    BfsQueue.push(smn);
}
/**
 * @brief pop bfs queue
 */
void ModuleTree::PopBFSQueue() {
    BfsQueue.pop();
}
/**
 * @brief getter for vertices
 * @return vertices of tree
 */
std::map<int,ModuleNode*>& ModuleTree::GetVertices() {
    return this->Vertices;
}
/**
 * @brief getter for edges
 * @return edges of tree
 */
std::vector<ModuleEdge>& ModuleTree::GetEdges() {
    return this->Edges;
}
/**
 * @brief retrieve the node with the given name
 * @param i name of node
 * @return node with given name
 */
ModuleNode* ModuleTree::GetNodeForName(const int i) {
    return NodeNameMap[i];
}
