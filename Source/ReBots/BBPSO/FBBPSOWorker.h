// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <chrono>
#include <sstream>
#include <random>
#include <iostream>
#include <ctime>
#include "BranchBoundPSO.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
typedef std::chrono::high_resolution_clock Clock;
using namespace std;
/**
 * @class FBBPSOWorker
 * @brief Worker to dispatch BBPSO operation on a separate thread
 */
class REBOTS_API FBBPSOWorker : public FRunnable
{
    static FBBPSOWorker* Runnable;/**<  Singleton instance, can access the thread any time via static accessor, if it is active! */
    FRunnableThread* Thread;/**< Thread to run the worker FRunnable on */
    std::vector<std::pair<float,float> > PositionBounds; /**< position bounds */
	double ElapsedTime; /**< elapsed run time */
    std::vector<std::pair<float,float> > VelocityBounds; /**< velocity bounds */
    std::vector<float> Target; /**< target vector */
    std::vector<float> Start; /**< start vector */
    std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> Fitness; /**< fitness function */
    float Delta; /**< delta */
    BranchBoundPSO BBPSO; /**< instance of the optimization procedure */
    std::vector<float>& SolutionPosition; /**< place to store solution */
    int NumParticlces; /**< num particles */
    int NumIterations; /**< num iterations */
    int NumDimensions; /**< num dimensions */
    float* SolutionFitnessValue; /**< solution fitness value */
    FThreadSafeCounter StopTaskCounter;  /**< Stop this thread? Uses Thread Safe Counter */
    unsigned Seed; /**< seed value */
    std::mt19937 Generator; /**< generator for random nums */
    bool HaveFoundSolution = false; /**< have we found a solution yet? */
    int IDNum = 0; /**< initial id number */
	std::chrono::time_point<std::chrono::steady_clock> start; /**< starting time */
public:
	/**
	* @brief get elapsed time
	* @param elapsed time
	*/
	float GetElapsedTime();
    /**
     * @brief get current upper bound
     * @return current upper bound
     */
    float GetCurrentUpperBound();
    /**
     * @brief get num active partitions
     * @return current num active partitions
     */
    int GetNumActivePartitions();
    /**
     * @brief is the thread finished?
     * @return true if finished, false otherwise
     */
    bool IsFinished() const
    {
        return HaveFoundSolution;
    }
    /**
     * @brief constructor
     * @param NParts number of particles
     * @param NIts number of iterations
     * @param NDims number of dimensions
     * @param SPos solution position
     * @param SFitnessValue solution fitness value
     */
    FBBPSOWorker(int NParts, int NIts, int NDims,
                 std::vector<std::pair<float,float> > PBounds, std::vector<std::pair<float,float> > VBounds, float D,
                 std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F,
                 std::vector<float> St, std::vector<float> Tar,
                 std::vector<float>& SPos, float* SFitnessValue);
    /**
     * @brief destructor
     */
    virtual ~FBBPSOWorker();
    /**
     * @brief initialize thread
     * @return whether or not initialization was succesful
     */
    virtual bool Init();
    /**
     * @brief run thread
     * @return return code (int)
     */
    virtual uint32 Run();
    /**
     * @brief stop thread
     */
    virtual void Stop();
    /**
     * @brief ensure that the thread has completed properly
     */
    void EnsureCompletion();
    
    /**
     * @brief initialize BBPSO thread 
     * @param NParts number of particles
     * @param NIts number of iterations
     * @param NDims number of dimensions
     * @param PBounds position bounds
     * @param VBounds velocity bounds
     * @param D threshold value
     * @param F fitness function
     * @param Tar target vector
     * @param SPos [out] solution position
     * @param SFitnessValue [out] solution fitness value
     */
    static FBBPSOWorker* BBPSOInit(int NParts, int NIts, int NDims,
                                   std::vector<std::pair<float,float> > PBounds, std::vector<std::pair<float,float> > VBounds, float D,
                                   std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F,
                                   std::vector<float> St,
                                   std::vector<float> Tar,
                                   std::vector<float>& SPos, float* SFitnessValue);
    /**
     * @brief shutdown the thread
     */
    static void Shutdown();
    /**
     * @brief is the thread finished?
     * @return true if thread finished, false otherwise
     */
    static bool IsThreadFinished();
};
