 
#include "PSOParticleSwarm.h"

/**
 * @brief update swarm MODE_ACCELERATED
 */
void PSOParticleSwarm::updateSwarmAccelerated() {
    for (int i=0; i<this->numParticles; i++) {
        for (int j=0; j<numDimensions; j++) {
            std::normal_distribution<> normDist(0,1);
            float newPos = (1 - beta)*this->particles[i].getPositionAtIndex(j) +
            beta*this->globalBestParticle.getPositionAtIndex(j) + alpha*normDist(generator);
            this->particles[i].setPositionAtIndex(newPos,j);
            if (this->particles[i].getPositionAtIndex(j) < this->posRun[j].first) {
                this->particles[i].setPositionAtIndex(this->posRun[j].first, j);
            }
            if (this->particles[i].getPositionAtIndex(j) > this->posRun[j].second) {
                this->particles[i].setPositionAtIndex(this->posRun[j].second,j);
            }
        }
        float fitNew = this->fitness(this->particles[i],this->start,this->target);
        if (fitNew < this->globalBestFitness) {
            this->globalBestParticle = copyParticle(this->particles[i]);
            this->globalBestFitness = fitNew;
            if (this->globalBestFitness < this->fitnessThreshold) {
                this->fitnessThreshReached = true;
            }
        }
    }
}
/**
 * @brief updates positions/velocities of particles for MODE_CONSTRICTION swarms
 */
void PSOParticleSwarm::updateSwarmConstriction() {
    for (int i=0; i<this->numParticles; i++) {
        for (int j=0; j<this->numDimensions; j++) {
            std::uniform_real_distribution<> posRand(0,1);
            float newVel = this->w*this->particles[i].getVelocityAtIndex(j) +
            this->w*this->c1*posRand(generator)
            *(this->bestParticles[i].getPositionAtIndex(j) - this->particles[i].getPositionAtIndex(j)) +
            this->w*this->c2*posRand(generator)
            *(this->globalBestParticle.getPositionAtIndex(j) - this->particles[i].getPositionAtIndex(j));
            this->particles[i].setVelocityAtIndex(newVel, j);
            if (this->particles[i].getVelocityAtIndex(j) < this->velRun[j].first) {
                this->particles[i].setVelocityAtIndex(this->velRun[j].first, j);
            }
            if (this->particles[i].getVelocityAtIndex(j) > this->velRun[j].second) {
                this->particles[i].setVelocityAtIndex(this->velRun[j].second, j);
            }
            this->particles[i].setPositionAtIndex(this->particles[i].getPositionAtIndex(j) +
                                                  this->particles[i].getVelocityAtIndex(j), j);
            if (this->particles[i].getPositionAtIndex(j) < this->posRun[j].first) {
                this->particles[i].setPositionAtIndex(this->posRun[j].first, j);
            }
            if (this->particles[i].getPositionAtIndex(j) > this->posRun[j].second) {
                this->particles[i].setPositionAtIndex(this->posRun[j].second,j);
            }
        }
        float fitNew = this->fitness(this->particles[i], this->start, this->target);
        float fitOld = this->fitness(this->bestParticles[i], this->start, this->target);
        if (fitNew < fitOld) {
            this->bestParticles[i] = copyParticle(this->particles[i]);
            if (fitNew < this->globalBestFitness) {
                this->globalBestParticle = copyParticle(this->particles[i]);
                this->globalBestFitness = fitNew;
                if (this->globalBestFitness < this->fitnessThreshold) {
                    this->fitnessThreshReached = true;
                }
            }
        }
    }
}
/**
 * @brief updates positions/velocities for MODE_BARE_BONES swarms
 */
