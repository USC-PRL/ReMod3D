#include "PSOParticle.h"
#include <functional>
#include <chrono>
#include <random>
#pragma once
/**
 * @enum pso mode
 * @brief particle swarm optimization variants supported
 */
enum PSO_MODE {
    MODE_CONSTRICTION = 0,
    MODE_BARE_BONES = 1,
    MODE_ACCELERATED = 2
};
/**
 * @class PSOParticleSwarm
 * @brief pso particle swarm
 */
class REBOTS_API PSOParticleSwarm
{
private:
    bool swarmCompleted; /**< has swarming completed */
    bool saveBestCollisionParticles; /**< save best particles that are in collision */
    bool fitnessThreshReached; /**< fitness threshold reached */
    float c1; /**< PSO c1 constant */
    float c2; /**< PSO c2 constant */
    float w; /**< PSO w constant */
    float globalBestFitness; /**< global best fitness */
    int iterationCount; /**< iteration count */
    int numDimensions; /**< num dimensions of swarm */
    int numParticles; /**< num particles in swarm */
    int numIterations; /**< max iterations of PSO */
    std::vector<PSOParticle> particles; /**< particles in swarm */
    std::vector<PSOParticle> bestParticles; /**< particle bests in swarm */
    std::vector<PSOParticle> bestCollisionParticles; /**< particle bests in swarm (and in C_nonfree))\*/
    std::vector<std::pair<float, float> > posInit; /**< pos init bounds */
    std::vector<std::pair<float, float> > posRun; /**< pos run bounds */
    std::vector<std::pair<float, float> > velInit; /**< vel init bounds */
    std::vector<std::pair<float, float> > velRun; /**< vel run bounds */
    PSOParticle globalBestParticle; /**< global best particle */
    float fitnessThreshold; /**< fitness threshold */
    std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> fitness; /**< fitness function pointer */
    std::function<bool(std::vector<float>)> collision; /**< collision detector (if saving collision particles) */
    std::vector<float> target; /**< target position */
    std::vector<float> start; /**< start position */
    PSO_MODE mode; /**< pso mode */
    unsigned seed; /**< seed value */
    std::mt19937 generator; /**< generator for random nums */
    float alpha; /**< alpha */
    float beta; /**< beta */
    /**
     * @brief updates positions/velocities of particles for MODE_CONSTRICTION swarms
     */
    void updateSwarmConstriction();
    /**
     * @brief updates positions/velocities for MODE_BARE_BONES swarms
     */
    void updateSwarmBBPSO();
    /**
     * @brief update swarm MODE_ACCELERATED
     */
    void updateSwarmAccelerated();
public:
    /**
     * @brief constructor
     * @param numParticles num particles in swarm
     * @param maxIterations maximum iterations in PSO run
     * @param numDimensions dimensionality of problem (num elements in velocity, position vectors of particles in swarm)
     */
    PSOParticleSwarm(int numParticles, int maxIterations, int numDimensions);
    
    /**
     * @brief initialize swarm for PSO run
     * @param posInit bounds for particle position initialization
     * @param velInit bounds for particle velocity initialization
     * @param posRun bounds for particle position during PSO run
     * @param velRun bounds for particle velocity during PSO run
     * @param fitThresh threshold for early termination of PSO run due to high enough fitness
     * @param m PSO variant being used (see above)
     * @param fitness pointer to fitness function to evaluate particles
     * @param st start vector
     * @param tar target vector
     * @param saveBestCol should save best collision particles
     */
    void initializeSwarm(std::vector<std::pair<float, float> > posInit,
                         std::vector<std::pair<float, float> > velInit,
                         std::vector<std::pair<float, float> > posRun,
                         std::vector<std::pair<float, float> > velRun,
                         float fitThresh, PSO_MODE m,
                         std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> fitness,
                         std::vector<float> st,
                         std::vector<float> tar,
                         bool saveBestCol = false);
    /**
     * @brief set collision detector
     * @param col collision detector
     */
    void setCollisionDetector(std::function<bool(std::vector<float>)> col);
    /**
     * @brief get iteration count
     * @return iteration count
     */
    int getIterationCount();
    /**
     * @brief return the particle at the given index in swarm particles vector
     * @param i particle index
     * @return particle at the specified index i
     */
    PSOParticle getParticleAtIndex(int i);
    /**
     * @brief return the particle at the given index in swarm bestParticles vector
     * @param i index of bestParticle particle
     * @return bestParticle at the specified index i
     */
    PSOParticle getBestParticleAtIndex(int i);
    /**
     * @brief get best particles
     * @return best particles
     */
    std::vector<PSOParticle> getBestParticles();
    /**
     * @brief get best collision particles
     * @return best collision particles
     */
    std::vector<PSOParticle> getBestCollisionParticles();
    /**
     * @brief return a new particle with the same position, velocity and dimensionality as the one given to the function
     * @param p particle to copy
     * @return particle that is a copy of p
     */
    PSOParticle copyParticle(PSOParticle const &p);
    /**
     * @brief return global best particle found during PSO run
     * @return answer to the optimization problem, best particle found overall
     */
    PSOParticle getGlobalBestParticle();
    /**
     * @brief get best fitness
     * @return global best fitness
     */
    float getGlobalBestFitness();
    /**
     * @brief return the number of particles in the swarm
     * @return num particles in swarm
     */
    int getNumParticles();
    /**
     * @brief return number of dimensions of each particle in swarm
     * @return num dimensions
     */
    int getNumDimensions();
    /**
     * @brief flag indicating whether or  not the PSO run has completed.
     * @return true if swarming completed, false otherwise
     */
    bool isSwarmingDone();
    /**
     * @brief perform pso optimization
     */
    PSOParticle optimize();
    /**
     * @brief updates the swarm (performs one more PSO iteration)
     */
    void updateSwarm();
};
