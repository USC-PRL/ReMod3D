// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include "Tree.h"
using namespace std;
/**
 * @class StateSpace
 * @brief Class representing a state space for path planning
 * @author Thomas Collins
 * @version 1.0
 * @date 04/11/2015
 * Contact: collinst@usc.edu
 * Created on: 04/11/2015
 */
class REBOTS_API StateSpace {
private:
    int dimension; /**< dimensionality of state space */
    std::vector<std::pair<float,float> > bounds; /**< bounds for each dimension */
    std::function<bool(const std::vector<float>&)> isValid; /**< is state valid? */
    std::function<float(const std::vector<float>&, const std::vector<float>&)> distVal; /**< calculate distance */
    float range; /**< max step size */
    unsigned Seed; /**< r seed value */
    std::mt19937 Generator; /**< random number generator */
public:
    /**
     * @brief destructor
     */
    ~StateSpace();
    /**
     * @brief Default constructor
     */
    StateSpace();
    /**
     * @brief constructor with arguments
     * @param d dimensionality
     * @param bs  bounds
     * @param r threshold (range)
     */
    StateSpace(const int d, const std::vector<std::pair<float,float> >& bs, const float r);
    /**
     * @brief get dimension of state space
     * @return dimension of state space
     */
    int getDimension();    /**
                            * @brief get bounds of state space
                            * @return bounds of state space
                            */
    std::vector<std::pair<float,float> >& getBounds();
    /**
     * @brief get range of state space
     * @return range of state space
     */
    float getRange();    /**
                          * @brief set dimension
                          * @param dimension
                          */
    void setDimension(const int d);
    /**
     * @brief set collision detector
     * @param iV is state valid function
     */
    void setIsValidFunction(std::function<bool(const std::vector<float>&)> iV);
    /**
     * @brief set distance function
     * @param d distance funcion
     */
    void setDistanceFunction(std::function<float(const std::vector<float>&,const std::vector<float>&)> d);
    /**
     * @brief call collision detector
     * @param s state
     * @return true if state in Cfree, false otherwise
     */
    bool isStateValid(const std::vector<float> & s);
    /**
     * @brief set bounds
     * @param bounds
     */
    void setBounds(const std::vector<std::pair<float,float> >& bs);
    /**
     * @brief set range
     * @param r range
     */
    void setRange(const float r);
    /**
     * Generate a random state within the bounds of the state space.
     * @return A random state
     */
    void randomState(std::vector<float>& st);
    /**
     * Generate a random state within the bounds of the state space in Cfree.
     * @return A random state
     */
    void randomFreeState(std::vector<float>& st);
    /**
     * Finds a state in the direction of @target from @source.state().
     * This new state will potentially be added to the tree.  No need to do
     * any validation on the state before returning, the tree will handle
     * that.
     */
    void intermediateState(const std::vector<float> source, const std::vector<float> target, const float stepSize,
                           std::vector<float> &st);
    /**
     * @brief distance between two configurations
     * @param from initial configuration
     * @param to final configuration
     * @return distance between from and to
     */
    float distance(const std::vector<float>& from, const std::vector<float>& to);
    /**
     * @brief nearest vertex to n in tree t
     * @param n vertex n
     * @param t tree
     * @param vertex nearest to n in t
     */
    std::vector<float> nearestVertex(const std::vector<float>& n, Tree t, int *cName);
    
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
    bool transitionValid(const std::vector<float>& s, std::vector<float>& g, const std::vector<float>& from, const std::vector<float>& to);
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
	bool longTransitionValid(const std::vector<float>& s, std::vector<float>& g, const std::vector<float>& from, const std::vector<float>& to);
};