void PSOParticleSwarm::updateSwarmBBPSO() {
    for (int i=0; i<this->numParticles; i++) {
        for (int j=0; j<this->numDimensions; j++) {
            std::normal_distribution<> normDist(
                                       0.5*(this->bestParticles[i].getPositionAtIndex(j) + this->globalBestParticle.getPositionAtIndex(j)),
                                       fabs(this->bestParticles[i].getPositionAtIndex(j) - this->globalBestParticle. getPositionAtIndex(j)));
            float randNum = normDist(generator);
            this->particles[i].setPositionAtIndex(randNum, j);
            if (this->particles[i].getPositionAtIndex(j) < this->posRun[j].first) {
                this->particles[i].setPositionAtIndex(this->posRun[j].first, j);
            }
            if (this->particles[i].getPositionAtIndex(j) > this->posRun[j].second) {
                this->particles[i].setPositionAtIndex(this->posRun[j].second, j);
            }
        }
        float fitNew = this->fitness(this->particles[i], this->start,this->target);
        float fitOld = this->fitness(this->bestParticles[i], this->start,this->target);
        if (fitNew < fitOld) {
            this->bestParticles[i] = copyParticle(this->particles[i]);
            if (fitNew < this->globalBestFitness) {
                this->globalBestParticle = copyParticle(this->particles[i]);
                this->globalBestFitness = fitNew;
                if (this->globalBestFitness < this->fitnessThreshold) {
                    this->fitnessThreshReached = true;
                }
            }
        }
    }
}
/**
 * @brief constructor
 * @param numParticles num particles in swarm
 * @param maxIterations maximum iterations in PSO run
 * @param numDimensions dimensionality of problem (num elements in velocity, position vectors of particles in swarm)
 */
PSOParticleSwarm::PSOParticleSwarm(int nParticles, int mIterations, int nDimensions) {
    this->numParticles = nParticles;
    this->numIterations = mIterations;
    this->numDimensions = nDimensions;
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::mt19937(seed);
}

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
void PSOParticleSwarm::initializeSwarm(std::vector<std::pair<float, float> > pInit,
                                      std::vector<std::pair<float, float> > vInit,
                                      std::vector<std::pair<float, float> > pRun,
                                      std::vector<std::pair<float, float> > vRun,
                                      float fitThresh, PSO_MODE m,
                                      std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> f,
                                       std::vector<float> st,
                                      std::vector<float> tar,
                                      bool saveBestCol) {
    this->target = tar;
    this->start = st;
    this->swarmCompleted = false;
    this->fitnessThreshold = fitThresh;
    this->fitnessThreshReached = false;
    this->mode = m;
    this->fitness = f;
    this->iterationCount = 0;
    this->posInit = pInit;
    this->velInit = vInit;
    this->posRun = pRun;
    this->velRun = vRun;
    this->globalBestFitness = -1.0;
    this->w = 0.7298;
    this->c1 = 2.05;
    this->c2 = 2.05;
    this->alpha = 0.7;
    this->beta = 0.5;
    this->saveBestCollisionParticles = saveBestCol;
    this->particles = std::vector<PSOParticle>(this->numParticles);
    this->bestParticles = std::vector<PSOParticle>(this->numParticles);
    this->bestCollisionParticles = std::vector<PSOParticle>();
    std::vector<float> startPos(this->numDimensions);
    std::vector<float> startVel(this->numDimensions);
    for (int i=0; i<this->numDimensions; i++) {
        startPos[i] = 0;
        startVel[i] = 0;
    }
    //Initialize particles uniformly in posInit and velInit ranges
    for (int i=0; i<this->numParticles; i++) {
        this->particles[i] = PSOParticle(this->numDimensions, startPos, startVel);
        for (int j=0; j<this->numDimensions; j++) {
            std::uniform_real_distribution<> posRand(this->posInit[j].first,this->posInit[j].second);
            this->particles[i].
            setPositionAtIndex(posRand(generator), j);
            //Only need to initialize velocity for variants that use it
            if (this->mode == MODE_CONSTRICTION) {
                std::uniform_real_distribution<> velRand(this->velInit[j].first,this->velInit[j].second);
                this->particles[i].
                setVelocityAtIndex(velRand(generator), j);
            }
            //best particles are initially just these initial particles
            this->bestParticles[i] = copyParticle(this->particles[i]);
        }
        //Fitness of current particle
        float fit = this->fitness(this->particles[i], this->start,this->target);
        //Keep track of global best particle found
        if (this->globalBestFitness < 0.0 || fit < this->globalBestFitness) {
            this->globalBestFitness = fit;
            this->globalBestParticle =  copyParticle(this->particles[i]);
        }
    }
    
}
/**
 * @brief set collision detector
 * @param col collision detector
 */
