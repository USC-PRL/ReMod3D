// Fill out your copyright notice in the Description page of Project Settings.

 
#include "BranchBoundParticleSwarm.h"
#include <chrono> 

/**
 * @brief constructor
 */
BranchBoundParticleSwarm::BranchBoundParticleSwarm(){}
/**
 * @brief destructor
 */
BranchBoundParticleSwarm::~BranchBoundParticleSwarm(){}
/**
 * @brief updates positions/velocities of particles for MODE_CONSTRICTION swarms
 */
void BranchBoundParticleSwarm::UpdateSwarmConstriction() {
    for (int i=0; i<this->NumParticles; i++) {
        for (int j=0; j<this->NumDimensions; j++) {
            std::uniform_real_distribution<> posRand(0,1);
            float NewVel = this->W*this->Particles[i].GetVelocity()[j] +
            this->W*this->C1*posRand(Generator)
            *(this->Particles[i].GetBestPosition()[j] - this->Particles[i].GetPosition()[j]) +
            this->W*this->C2*posRand(Generator)
            *(this->GlobalBestParticle.GetPosition()[j] - this->Particles[i].GetPosition()[j]);
            
            if (BestKnownParticle.GetDimension() > 0 && ShouldUseBestKnownParticle) {
                NewVel += this->W*this->C3*posRand(Generator)*(this->BestKnownParticle.GetPosition()[j] - this->Particles[i].GetPosition()[j]);
            }
            this->Particles[i].SetVelocityAtIndex(NewVel, j);
            
            this->Particles[i].ClampVelocityToBounds();
            this->Particles[i].SetPositionAtIndex(this->Particles[i].GetPosition()[j] +
                                                  this->Particles[i].GetVelocity()[j], j);
            this->Particles[i].ClampPositionToBounds();
        }
        float fitNew = this->Fitness(this->Particles[i], this->Start, this->Target);
        BranchBoundParticle BestParticle = BranchBoundParticle(this->Particles[i].GetBestPosition(), this->Particles[i].GetVelocity(), this->Particles[i].GetDimension());
        float fitOld = this->Fitness(BestParticle, this->Start, this->Target);
        if (fitNew < fitOld) {
            this->Particles[i].SetBestPosition(this->Particles[i].GetPosition());
            if (fitNew < this->GlobalBestFitness) {
                this->GlobalBestParticle = this->Particles[i];
                this->GlobalBestParticleIndex = i;
                this->GlobalBestFitness = fitNew;
                if (this->GlobalBestFitness < this->FitnessThreshold) {
                    this->FitnessThreshReached = true;
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
BranchBoundParticleSwarm::BranchBoundParticleSwarm(int nParticles, int mIterations, int nDimensions) {
    this->NumParticles = nParticles;
    this->NumIterations = mIterations;
    this->NumDimensions = nDimensions;
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
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
 */
void BranchBoundParticleSwarm::InitializeSwarm(std::vector<std::pair<float, float> > PosB,
                                       std::vector<std::pair<float, float> > VelB,
                                       float fitThresh,
                                       std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F,
                                       std::vector<float> st,
                                       std::vector<float> tar,
                                       BranchBoundParticle BestKnown,
                                       bool ShouldUseBest) {
    this->Target = tar;
    this->Start = st;
    this->SwarmCompleted = false;
    this->FitnessThreshold = fitThresh;
    this->FitnessThreshReached = false;
    this->ShouldUseBestKnownParticle = ShouldUseBest;
    this->Fitness = F;
    this->IterationCount = 0;
    this->PosBounds = PosB;
    this->VelBounds = VelB;
    this->GlobalBestFitness = -1.0;
    this->BestKnownParticle = BestKnown;
    
    this->W = 0.7298;
    if (ShouldUseBestKnownParticle) {
        this->C1 = 1.35;
        this->C2 = 1.35;
        this->C3 = 1.35;
    } else {
        this->C1 = 2.05;
        this->C2 = 2.05;
    }
    this->Particles = std::vector<BranchBoundParticle>(this->NumParticles);
    std::vector<float> startPos(this->NumDimensions);
    std::vector<float> startVel(this->NumDimensions);
    for (int i=0; i<this->NumDimensions; i++) {
        startPos[i] = 0;
        startVel[i] = 0;
    }
    //Initialize particles uniformly in posInit and velInit ranges
    for (int i=0; i<this->NumParticles; i++) {
        this->Particles[i] = BranchBoundParticle(startPos, startVel, this->NumDimensions);
        for (int j=0; j<this->NumDimensions; j++) {
            std::uniform_real_distribution<> posRand(this->PosBounds[j].first,this->PosBounds[j].second);
            this->Particles[i].SetPositionAtIndex(posRand(Generator), j);
            std::uniform_real_distribution<> velRand(this->VelBounds[j].first,this->VelBounds[j].second);
            this->Particles[i].SetVelocityAtIndex(velRand(Generator), j);
            this->Particles[i].SetPositionBoundForIndex(this->PosBounds[j], j);
            this->Particles[i].SetVelocityBoundForIndex(this->VelBounds[j], j);
        }
        this->Particles[i].SetBestPosition(this->Particles[i].GetPosition());
        //Fitness of current particle
        float fit = this->Fitness(this->Particles[i], this->Start, this->Target);
        //Keep track of global best particle found
        if (this->GlobalBestFitness < 0.0 || fit < this->GlobalBestFitness) {
            this->GlobalBestFitness = fit;
            this->GlobalBestParticle =  this->Particles[i];
            this->GlobalBestParticleIndex = i;
        }
    }
    
}
/**
 * @brief get global best particle index
 * @return global best particle index
 */
int BranchBoundParticleSwarm::GetGlobalBestParticleIndex() {
    return this->GlobalBestParticleIndex;
}
/**
 * @brief get the iteration count
 * @return iteration count
 */
int BranchBoundParticleSwarm::GetIterationCount() {
    return IterationCount;
}

/**
 * @brief return the particle at the given index in swarm particles vector
 * @param i particle index
 * @return particle at the specified index i
 */
BranchBoundParticle BranchBoundParticleSwarm::GetParticleAtIndex(int i) {
    return this->Particles[i];
}
/**
 * @brief return a new particle with the same position, velocity and dimensionality as the one given to the function
 * @param p particle to copy
 * @return particle that is a copy of p
 */
BranchBoundParticle BranchBoundParticleSwarm::CopyParticle(BranchBoundParticle const &p) {
    return BranchBoundParticle(p);
}
/**
 * @brief return global best particle found during PSO run
 * @return answer to the optimization problem, best particle found overall
 */
BranchBoundParticle BranchBoundParticleSwarm::GetGlobalBestParticle() {
    return this->GlobalBestParticle;
}

float BranchBoundParticleSwarm::GetGlobalBestFitness() {
    return this->GlobalBestFitness;
}
/**
 * @brief return the number of particles in the swarm
 * @return num particles in swarm
 */
int BranchBoundParticleSwarm::GetNumParticles() {
    return this->NumParticles;
}
/**
 * @brief return number of dimensions of each particle in swarm
 * @return num dimensions
 */
int BranchBoundParticleSwarm::GetNumDimensions() {
    return this->NumDimensions;
}
/**
 * @brief flag indicating whether or  not the PSO run has completed.
 * @return true if swarming completed, false otherwise
 */
bool BranchBoundParticleSwarm::IsSwarmingDone() {
    return this->SwarmCompleted;
}
/**
 * @brief perform pso optimization
 */
BranchBoundParticle BranchBoundParticleSwarm::Optimize() {
    while(!IsSwarmingDone()) {
        UpdateSwarm();
    }
    return this->GetGlobalBestParticle();
}
/**
 * @brief updates the swarm (performs one more PSO iteration)
 */
void BranchBoundParticleSwarm::UpdateSwarm() {
    //Update the particle positions and velocities based on variant being used
    UpdateSwarmConstriction();
    this->IterationCount++;
    //Check for termination conditions
    if (this->IterationCount >= this->NumIterations || this->FitnessThreshReached)
    {
        this->SwarmCompleted = true;
    }
}
