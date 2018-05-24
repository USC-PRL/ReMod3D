// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <utility>
#include <vector>
#include <queue>
#include "Node.h"
#include <algorithm>
#include <map>
using namespace std;

/**
 * @class Tree
 * @brief Class representing a tree for path planning
 * @author Thomas Collins
 * @version 1.0
 * @date 04/11/2015
 * Contact: collinst@usc.edu
 * Created on: 04/11/2015
 */
class REBOTS_API Tree {
private:
    std::vector<Node> vertices; /**< vertices of tree */
    std::vector<std::pair<int,int> > edges; /**< edges of tree */
    std::map<int,Node> nodeNameMap; /**< map of node names to nodes */
    std::map<int,std::vector<int> > adjacencyLists; /**< adjacency lists for each node */
public:
    /**
     * @brief destructor
     */
    ~Tree();
    /**
     * @brief default constructor
     */
    Tree();
    /**
     * @brief initialize tree with node
     * @param n node to initialize tree with
     */
    void initializeTree(Node& n);
    /**
     * @brief add vertex to tree
     * @param n node (vertex)
     */
    void addVertex(Node& n);
    /**
     * @brief add edge to tree
     * @param n1 node 1
     * @param n2 node 2
     */
    void addEdge(const int n1, const int n2);
    /**
     * @brief getter for vertices
     * @return vertices of tree
     */
    std::vector<Node>& getVertices();
    /**
     * @brief getter for edges
     * @return edges of tree
     */
    std::vector<std::pair<int,int> >& getEdges();
    /**
     * @brief retrieve the node with the given name
     * @param i name of node
     * @return node with given name
     */
    Node& getNodeForName(const int i);
    /**
     * @brief get adjacency list for node
     * @param int n node name
     * @return adjacency list for node
     */
    std::vector<int>& getAdjListForNode(const int n);
    /**
     * @brief breadth first search
     * @param n1 initial node
     * @param dim dimension of node
     * @return path
     */
    std::vector<int > BFS(const int n1, const int n2);
};
