// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RRT/Tree.h"
#include "RRT/StateSpace.h"
#include "PSO/PSOParticleSwarm.h"
#include "PSO/PSOParticle.h"
#include <functional>
#include <chrono>
#include <random>
#include <iostream>
#include <vector>
/**
 * 
 */
class REBOTS_API RORTTree
{
private:
	std::function<bool(std::vector<float>)> stateValid; /**< state valid function */
	std::function<float(PSOParticle, std::vector<float>, std::vector<float>)> fitnessFunc; /**< fitness function */
	std::vector<std::vector<float> > path; /**< current path */
	vector<int> pathVertsS; /**< path vertices start tree */
	vector<int> pathVertsG; /**< path vertices goal tree */
	Tree rrtTreeG; /**< rrt tree goal */
	std::vector<float> start;
	std::vector<float> goal;
	Tree rrtTreeS; /**< rrt tree start */
	float alpha = 0.9; /**< alpha */
	int numStatesOptimized = 0;
	int numStatesRandomized = 0;
	unsigned Seed; /**< seed value */
	std::mt19937 Generator; /**< generator for random nums */
	bool didFindSolution = false; /**< did we find a solution */
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
	bool checkConnection(int dim, StateSpace& s, Tree& t, std::vector<float>& goalState, int* goalClosest);
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
	bool connect(Tree* cTree, Tree* oTree, const std::vector<float>& interM, StateSpace& s, int dim,
		int maxStates, float range);
	/**
	* @brief build rapidly exploring random tree (unidirectional)
	* @param initState initial state
	* @param bs bounds per dimension
	* @param maxStates maximum number of states
	* @param range range of RRT procedure
	*/
	std::vector<std::vector<float> > buildRORTConnect(std::vector<float> initState, std::vector<float> goalState,
		std::vector<std::pair<float, float> > bs, int maxStates, float range,
		Tree& sTree, Tree& gTree);
	/**
	* @brief finish pp by joining two trees
	* @param tS tree start
	* @param tG tree goal
	* @param sTree start tree
	* @param gTree goal tree
	*/
	void finishRORT(Tree tS, Tree tG, Tree& sTree, Tree& gTree);
public:
	/**
	* @brief destructor
	*/
	~RORTTree();
	/**
	* @brief constructor
	*/
	RORTTree();
	/**
	* @brief constructor
	* @param sv state valid function
	*/
	RORTTree(std::function<bool(std::vector<float>)> sv,
		std::function<float(PSOParticle, std::vector<float>, std::vector<float>)> fit);
	/**
	* @brief run RRT connect path planner
	* @param initState initial state
	* @param goalState goal state
	* @param bs bounds
	* @param maxStates maximum number states allowed
	* @param range range of path planning query
	* @return path
	*/
	std::vector<std::vector<float> > rortConnectPathPlanner(std::vector<float> initState, std::vector<float> goalState,
		std::vector<std::pair<float, float> > bs, int maxStates,
		float range);
	/**
	* @brief did the process find a solution
	* @return true if we found a solution, false otherwise
	*/
	bool didRORTFindSolution();
	/**
	* @brief get the length of the path
	* @return length of path
	*/
	float getPathLength();
	/**
	* @brief get num states optimized
	* @return num states optimized
	*/
	int getNumStatesOptimized();
	/**
	* @brief get num states randomized
	* @return num states randomized
	*/
	int getNumStatesRandomized();
	/**
	* @brief patch path
	*/
	void patchUpPath(float range, int dim);
	/**
	* @brief compute bounds
	* @param point point around which bounds should be made
	* @param range range around which to create bounds around
	*/
	std::vector<std::pair<float, float> > computePosBounds(std::vector<std::pair<float,float> > bs, std::vector<float> point, float range);
	/**
	* @brief compute bounds
	* @param bs position bounds
	* @return velocity bounds
	*/
	std::vector<std::pair<float, float> > computeVelBounds(std::vector<std::pair<float, float> > bs);
	int getNumGraphNodes();
};

