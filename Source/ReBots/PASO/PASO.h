// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <functional>
#include <vector>
#include "BBPSO/BranchBoundParticle.h"
#include "BBPSO/BranchBoundParticleSwarm.h"
#include "BBPSO/BranchBoundPSO.h"
#include "PSO/PSOParticleSwarm.h"
#include "PSO/PSOParticle.h"
#include "PSO/PSOParticleFitness.h"
using namespace std;
/**
 * @class PASO
 * @brief paso algorithm
 */
class REBOTS_API PASO
{
private:
    std::vector<std::pair<float, float> > PosBounds; /**< run time bounds in which to keep particles */
    std::vector<std::pair<float, float> > VelBounds; /**< initialization bounds for particles */
    std::vector<std::vector<float> > Path; /**< path computed by PASO */
    int TryCounter = 0; /**< number of tries to connect the path */
    int TryCounterLimit = 0; /**< number of tries to limit trying to connect */
    float BaseCaseError = 0.0; /**< step size */
    std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> FitnessFunction; /**< fitness function */
    std::function<bool(std::vector<float>)> StateValid; /**< collision detector */
    std::function<float(std::vector<float>,std::vector<float>)> Distance; /**< distance function */
    std::function<std::vector<float>(std::vector<float>, std::vector<float>)> ComputeLGoal; /**< interpolate linearly local goal */
    int CDim; /**< dimensionality of problem in C-space */
    int WDim; /**< dimensionality of problem in W-space */
    float DistanceStartToGoal; /**< initial start to goal distance */
    float PasoRuntime; /**< runtime of PASO algorithm */
    bool DidConverge = false; /**< did the PASO algorithm converge on a solution? */
public:
    /**
     * @brief destructor
     */
    ~PASO();
    /**
     * @brief constructor
     */
    PASO();
    /**
     * @brief constructor
     * @param tcLimit try counter limit
     * @param baseCase step size
     * @param PBounds position bounds
     * @param VBouns velocity bounds
     * @param Fit fitness function
     * @param StateV state valid
     * @param Dist distance function
     */
    PASO(int cdim, int wdim, int tcLimit, float baseCase, std::vector<std::pair<float, float> > PBounds,
         std::vector<std::pair<float, float> > VBounds, std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> Fit,
         std::function<bool(std::vector<float>)> StateV,std::function<float(std::vector<float>,std::vector<float>)> Dist);
    /**
     * @brief get path
     * @return path planned by algorithm
     */
    std::vector<std::vector<float> > GetPath();
    /**
     * @brief getter for pasoRuntime
     * @return value of pasoRuntime
     */
    float GetPASORuntime();
    /**
     * @brief did paso converge
     * @return whether or not paso converged
     */
    bool DidPASOConverge();
	/**
	* @brief get number of tries performed
	* @return try counter value
	*/
	int GetTryCounter();
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
	bool LongTransitionValid(const std::vector<float>& from, const std::vector<float>& to, float range);
    /**
     * @brief plan path function (PASO V5)
     * @param start starting point in c space
     * @param goal goal point in c space
     * @param run initialization bounds
     * @param vel run bounds
     * @param tryLimit number of tries to allow before failure
     * @param baseCase resolution of path (distance metric)
     * @param forward is direction forward (true) or reverse (false)
     * @return planned path
     */
    bool PlanPathOptimize(std::vector<float> start,
                          std::vector<float> goal);
    /**
     * @brief compute bounds
     * @param point point around which bounds should be made
     * @param range range around which to create bounds around
     */
    std::vector<std::pair<float,float> > ComputePosBounds(std::vector<float> point, float range);
    /**
     * @brief compute bounds
     * @param bs position bounds
     */
    std::vector<std::pair<float,float> > ComputeVelBounds(std::vector<std::pair<float,float> > bs);
    
};
