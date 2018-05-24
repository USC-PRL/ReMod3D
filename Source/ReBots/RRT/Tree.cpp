// Fill out your copyright notice in the Description page of Project Settings.

 
#include "Tree.h"

/**
 * @brief destructor
 */
Tree::~Tree(){}
/**
 * @brief default constructor
 */
Tree::Tree() {}
/**
 * @brief initialize tree with node
 * @param n node to initialize tree with
 */
void Tree::initializeTree(Node& n) {
    vertices.clear();
    edges.clear();
    addVertex(n);
}
/**
 * @brief add vertex to tree
 * @param n node (vertex)
 */
void Tree::addVertex(Node& n) {
    vertices.push_back(n);
    nodeNameMap[n.getName()] = n;
    adjacencyLists[n.getName()] = std::vector<int>(0);
}
/**
 * @brief add edge to tree
 * @param n1 node 1
 * @param n2 node 2
 */
void Tree::addEdge(const int n1, const int n2) {
    edges.push_back(std::pair<int,int>(n1,n2));
    adjacencyLists[n1].push_back(n2);
}
/**
 * @brief getter for vertices
 * @return vertices of tree
 */
std::vector<Node>& Tree::getVertices() {
    return this->vertices;
}
/**
 * @brief getter for edges
 * @return edges of tree
 */
std::vector<std::pair<int,int> >& Tree::getEdges() {
    return this->edges;
}
/**
 * @brief retrieve the node with the given name
 * @param i name of node
 * @return node with given name
 */
Node& Tree::getNodeForName(const int i) {
    return nodeNameMap[i];
}
/**
 * @brief get adjacency list for node
 * @param int n node name
 * @return adjacency list for node
 */
std::vector<int>& Tree::getAdjListForNode(const int n) {
    return adjacencyLists[n];
}
/**
 * @brief breadth first search
 * @param n1 initial node
 * @param dim dimension of node
 * @return path
 */
std::vector<int > Tree::BFS(const int n1, const int n2) {
    std::vector<bool> isNodeDiscovered(vertices.size());
    std::vector<int> prev(vertices.size());
    for (int i=0; i<vertices.size(); i++) {
        isNodeDiscovered[i] = false;
        prev[i] = -1;
    }
    std::queue<int> qu;
    qu.push(n1);
    isNodeDiscovered[n1] = true;
    while (qu.size() > 0) {
        Node v = nodeNameMap[qu.front()];
        qu.pop();
        std::vector<int> adj = adjacencyLists[v.getName()];
        for (int i=0; i<adj.size(); i++) {
            Node w = nodeNameMap[adj[i]];
            if (!isNodeDiscovered[w.getName()]) {
                isNodeDiscovered[w.getName()] = true;
                prev[w.getName()] = v.getName();
                qu.push(w.getName());
            }
        }
    }
    std::vector<int> prevFromGoal;
    int current = n2;
    while (current != -1) {
        prevFromGoal.push_back(current);
        current = prev[current];
    }
    std::reverse(prevFromGoal.begin(),prevFromGoal.end());
    return prevFromGoal;
}
