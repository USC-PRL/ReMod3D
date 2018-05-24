// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BranchBoundParticle.h"
#include <random>
#include <vector>
#include <functional>
/**
 * @class BranchBoundParticleSwarm
 * @brief particle swarm for branch and bound PSO
 */
class REBOTS_API BranchBoundParticleSwarm
{
private:
    bool SwarmCompleted; /**< has swarming completed */
    bool FitnessThreshReached; /**< fitness threshold reached */
    float C1; /**< PSO c1 constant */
    float C2; /**< PSO c2 constant */
    float C3; /**< PSO c3 constant */
    float W; /**< PSO w constant */
    float GlobalBestFitness; /**< global best fitness */
    int IterationCount; /**< iteration count */
    int NumDimensions; /**< num dimensions of swarm */
    int NumParticles; /**< num particles in swarm */
    int NumIterations; /**< max iterations of PSO */
    int GlobalBestParticleIndex; /**< global best particle index */
    std::vector<BranchBoundParticle> Particles; /**< particles in swarm */
    std::vector<std::pair<float, float> > PosBounds; /**< pos init bounds */
    std::vector<std::pair<float, float> > VelBounds; /**< vel init bounds */
    BranchBoundParticle BestKnownParticle; /**< best known particle */
    BranchBoundParticle GlobalBestParticle; /**< global best particle */
    bool ShouldUseBestKnownParticle; /**< should we use best known particle? */
    float FitnessThreshold; /**< fitness threshold */
    std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> Fitness; /**< fitness function pointer */
    std::vector<float> Target; /**< target position */
    unsigned Seed; /**< seed value */
    std::mt19937 Generator; /**< generator for random nums */
    int IDNumber; /**< id number of swarm */
    std::vector<float> Start; /**< start configuration */
    /**
     * @brief updates positions/velocities of particles for MODE_CONSTRICTION swarms
     */
    void UpdateSwarmConstriction();
public:
    /**
     * @brief constructor
     */
	BranchBoundParticleSwarm();
    /**
     * @brief destructor
     */
	~BranchBoundParticleSwarm();
    /**
     * @brief constructor
     * @param numParticles num particles in swarm
     * @param maxIterations maximum iterations in PSO run
     * @param numDimensions dimensionality of problem (num elements in velocity, position vectors of particles in swarm)
     */
    BranchBoundParticleSwarm(int numParticles, int maxIterations, int numDimensions);
    
    /**
     * @brief initialize swarm for PSO run
     * @param posInit bounds for particle position initialization
     * @param velInit bounds for particle velocity initialization
     * @param posRun bounds for particle position during PSO run
     * @param velRun bounds for particle velocity during PSO run
     * @param fitThresh threshold for early termination of PSO run due to high enough fitness
     * @param m PSO variant being used (see above)
     * @param fitness pointer to fitness function to evaluate particles
     */
    void InitializeSwarm(std::vector<std::pair<float, float> > PosB,
                         std::vector<std::pair<float, float> > VelB,
                         float fitThresh,
                         std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F,
                         std::vector<float> st,
                         std::vector<float> tar,
                         BranchBoundParticle BestKnown,
                         bool ShouldUseBest);
    /**
     * @brief get iteration count
     * @return iteration count
     */
    int GetIterationCount();
    /**
     * @brief get global best particle index
     * @return global best particle index
     */
    int GetGlobalBestParticleIndex();
    /**
     * @brief return the particle at the given index in swarm particles vector
     * @param i particle index
     * @return particle at the specified index i
     */
    BranchBoundParticle GetParticleAtIndex(int i);
    /**
     * @brief return a new particle with the same position, velocity and dimensionality as the one given to the function
     * @param p particle to copy
     * @return particle that is a copy of p
     */
    BranchBoundParticle CopyParticle(BranchBoundParticle const &p);
    /**
     * @brief return global best particle found during PSO run
     * @return answer to the optimization problem, best particle found overall
     */
    BranchBoundParticle GetGlobalBestParticle();
    /**
     * @brief get best fitness
     * @return global best fitness
     */
    float GetGlobalBestFitness();
    /**
     * @brief return the number of particles in the swarm
     * @return num particles in swarm
     */
    int GetNumParticles();
    /**
     * @brief return number of dimensions of each particle in swarm
     * @return num dimensions
     */
    int GetNumDimensions();
    /**
     * @brief flag indicating whether or  not the PSO run has completed.
     * @return true if swarming completed, false otherwise
     */
    bool IsSwarmingDone();
    /**
     * @brief perform pso optimization
     */
    BranchBoundParticle Optimize();
    /**
     * @brief updates the swarm (performs one more PSO iteration)
     */
    void UpdateSwarm();
};
