// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tree.h"
#include "StateSpace.h"
#include <functional>
#include <vector>
/**
 * @class RRTTree
 * @brief rrt tree
 */
class REBOTS_API RRTTree {
private:
    std::function<bool(std::vector<float>)> stateValid; /**< state valid function */
    std::vector<std::vector<float> > path; /**< current path */
    vector<int> pathVertsS; /**< path vertices start tree */
    vector<int> pathVertsG; /**< path vertices goal tree */
    Tree rrtTreeG; /**< rrt tree goal */
    Tree rrtTreeS; /**< rrt tree start */
	vector<float> start; /**< start state */
	vector<float> goal; /**< goal state */
	bool didFindSolution = false; /**< did we find a solution */
	int numStatesRandomized; /**< num states randomized */
	int numStatesOptimized; /**< num states optimized */

	unsigned Seed; /**< r seed value */
	std::mt19937 Generator; /**< random number generator */
    /**
     * @brief Calculate the distance between two states
     * @param from Start state
     * @param to End state
     * @return The distance between the states
     */
    float distance(const std::vector<float>& from, const std::vector<float>& to);
    /**
     * @brief check the connection of the RRT with the goal state
     * @param dim dimension of space
     * @param s state space
     * @param t tree
     * @param goalState state of goal
     * @param [out] goalClosest name of node closest to goal state
     */
    bool checkConnection(int dim,StateSpace& s, Tree& t, std::vector<float>& goalState, int* goalClosest);
    /**
     * @brief try to connect the two trees
     * @param cTree current tree
     * @param oTree other tree
     * @param interM target configuration of cTree
     * @param s state space
     * @param dim dimension of state space
     * @param maxStates maximum number of states in a tree
     * @param range range of RRT exploration steps
     * @return did connection succeed
     */
    bool connect(Tree* cTree,Tree* oTree, const std::vector<float>& interM, StateSpace& s, int dim,
                 int maxStates, float range);
    /**
     * @brief build rapidly exploring random tree (unidirectional)
     * @param initState initial state
     * @param bs bounds per dimension
     * @param maxStates maximum number of states
     * @param range range of RRT procedure
     */
    std::vector<std::vector<float> > buildRRTConnect(std::vector<float> initState, std::vector<float> goalState,
                                                     std::vector<std::pair<float,float> > bs, int maxStates, float range,
                                                     Tree& sTree, Tree& gTree);
public:
    /**
     * @brief destructor
     */
    ~RRTTree();
    /**
     * @brief constructor
     */
    RRTTree();
    /**
     * @brief constructor
     * @param sv state valid function
     */
    RRTTree(std::function<bool(std::vector<float>)> sv);
    /**
     * @brief run RRT connect path planner
     * @param initState initial state
     * @param goalState goal state
     * @param bs bounds
     * @param maxStates maximum number states allowed
     * @param range range of path planning query
     * @return path
     */
    std::vector<std::vector<float> > rrtConnectPathPlanner(std::vector<float> initState, std::vector<float> goalState,
                                                           std::vector<std::pair<float,float> > bs, int maxStates,
                                                           float range);
	/**
	* @brief did the process find a solution
	* @return true if we found a solution, false otherwise
	*/
	bool didRRTFindSolution();
	/**
	* @brief get the length of the path
	* @return length of path
	*/
	float getPathLength();
	int getNumStatesOptimized();
	int getNumStatesRandomized();
	int getNumGraphNodes();
};
