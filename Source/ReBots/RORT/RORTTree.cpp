// Fill out your copyright notice in the Description page of Project Settings.

 
#include "RORTTree.h"
/**
* @brief constructor
*/
RORTTree::RORTTree() { this->didFindSolution = false; }
/**
* @brief constructor
* @param sv state valid function
*/
RORTTree::RORTTree(std::function<bool(std::vector<float>)> sv,
	std::function<float(PSOParticle, std::vector<float>, std::vector<float>)> fit) {
	this->stateValid = sv;
	this->fitnessFunc = fit;
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
float RORTTree::distance(const std::vector<float>& from, const std::vector<float>& to) {
	float dist = 0.0;
	for (int i = 0; i<from.size(); i++) {
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
bool RORTTree::checkConnection(int dim, StateSpace& s, Tree& t, std::vector<float>& goalState, int* goalClosest) {
	float distanceToGoal = 0.0;
	std::vector<float> gClose = s.nearestVertex(goalState, t, goalClosest);
	if (s.transitionValid(start,goal,goalState, gClose)) {
		return true;
	}
	else {
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
bool RORTTree::connect(Tree* cTree, Tree* oTree, const std::vector<float>& interM, StateSpace& s, int dim,
	int maxStates, float range) {
	int oCloseName;
	std::vector<float> cOther = s.nearestVertex(interM, *oTree, &oCloseName);
	while (true) {
		std::vector<float> interOther(dim);
		s.intermediateState(cOther, interM, range, interOther);
		bool trapped = !(s.isStateValid(interOther) && s.transitionValid(start,goal,cOther, interOther));
		if (!trapped) {
			Node interOtherNode(interOther, true, oTree->getVertices().size(), dim);
			oTree->addVertex(interOtherNode);
			oTree->addEdge(oCloseName, interOtherNode.getName());
			numStatesRandomized++;
			cOther = interOther;
			oCloseName = interOtherNode.getName();
			if (s.transitionValid(start,goal,interM, interOther)) {
				return true;
			}

		}
		else {
			return false;
		}
	}
	return false;
}
/**
* @brief compute bounds
* @param point point around which bounds should be made
* @param range range around which to create bounds around
*/
std::vector<std::pair<float, float> > RORTTree::computePosBounds(std::vector<std::pair<float,float> > bs,
												std::vector<float> point, float range) {
	std::vector<std::pair<float, float> > pbounds(point.size());
	for (int i = 0; i<point.size(); i++) {
		pbounds[i] = std::pair<float, float>(fmax(point[i] - range, bs[i].first), fmin(point[i] + range, bs[i].second));
	}
	return pbounds;
}
/**
* @brief compute bounds
* @param bs position bounds
* @return velocity bounds
*/
std::vector<std::pair<float, float> > RORTTree::computeVelBounds(std::vector<std::pair<float, float> > bs) {
	std::vector<std::pair<float, float> > velB(bs.size());
	for (int i = 0; i<bs.size(); i++) {
		float maxVal = fabs(fmax(bs[i].first, bs[i].second));
		velB[i] = std::pair<float, float>(-maxVal, maxVal);
	}
	return velB;
}
/**
* @brief build rapidly exploring random tree (unidirectional)
* @param initState initial state
* @param bs bounds per dimension
* @param maxStates maximum number of states
* @param range range of RRT procedure
*/
std::vector<std::vector<float> > RORTTree::buildRORTConnect(std::vector<float> initState, std::vector<float> goalState,
	std::vector<std::pair<float, float> > bs, int maxStates, float range,
	Tree& sTree, Tree& gTree) {
	Tree tS, tG;
	this->start = initState;
	this->goal = goalState;
	bool startTree = true;
	StateSpace s(bs.size(), bs, range);
	s.setIsValidFunction(this->stateValid);
	s.setDistanceFunction(std::bind(&RORTTree::distance, this, std::placeholders::_1, std::placeholders::_2));
	Node initNode(initState, true, 0, bs.size());
	Node goalNode(goalState, true, 0, bs.size());
	tS.initializeTree(initNode);
	tG.initializeTree(goalNode);
	pathVertsG.clear();
	pathVertsS.clear();
	rrtTreeS = Tree();
	rrtTreeG = Tree();
	path.clear();
	std::uniform_real_distribution<> real01(0, 1);
	while (tS.getVertices().size() < maxStates && tG.getVertices().size() < maxStates) {
		bool shouldTryConnect = false;
		Tree *cTree = NULL, *oTree = NULL;
		if (startTree) { cTree = &tS; oTree = &tG; }
		else { cTree = &tG; oTree = &tS; }
		int closestName;
		std::vector<float> randQ(bs.size());
		s.randomState(randQ);
		std::vector<float> closestQ = s.nearestVertex(randQ, *cTree, &closestName);
		std::vector<float> interM(bs.size());
		s.intermediateState(closestQ, randQ, range, interM);

		if (real01(Generator) < alpha) {
			std::vector<float> gState(bs.size());
			if (startTree) {
				gState = goalState;
			}
			else {
				gState = initState;
			}
			int oCloseName;
			std::vector<float> cOther = s.nearestVertex(gState, *oTree, &oCloseName);
			closestQ = s.nearestVertex(gState, *cTree, &closestName);
			PSOParticleSwarm PSOSwarm = PSOParticleSwarm(20, 30, bs.size());
			PSOSwarm.initializeSwarm(computePosBounds(bs, closestQ, range), 
				computeVelBounds(computePosBounds(bs, closestQ, range)), 
				computePosBounds(bs, closestQ, range),
				computeVelBounds(computePosBounds(bs, closestQ, range))
				, 0.001, MODE_CONSTRICTION, fitnessFunc,
				closestQ, cOther);
			PSOParticle P = PSOSwarm.optimize();
			std::vector<float> optPos = P.getPosition();
			if (s.longTransitionValid(start,goal,closestQ, optPos) && distance(optPos, cOther) < distance(closestQ, cOther)) {
				Node interNode(optPos, true, cTree->getVertices().size(), bs.size());
				cTree->addVertex(interNode);
				cTree->addEdge(closestName, cTree->getVertices().size() - 1);
				numStatesOptimized++;
				if (connect(cTree, oTree, optPos, s, bs.size(), maxStates, range)) {
					finishRORT(tS, tG, sTree, gTree);
					patchUpPath(range, bs.size());
					return path;
				}
			}
			else {
				std::vector<float> randQL(bs.size());
				s.randomState(randQL);
				closestQ = s.nearestVertex(randQL, *cTree, &closestName);
				s.intermediateState(closestQ, randQL, range, interM);
				if (s.transitionValid(start,goal,closestQ, interM)) {
					Node interNode(interM, true, cTree->getVertices().size(), bs.size());
					cTree->addVertex(interNode);
					cTree->addEdge(closestName, cTree->getVertices().size() - 1);
					numStatesRandomized++;
					if (connect(cTree, oTree, interM, s, bs.size(), maxStates, range)) {
						finishRORT(tS, tG, sTree, gTree);
						patchUpPath(range, bs.size());
						return path;
					}

				}
			}
		}
		else {
			if (s.transitionValid(start,goal,closestQ, interM)) {
				Node interNode(interM, true, cTree->getVertices().size(), bs.size());
				cTree->addVertex(interNode);
				cTree->addEdge(closestName, cTree->getVertices().size() - 1);
				numStatesRandomized++;
				if (connect(cTree, oTree, interM, s, bs.size(), maxStates, range)) {
					finishRORT(tS, tG, sTree, gTree);
					patchUpPath(range, bs.size());
					return path;
				}

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
* @brief patch path
*/
void RORTTree::patchUpPath(float range, int dim) {
	std::vector<std::vector<float> > tempPath;
	std::map<std::pair<int, int>, std::vector<std::vector<float> > > fixMap;
	for (int i = 1; i < path.size(); i++) {
		if (distance(path[i - 1], path[i]) > range) {
			std::vector<float> diff(dim);
			for (int j = 0; j < dim; j++) {
				diff[j] = (path[i][j] - path[i - 1][j]) / distance(path[i - 1], path[i]);
			}
			int numPathEls = distance(path[i - 1], path[i]) / range;
			std::vector<std::vector<float> > fixPathEls;
			for (int j = 0; j < numPathEls; j++) {
				std::vector<float> pathEl(dim);
				for (int k = 0; k < pathEl.size(); k++) {
					pathEl[k] = range*(j + 1)*path[i - 1][j];
				}
				fixPathEls.push_back(pathEl);
			}
			fixMap[std::pair<int,int>(i-1,i)] = fixPathEls;
		}
	}

	std::cout << "Done Fixing Pairs" << std::endl;
}
/**
* @brief finish pp by joining two trees
* @param tS tree start
* @param tG tree goal
* @param sTree start tree
* @param gTree goal tree
*/
void RORTTree::finishRORT(Tree tS, Tree tG, Tree& sTree, Tree& gTree) {
	sTree = tS;
	gTree = tG;
	pathVertsS = sTree.BFS(0, sTree.getVertices().size() - 1);
	pathVertsG = gTree.BFS(0, gTree.getVertices().size() - 1);
	rrtTreeS = sTree;
	rrtTreeG = gTree;
	for (int i = 0; i<pathVertsS.size(); i++) {
		Node n = sTree.getNodeForName(pathVertsS[i]);
		vector<float> angles = n.getState();
		path.push_back(angles);
	}
	for (int i = pathVertsG.size() - 1; i >= 0; i--) {
		Node n = gTree.getNodeForName(pathVertsG[i]);
		vector<float> angles = n.getState();
		path.push_back(angles);
	}
	this->didFindSolution = true;
}
/**
* @brief run RRT connect path planner
* @param initState initial state
* @param goalState goal state
* @param bs bounds
* @param maxStates maximum number states allowed
* @param range range of path planning query
*/
std::vector<std::vector<float> > RORTTree::rortConnectPathPlanner(std::vector<float> initState, std::vector<float> goalState,
	std::vector<std::pair<float, float> > bs, int maxStates,
	float range) {
	return buildRORTConnect(initState, goalState, bs, maxStates, range, this->rrtTreeS, this->rrtTreeG);
}
int RORTTree::getNumGraphNodes() {
	return numStatesOptimized+numStatesRandomized;
}
/**
* @brief did the process find a solution
* @return true if we found a solution, false otherwise
*/
bool RORTTree::didRORTFindSolution() {
	return this->didFindSolution;
}
/**
* @brief get the length of the path
* @return length of path
*/
float RORTTree::getPathLength() {
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
int RORTTree::getNumStatesOptimized() {
	return this->numStatesOptimized;
}
/**
* @brief get num states randomized
* @return num states randomized
*/
int RORTTree::getNumStatesRandomized() {
	return this->numStatesRandomized;
}
/**
* @brief destructor
*/
RORTTree::~RORTTree() {}

