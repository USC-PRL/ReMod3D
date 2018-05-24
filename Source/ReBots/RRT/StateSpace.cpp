// Fill out your copyright notice in the Description page of Project Settings.

 
#include "StateSpace.h"
/**
 * @brief destructor
 */
StateSpace::~StateSpace(){}
/**
 * @brief Default constructor
 */
StateSpace::StateSpace() {
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
};
/**
 * @brief constructor with arguments
 * @param d dimensionality
 * @param bs  bounds
 * @param r threshold (range)
 */
StateSpace::StateSpace(const int d, const std::vector<std::pair<float,float> >& bs, const float r) {
    this->dimension = d;
    this->bounds = bs;
    this->range = r;
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
}
/**
 * @brief get dimension of state space
 * @return dimension of state space
 */
int StateSpace::getDimension() {
    return this->dimension;
}
/**
 * @brief get bounds of state space
 * @return bounds of state space
 */
std::vector<std::pair<float,float> >& StateSpace::getBounds() {
    return this->bounds;
}
/**
 * @brief get range of state space
 * @return range of state space
 */
float StateSpace::getRange() {
    return this->range;
}
/**
 * @brief set dimension
 * @param dimension
 */
void StateSpace::setDimension(const int d) {
    this->dimension = d;
}
/**
 * @brief set collision detector
 * @param iV is state valid function
 */
void StateSpace::setIsValidFunction(std::function<bool(const std::vector<float>&)> iV) {
    this->isValid = iV;
}
/**
 * @brief set distance function
 * @param d distance funcion
 */
void StateSpace::setDistanceFunction(std::function<float(const std::vector<float>&,const std::vector<float>&)> d) {
    this->distVal = d;
}
/**
 * @brief call collision detector
 * @param s state
 * @return true if state in Cfree, false otherwise
 */
bool StateSpace::isStateValid(const std::vector<float> & s) {
    return this->isValid(s);
}
/**
 * @brief set bounds
 * @param bounds
 */
void StateSpace::setBounds(const std::vector<std::pair<float,float> >& bs) {
    this->bounds = bs;
}
/**
 * @brief set range
 * @param r range
 */
void StateSpace::setRange(const float r) {
    this->range =r;
}
/**
 * Generate a random state within the bounds of the state space.
 * @return A random state
 */
void StateSpace::randomState(std::vector<float>& st) {
    for (int i=0; i<this->dimension; i++) {
        uniform_real_distribution<> realDis(this->bounds[i].first, this->bounds[i].second);
        st[i] = realDis(Generator);
    }
};
/**
 * Generate a random state within the bounds of the state space in Cfree.
 * @return A random state
 */
void StateSpace::randomFreeState(std::vector<float>& st) {
    bool cFree = false;
    while (!cFree) {
        for (int i=0; i<this->dimension; i++) {
            uniform_real_distribution<> realDis(this->bounds[i].first, this->bounds[i].second);
            st[i] = realDis(Generator);
        }
        cFree = isValid(st);
    }
};
/**
 * Finds a state in the direction of @target from @source.state().
 * This new state will potentially be added to the tree.  No need to do
 * any validation on the state before returning, the tree will handle
 * that.
 */
void StateSpace::intermediateState(const std::vector<float> source, const std::vector<float> target, const float stepSize,
                                   std::vector<float> &st) {
    float magnitude = 0.0;
    for (int i=0; i<this->dimension; i++) {
        magnitude += (target[i] - source[i])*(target[i] - source[i]);
    }
    magnitude = sqrt(magnitude);
    for (int i=0; i<this->dimension; i++) {
        st[i] = source[i] + stepSize*(target[i] - source[i])/magnitude;
    }
}
/**
 * @brief distance between two configurations
 * @param from initial configuration
 * @param to final configuration
 * @return distance between from and to
 */
float StateSpace::distance(const std::vector<float>& from, const std::vector<float>& to) {
    return distVal(from,to);
}
/**
 * @brief nearest vertex to n in tree t
 * @param n vertex n
 * @param t tree
 * @param vertex nearest to n in t
 */
std::vector<float> StateSpace::nearestVertex(const std::vector<float>& n, Tree t, int *cName) {
    float distanceVal = std::numeric_limits<float>::max();
    std::vector<Node> vs = t.getVertices();
    Node cNode = vs[0];
    *cName = -1;
    for (int i=0; i<vs.size(); i++) {
        float newDistance = 0.0;
        if (distanceVal < 0 || (newDistance = distVal(vs[i].getState(), n)) < distanceVal) {
            distanceVal = newDistance;
            cNode = vs[i];
            *cName = vs[i].getName();
        }
    }
    return cNode.getState();
}

/**
 * @brief Check motion validity from one state to another
 * @details Returns a boolean indicating whether or not a direct motion from
 * one state to another is valid.
 *
 * @param from The start state
 * @param to The destination state
 *
 * @return A boolean indicating validity
 */
bool StateSpace::transitionValid(const std::vector<float>& s, std::vector<float>& g, const std::vector<float>& from, const std::vector<float>& to) {
	bool bValid = false;
	bool eValid = false;
	if (distVal(from, s) < 0.01) {
		bValid = true;
	}
	else {
		if (isValid(from)) bValid = true;
	}
	if (distVal(to, g) < 0.01) {
		eValid = true;
	}
	else {
		if (isValid(to)) eValid = true;
	}
    if (bValid && eValid && distVal(from,to) <= this->range) {
        return true;
    } else {
        return false;
    }
}
/**
* @brief Check motion validity from one state to another (long distance)
* @details Returns a boolean indicating whether or not a direct motion from
* one state to another is valid.
*
* @param from The start state
* @param to The destination state
*
* @return A boolean indicating validity
*/
bool StateSpace::longTransitionValid(const std::vector<float>& s, std::vector<float>& g, const std::vector<float>& from, const std::vector<float>& to) {
	if (isValid(from) && isValid(to) && distVal(from, to) <= this->range) {
		return true;
	}
	else if (isValid(from) && isValid(to)) {
		std::vector<float> mid(from.size());
		for (int i = 0; i < mid.size(); i++) {
			mid[i] = (from[i] + to[i]) / 2.0;
		}
		return longTransitionValid(s, g, from, mid) && longTransitionValid(s,g,mid, to);
	}
	else {
		return false;
	}
}
