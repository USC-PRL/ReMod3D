// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include <queue>
#include "BranchBoundParticleSwarm.h"
#include "BranchBoundParticle.h"
#include "BranchBoundPartition.h"
#include <map>
#include <limits>
#include <time.h>
/**
 * @class BranchBoundPSO
 * @brief Class representing the branch and bound particle swarm optimization algorithm
 */
class REBOTS_API BranchBoundPSO
{
private:
    std::vector<BranchBoundPartition*> InactivePartitions; /**< all partitions */
    std::vector<BranchBoundPartition*> ActivePartitions; /**< currently active partitions */
    BranchBoundParticle BestGlobalBestParticle; /**< final solution to problem */
    int PartitionLimit; /**< number of partitions to limit */
    int StepCount = 0; /**< step counter */
    clock_t start_time; /**< starting time */
    int TimeLimitSeconds = 200; /**< time limit of procedure in seconds */
    float Delta; /**< allowable error between lower and upper bounds */
    float CurrentLowerBound; /**< current lower bound */
    float CurrentUpperBound; /**< current upper bound */
	int CurrentBestPartition = -1; /**< current best partion */
    std::vector<std::pair<float,float> > PosBounds; /**< position bounds */
    std::vector<std::pair<float,float> > VelBounds; /**< velocity bounds */
    std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> Fitness; /**< fitness function */
    std::vector<float> Target; /**< target vector */
    std::vector<float> Start; /**< start vector */
	float BestPartitionBias = 0.2; /**< bias toward splitting best partition */
    int NumDimensions; /**< number of dimensions */
    int NumParticles; /**< number of particles */
    int NumIterations; /**< number of iterations */
    unsigned Seed; /**< seed value */
    std::mt19937 Generator; /**< generator for random nums */
    int DebugPrint = false; /**< Debug print for PSO procedure */
    /**
     * @brief branch the given partition
     * @param P partition
     */
    void BranchPartition(BranchBoundPartition* P);
    /**
     * @brief update partition lists
     * @param parentp parent partition
     * @param childrenp children partitions
     */
    void UpdatePartitionLists(BranchBoundPartition *ParentP, std::vector<BranchBoundPartition*> ChildrenP);
    /**
     * @brief bound active partition at index
     * @param i index
     */
    void BoundPartitionAtIndex(int i);
public:
    /**
     * @brief get number of active partitions
     * @return number of active partitions
     */
    int GetNumActivePartitions();
    /**
     * @brief initialize PSO BB procedure
     * @param PosB position bounds
     * @param VelB velocity bounds
     * @param D delta 
     * @param F fitness function
     * @param st start vector
     * @param tar target vector
     */
    void InitializeBBPSO(std::vector<std::pair<float, float> > PosB, std::vector<std::pair<float, float> > VelB, float D,
                         std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F, std::vector<float> st, std::vector<float> tar);
    /**
     * @brief compute velocity bounds for position bounds
     * @param PBounds position bounds
     * @return velocity bounds
     */
    std::vector<std::pair<float,float> > ComputeVelocityBoundsForPositionBounds(std::vector<std::pair<float,float> > PBounds);
    /**
     * @brief get time limit in seconds
     * @return time limit in seconds
     */
    int GetTimeLimitSeconds();
    /**
     * @brief get partition limit
     * @return partition limit
     */
    int GetPartitionLimit();
    /**
     * @brief get delta value
     * @return delta value
     */
    float GetDelta();
    /**
     * @brief get current lower bound
     * @return lower bound
     */
    float GetCurrentLowerBound();
    /**
     * @brief get current upper bound
     * @return upper bound
     */
    float GetCurrentUpperBound();
    /**
     * @brief set time limit in seconds
     * @param TL limit in seconds
     */
    void SetTimeLimitSeconds(int TL);
    /**
     * @brief set partition limit
     * @param PL partition limit
     */
    void SetPartitionLimit(int PL);
    /**
     * @brief set delta value
     * @param D delta value
     */
    void SetDelta(float D);
    /**
     * @brief set current lower bound
     * @param LB lower bound
     */
    void SetCurrentLowerBound(float LB);
    /**
     * @brief set current upper bound 
     * @param UB upper bound
     */
    void SetCurrentUpperBound(float UB);
    /**
     * @brief optimize using Branch and bound PSO
     */
    void BBPSOOptimize();
    /**
     * @brief optimize using Branch and bound PSO (one step)
     */
    bool BBPSOOptimizeStep();
    /**
     * @brief get final optimization solution
     * @return final best particle
     */
    BranchBoundParticle GetFinalSolution();
    /**
     * @brief constructor
     */
	BranchBoundPSO();
    /**
     * @brief constructor
     * @param NumP number of particles
     * @param NumIt number of iterations
     * @param NumDim number of dimensions
     */
    BranchBoundPSO(int NumP, int NumIt, int NumDim);
    /**
     * @brief destructor
     */
	~BranchBoundPSO();
};