void PSOParticleSwarm::setCollisionDetector(std::function<bool(std::vector<float>)> col) {
    this->collision = col;
}
/**
 * @brief get the iteration count
 * @return iteration count
 */
int PSOParticleSwarm::getIterationCount() {
    return iterationCount;
}

/**
 * @brief return the particle at the given index in swarm particles vector
 * @param i particle index
 * @return particle at the specified index i
 */
PSOParticle PSOParticleSwarm::getParticleAtIndex(int i) {
    return this->particles[i];
}
/**
 * @brief return the particle at the given index in swarm bestParticles vector
 * @param i index of bestParticle particle
 * @return bestParticle at the specified index i
 */
PSOParticle PSOParticleSwarm::getBestParticleAtIndex(int i) {
    return this->bestParticles[i];
}
/**
 * @brief get best particles of swarm
 * @return best particles
 */
std::vector<PSOParticle> PSOParticleSwarm::getBestParticles() {
    return this->bestParticles;
}
/**
 * @brief get best collision particles of swarm
 * @return best collision particles
 */
std::vector<PSOParticle> PSOParticleSwarm::getBestCollisionParticles() {
    return this->bestCollisionParticles;
}
/**
 * @brief return a new particle with the same position, velocity and dimensionality as the one given to the function
 * @param p particle to copy
 * @return particle that is a copy of p
 */
PSOParticle PSOParticleSwarm::copyParticle(PSOParticle const &p) {
    return PSOParticle(p);
}
/**
 * @brief return global best particle found during PSO run
 * @return answer to the optimization problem, best particle found overall
 */
PSOParticle PSOParticleSwarm::getGlobalBestParticle() {
    return this->globalBestParticle;
}

float PSOParticleSwarm::getGlobalBestFitness() {
    return this->globalBestFitness;
}
/**
 * @brief return the number of particles in the swarm
 * @return num particles in swarm
 */
int PSOParticleSwarm::getNumParticles() {
    return this->numParticles;
}
/**
 * @brief return number of dimensions of each particle in swarm
 * @return num dimensions
 */
int PSOParticleSwarm::getNumDimensions() {
    return this->numDimensions;
}
/**
 * @brief flag indicating whether or  not the PSO run has completed.
 * @return true if swarming completed, false otherwise
 */
bool PSOParticleSwarm::isSwarmingDone() {
    return this->swarmCompleted;
}
/**
 * @brief perform pso optimization
 */
PSOParticle PSOParticleSwarm::optimize() {
    while(!isSwarmingDone()) {
        updateSwarm();
    }
    return this->getGlobalBestParticle();
}
/**
 * @brief updates the swarm (performs one more PSO iteration)
 */
void PSOParticleSwarm::updateSwarm() {
    //Update the particle positions and velocities based on variant being used
    if (this->mode == MODE_CONSTRICTION) {
        updateSwarmConstriction();
    } else if (this->mode == MODE_BARE_BONES) {
        updateSwarmBBPSO();
    } else if (this->mode == MODE_ACCELERATED) {
        updateSwarmAccelerated();
    }
    this->iterationCount++;
    //Check for termination conditions
    if (this->iterationCount >= this->numIterations || this->fitnessThreshReached)
    {
        this->swarmCompleted = true;
    }
}
