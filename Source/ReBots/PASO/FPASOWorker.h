// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PASO.h"
#include "RRT/RRTTree.h"
#include <vector>
#include <functional>
#include <chrono>
#include <random>
using namespace std;
/**
 * @class FPASOWorker
 * @brief paso worker
 */
class REBOTS_API FPASOWorker : public FRunnable
{
    static  FPASOWorker* Runnable;/**<  Singleton instance, can access the thread any time via static accessor, if it is active! */
    FRunnableThread* Thread;/**< Thread to run the worker FRunnable on */
    std::vector<std::pair<float,float> > PositionBounds; /**< position bounds */
    std::vector<std::pair<float,float> > VelocityBounds; /**< velocity bounds */
    std::vector<float> Target; /**< target vector */
    std::vector<float> Start; /**< start vector */
    int TCLimit; /**< try counter limit */
    float BaseCase; /**< Base case */
    std::function<bool(std::vector<float>)> StateV;
    std::function<float(std::vector<float>,std::vector<float>)> Dist;
    std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> Fitness; /**< fitness function */
    float Delta; /**< delta */
    PASO PASOPP; /**< instance of the optimization procedure */
    std::vector<std::vector<float> >& SolutionPosition; /**< place to store solution */
    int NumParticlces; /**< num particles */
    int NumIterations; /**< num iterations */
    int NumDimensions; /**< num dimensions */
    float* SolutionFitnessValue; /**< solution fitness value */
    FThreadSafeCounter StopTaskCounter;  /**< Stop this thread? Uses Thread Safe Counter */
    bool HaveFoundSolution = false; /**< have we found a solution yet? */
    unsigned Seed; /**< seed value */
	RRTTree RRT; /**< instance of the optimization procedure */
    std::mt19937 Generator; /**< generator for random nums */
	bool DidC = false; //
    
public:
    /**
     * @brief did paso converge
     * @return whether or not paso converged
     */
    bool DidConverge() {
        return DidC;
    }
	/**
	* @brief get try counter
	* @return try count
	*/
	int GetTryCounter() {
		return PASOPP.GetTryCounter();
	}
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
     * @param Try number of tries
     * @param PBounds position bounds
     * @param VBounds velocity bounds
     * @param D delta
     * @param Fit fitness function
     * @param SV state valid function
     * @param Dis distance function
     * @param St start vector
     * @param Tar target vector
     * @param SPos solution position
     * @param SFitnessValue solution fitness value
     */
    FPASOWorker(int NParts, int NIts, int NDims, int Try,
                std::vector<std::pair<float,float> > PBounds,
                std::vector<std::pair<float,float> > VBounds, float D,
                std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> Fit,
                std::function<bool(std::vector<float>)> SV,
                std::function<float(std::vector<float>,std::vector<float>)> Dis,
                std::vector<float> St,
                std::vector<float> Tar,
                std::vector<std::vector<float> >& SPos,
                float* SFitnessValue);
    /**
     * @brief destructor
     */
    virtual ~FPASOWorker();
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
    static FPASOWorker* PASOInit(int NParts, int NIts, int NDims, int Try,
                                 std::vector<std::pair<float,float> > PBounds,
                                 std::vector<std::pair<float,float> > VBounds, float D,
                                 std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> Fit,
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
