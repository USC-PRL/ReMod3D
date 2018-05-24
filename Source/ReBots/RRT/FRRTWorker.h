// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RRTTree.h"
#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <sstream>
using namespace std;
/**
 * @class FRRTWorker
 * @brief rrt worker for separate thread
 */
class REBOTS_API FRRTWorker : public FRunnable
{
    static  FRRTWorker* Runnable;/**<  Singleton instance, can access the thread any time via static accessor, if it is active! */
    FRunnableThread* Thread;/**< Thread to run the worker FRunnable on */
    std::vector<std::pair<float,float> > PositionBounds; /**< position bounds */
    std::vector<float> Target; /**< target vector */
    int TCLimit; /**< try limit */
    std::vector<float> Start; /**< start vector */
    std::function<bool(std::vector<float>)> StateV;
    std::function<float(std::vector<float>,std::vector<float>)> Dist;
    int MaxNumStates; /**< num allowable states */
    float Delta; /**< delta */
    RRTTree RRT; /**< instance of the optimization procedure */
    std::vector<std::vector<float> >& SolutionPosition; /**< place to store solution */
    int NumDimensions; /**< num dimensions */
    float* SolutionFitnessValue; /**< solution fitness value */
    FThreadSafeCounter StopTaskCounter;  /**< Stop this thread? Uses Thread Safe Counter */
    unsigned Seed; /**< seed value */
    std::mt19937 Generator; /**< generator for random nums */
    bool HaveFoundSolution = false; /**< have we found a solution yet? */
    int IDNum = 0; /**< id number */
    
public:
	int GetNumStatesOptimized();
	int GetNumStatesRandomized();
	float GetPathSize();
	int GetGraphSize();
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
     * @param NumStates number of states (max)
     * @param NDims number of dimensions
     * @param Try number of tries
     * @param PBounds position bounds
     * @param D threshold
     * @param SV state valid function
     * @param Dis distance function
     * @param St start vector
     * @param Tar target vector
     * @param SPos solution position
     * @param SFitnessValue solution fitness value
     */
    FRRTWorker(int NumStates, int NDims, int Try,
                std::vector<std::pair<float,float> > PBounds, float D,
                std::function<bool(std::vector<float>)> SV,
                std::function<float(std::vector<float>,std::vector<float>)> Dis,
                std::vector<float> St,
                std::vector<float> Tar,
                std::vector<std::vector<float> >& SPos,
                float* SFitnessValue);
    /**
     * @brief destructor
     */
    virtual ~FRRTWorker();
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
     * @brief constructor
     * @param NumStates number of states (max)
     * @param NDims number of dimensions
     * @param Try number of tries
     * @param PBounds position bounds
     * @param D threshold
     * @param SV state valid function
     * @param Dis distance function
     * @param St start vector
     * @param Tar target vector
     * @param SPos solution position
     * @param SFitnessValue solution fitness value
     */
    static FRRTWorker* RRTInit(int NumStates, int NDims, int Try,
                                 std::vector<std::pair<float,float> > PBounds, float D,
                                 std::function<bool(std::vector<float>)> SV,
                                 std::function<float(std::vector<float>,std::vector<float>)> Dis,
                                 std::vector<float> St,
                                 std::vector<float> Tar,
                                 std::vector<std::vector<float> >& SPos, float* SFitnessValue);
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
