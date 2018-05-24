// Fill out your copyright notice in the Description page of Project Settings.

 
#include "FPASOWorker.h"
//***********************************************************
//Thread Worker Starts as NULL, prior to being instanced
//		This line is essential! Compiler error without it
FPASOWorker* FPASOWorker::Runnable = NULL;
//***********************************************************
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
FPASOWorker::FPASOWorker(int NParts, int NIts, int NDims, int Try,
                         std::vector<std::pair<float,float> > PBounds,
                         std::vector<std::pair<float,float> > VBounds, float D,
                         std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> Fit,
                         std::function<bool(std::vector<float>)> SV,
                         std::function<float(std::vector<float>,std::vector<float>)> Dis,
                         std::vector<float> St,
                         std::vector<float> Tar,
                         std::vector<std::vector<float> >& SPos,
                         float* SFitnessValue) :SolutionPosition(SPos)
{
    this->PositionBounds = PBounds;
    this->VelocityBounds = VBounds;
    this->Target = Tar;
    this->TCLimit = Try;
    this->Start = St;
    this->StateV = SV;
    this->Dist = Dis;
    this->NumParticlces = NParts;
    this->NumIterations = NIts;
    this->NumDimensions = NDims;
    this->Fitness = Fit;
    this->Delta = D;
    this->SolutionFitnessValue = SFitnessValue;
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
    std::uniform_int_distribution<> IDNumDist(0, std::numeric_limits<int>::max());
    FString WorkerFString = FString::Printf(TEXT("PASOWorker%d"), IDNumDist(Generator));
    this->Thread = FRunnableThread::Create(this, *WorkerFString, 0, TPri_Highest); //windows default = 8mb for thread, could specify more
}
/**
 * @brief destructor
 */
FPASOWorker::~FPASOWorker() {
    delete Thread;
    Thread = NULL;
}
/**
 * @brief initialize thread
 * @return whether or not initialization was succesful
 */
bool FPASOWorker::Init() {
    PASOPP = PASO(NumDimensions, NumDimensions, TCLimit, Delta, PositionBounds, VelocityBounds, Fitness, StateV, Dist);
	//RRT = RRTTree(StateV);
	cout<<"Initializing PASO On Separate Thread"<<endl;
    return true;
}
/**
 * @brief run thread
 * @return return code (int)
 */
uint32 FPASOWorker::Run() {
    PASOPP.PlanPathOptimize(Start, Target);
    SolutionPosition = PASOPP.GetPath();
	DidC = PASOPP.DidPASOConverge();
	//SolutionPosition = RRT.rrtConnectPathPlanner(Start, Target, PositionBounds, 5000, 2*Delta);
    HaveFoundSolution = true;
    return 0;
}
/**
 * @brief stop the thread
 */
void FPASOWorker::Stop()
{
    StopTaskCounter.Increment();
}
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
FPASOWorker* FPASOWorker::PASOInit(int NParts, int NIts, int NDims, int Try,
                                   std::vector<std::pair<float,float> > PBounds,
                                   std::vector<std::pair<float,float> > VBounds, float D,
                                   std::function<float(PSOParticle,std::vector<float>,std::vector<float>)> Fit,
                                   std::function<bool(std::vector<float>)> SV,
                                   std::function<float(std::vector<float>,std::vector<float>)> Dis,
                                   std::vector<float> St,
                                   std::vector<float> Tar,
                                   std::vector<std::vector<float> >& SPos,
                                   float* SFitnessValue) {
    //Create new instance of thread if it does not exist
    //		and the platform supports multi threading!
    if (!Runnable && FPlatformProcess::SupportsMultithreading())
    {
        Runnable = new FPASOWorker(NParts, NIts, NDims, Try, PBounds, VBounds, D, Fit, SV, Dis, St, Tar, SPos, SFitnessValue);
    }
    return Runnable;
}
/**
 * @brief ensure the completion of the thread
 */
void FPASOWorker::EnsureCompletion()
{
    Stop();
    Thread->WaitForCompletion();
}
/**
 * @brief shutdown the thread
 */
void FPASOWorker::Shutdown()
{
    if (Runnable)
    {
        Runnable->EnsureCompletion();
        delete Runnable;
        Runnable = NULL;
    }
}
/**
 * @brief is the thread finished?
 * @return true if thread finished, false otherwise
 */
bool FPASOWorker::IsThreadFinished()
{
    if(Runnable) return Runnable->IsFinished();
    return true;
}
