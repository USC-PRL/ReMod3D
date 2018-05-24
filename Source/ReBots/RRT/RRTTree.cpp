// Fill out your copyright notice in the Description page of Project Settings.

 
#include "RRTTree.h"
/**
 * @brief constructor
 */
RRTTree::RRTTree() { 
	this->didFindSolution = false;    
	Seed = std::chrono::system_clock::now().time_since_epoch().count();
	Generator = std::mt19937(Seed);
}
/**
 * @brief constructor
 * @param sv state valid function
 */
RRTTree::RRTTree(std::function<bool(std::vector<float>)> sv) {
    this->stateValid = sv;
    pathVertsS.clear();
    pathVertsG.clear();
	this->didFindSolution = false;
	Seed = std::chrono::system_clock::now().time_since_epoch().count();
	Generator = std::mt19937(Seed);
}
/**
 * @brief Calculate the distance between two states
 * @param from Start state
 * @param to End state
 * @return The distance between the states
 */
float RRTTree::distance(const std::vector<float>& from, const std::vector<float>& to) {
    float dist = 0.0;
    for (int i=0; i<from.size(); i++) {
        dist += (from[i] - to[i])*(from[i] - to[i]);
    }
    return sqrt(dist);
}
/**
 * @brief check the connection of the RRT with the goal state
 * @param dim dimension of space
 * @param s state space
 * @param t tree
 * @param goalState state of goal
 * @param [out] goalClosest name of node closest to goal state
 */
bool RRTTree::checkConnection(int dim,StateSpace& s, Tree& t, std::vector<float>& goalState, int* goalClosest) {
    float distanceToGoal = 0.0;
    std::vector<float> gClose = s.nearestVertex(goalState, t, goalClosest);
    if (s.transitionValid(this->start,this->goal,goalState, gClose)) {
        return true;
    } else {
        return false;
    }
}
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
bool RRTTree::connect(Tree* cTree,Tree* oTree, const std::vector<float>& interM, StateSpace& s, int dim,
                      int maxStates, float range) {
    int oCloseName;
    std::vector<float> cOther = s.nearestVertex(interM,*oTree,&oCloseName);
    while(true) {
        std::vector<float> interOther(dim);
        s.intermediateState(cOther,interM,range,interOther);
        bool trapped = !(s.isStateValid(interOther) && s.transitionValid(start,goal,cOther, interOther));
        if (!trapped) {
            Node interOtherNode(interOther,true,oTree->getVertices().size(),dim);
            oTree->addVertex(interOtherNode);
            oTree->addEdge(oCloseName,interOtherNode.getName());
			numStatesRandomized++;
            cOther = interOther;
            oCloseName = interOtherNode.getName();
            if (s.transitionValid(start, goal, interM,interOther)) {
                return true;
            }
            
        } else {
            return false;
        }
    }
    return false;
}
/**
 * @brief build rapidly exploring random tree (unidirectional)
 * @param initState initial state
 * @param bs bounds per dimension
 * @param maxStates maximum number of states
 * @param range range of RRT procedure
 */
std::vector<std::vector<float> > RRTTree::buildRRTConnect(std::vector<float> initState, std::vector<float> goalState,
                                                          std::vector<std::pair<float,float> > bs, int maxStates, float range,
                                                          Tree& sTree, Tree& gTree) {
    Tree tS,tG;
	this->start = initState;
	this->goal = goalState;
    bool startTree = true;
    StateSpace s(bs.size(),bs,range);
    s.setIsValidFunction(this->stateValid);
    s.setDistanceFunction(std::bind(&RRTTree::distance, this,std::placeholders::_1,std::placeholders::_2));
    Node initNode(initState,true,0,bs.size());
    Node goalNode(goalState,true,0,bs.size());
    tS.initializeTree(initNode);
    tG.initializeTree(goalNode);
    pathVertsG.clear();
    pathVertsS.clear();
    rrtTreeS = Tree();
    rrtTreeG = Tree();
    path.clear();
    while (tS.getVertices().size() < maxStates && tG.getVertices().size() < maxStates) {
        Tree *cTree = NULL, *oTree = NULL;
        if (startTree) {cTree = &tS; oTree = &tG;}
        else {cTree = &tG; oTree = &tS;}
        int closestName;
		std::uniform_real_distribution<> real01(0, 1);
		std::vector<float> randQ(bs.size());
		s.randomState(randQ);
		std::vector<float> gState;
		if (startTree) {
			gState = goalState;
		}
		else {
			gState = initState;
		}
		if (real01(Generator) < 0.2) {
			randQ = gState;
		}
        std::vector<float> closestQ = s.nearestVertex(randQ, *cTree, &closestName);
        std::vector<float> interM(bs.size());
        s.intermediateState(closestQ, randQ, range, interM);
        if (s.transitionValid(start,goal,closestQ,interM)) {
            Node interNode(interM,true,cTree->getVertices().size(),bs.size());
            cTree->addVertex(interNode);
            cTree->addEdge(closestName,cTree->getVertices().size() - 1);
			numStatesRandomized++;
            if (connect(cTree, oTree, interM, s, bs.size(), maxStates, range)) {
                sTree = tS;
                gTree = tG;
                pathVertsS = sTree.BFS(0,sTree.getVertices().size() - 1);
                pathVertsG = gTree.BFS(0,gTree.getVertices().size() - 1);
                rrtTreeS = sTree;
                rrtTreeG = gTree;
                for (int i=0; i<pathVertsS.size(); i++) {
                    Node n = sTree.getNodeForName(pathVertsS[i]);
                    vector<float> angles = n.getState();
                    path.push_back(angles);
                }
                for (int i=pathVertsG.size() -1; i>=0; i--) {
                    Node n = gTree.getNodeForName(pathVertsG[i]);
                    vector<float> angles = n.getState();
                    path.push_back(angles);
                }
				this->didFindSolution = true;
                return path;
            }
            
        }
        startTree = !startTree;
    }
    sTree = tS;
    gTree = tG;
    path.clear();
	this->didFindSolution = false;
    return path;
}
/**
 * @brief run RRT connect path planner
 * @param initState initial state
 * @param goalState goal state
 * @param bs bounds
 * @param maxStates maximum number states allowed
 * @param range range of path planning query
 */
std::vector<std::vector<float> > RRTTree::rrtConnectPathPlanner(std::vector<float> initState, std::vector<float> goalState,
                                                                std::vector<std::pair<float,float> > bs, int maxStates,
                                                                float range) {
    return buildRRTConnect(initState,goalState,bs,maxStates,range,this->rrtTreeS,this->rrtTreeG);
}
/**
* @brief did the process find a solution
* @return true if we found a solution, false otherwise
*/
bool RRTTree::didRRTFindSolution() {
	return this->didFindSolution;
}
/**
* @brief get the length of the path
* @return length of path
*/
float RRTTree::getPathLength() {
	if (this->didFindSolution) {
		float pathLength = 0.0;
		for (int i = 1; i < path.size(); i++) {
			pathLength += distance(path[i - 1], path[i]);
		}
		return pathLength;
	}
	else {
		return -1;
	}
}
/**
* @brief get num states optimized
* @return num states optimized
*/
int RRTTree::getNumStatesOptimized() { return 0; }
/**
* @brief get num states randomized
* @return num states randomized
*/
int RRTTree::getNumStatesRandomized() { return numStatesRandomized; }
int RRTTree::getNumGraphNodes() { return numStatesRandomized; }
/**
 * @brief destructor
 */
RRTTree::~RRTTree(){}
