// Fill out your copyright notice in the Description page of Project Settings.

 
#include "FBBPSOWorker.h"

//***********************************************************
//Thread Worker Starts as NULL, prior to being instanced
//		This line is essential! Compiler error without it
FBBPSOWorker* FBBPSOWorker::Runnable = NULL;
//***********************************************************

FBBPSOWorker::FBBPSOWorker(int NParts, int NIts, int NDims,
                           std::vector<std::pair<float,float> > PBounds, std::vector<std::pair<float,float> > VBounds, float D,
                           std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F, std::vector<float> St, std::vector<float> Tar,
                           std::vector<float>& SPos, float* SFitnessValue)
:SolutionPosition(SPos)
{
	this->ElapsedTime = 0.0;
    this->PositionBounds = PBounds;
    this->VelocityBounds = VBounds;
    this->Target = Tar;
    this->Start = St;
    this->NumParticlces = NParts;
    this->NumIterations = NIts;
    this->NumDimensions = NDims;
    this->Fitness = F;
    this->Delta = D;
    this->SolutionFitnessValue = SFitnessValue;
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
    std::uniform_int_distribution<> IDNumDist(0, std::numeric_limits<int>::max());
    FString WorkerFString = FString::Printf(TEXT("PSOWorker%d"), IDNumDist(Generator));
    this->Thread = FRunnableThread::Create(this, *WorkerFString, 0, TPri_Highest); //windows default = 8mb for thread, could specify more
}
/**
 * @brief destructor
 */
FBBPSOWorker::~FBBPSOWorker()
{
    delete Thread;
    Thread = NULL;
}
/**
* @brief get elapsed time
* @param elapsed time
*/
float FBBPSOWorker::GetElapsedTime() {
	return this->ElapsedTime;
	//auto end = std::chrono::steady_clock::now();
	//auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	//return elapsed.count();
}
/**
 * @brief get current upper bound
 * @return current upper bound
 */
float FBBPSOWorker::GetCurrentUpperBound() {
    return this->BBPSO.GetCurrentUpperBound();
}
//Init
bool FBBPSOWorker::Init()
{
    BBPSO = BranchBoundPSO(NumParticlces,NumIterations,NumDimensions);
    BBPSO.InitializeBBPSO(PositionBounds, VelocityBounds, Delta,
                          Fitness,Start,Target);
    cout<<"Initializing BBPSO On Separate Thread"<<endl;
    return true;
}

//Run
uint32 FBBPSOWorker::Run()
{
	time_t t1 = std::clock();
    BBPSO.BBPSOOptimize();
	time_t t2 = std::clock();
	ElapsedTime = (t2 - t1)/(double)CLOCKS_PER_SEC;
    SolutionPosition = BBPSO.GetFinalSolution().GetPosition();
    *SolutionFitnessValue = BBPSO.GetCurrentUpperBound();
    
    HaveFoundSolution = true;
    cout<<"Finished finding solution"<<endl;
    return 0;
}
/**
 * @brief get num active partitions
 * @return current num active partitions
 */
int FBBPSOWorker::GetNumActivePartitions() {
    return BBPSO.GetNumActivePartitions();
}
/**
 * @brief stop the thread
 */
void FBBPSOWorker::Stop()
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
FBBPSOWorker* FBBPSOWorker::BBPSOInit(int NParts, int NIts, int NDims,
                                      std::vector<std::pair<float,float> > PBounds, std::vector<std::pair<float,float> > VBounds, float D,
                                      std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F, std::vector<float> St, std::vector<float> Tar,
                                      std::vector<float>& SPos, float* SFitnessValue)
{
    //Create new instance of thread if it does not exist
    //		and the platform supports multi threading!
    if (!Runnable && FPlatformProcess::SupportsMultithreading())
    {
        Runnable = new FBBPSOWorker(NParts, NIts, NDims, PBounds, VBounds, D, F, St, Tar, SPos, SFitnessValue);
    }
    return Runnable;
}
/**
 * @brief ensure the completion of the thread
 */
void FBBPSOWorker::EnsureCompletion()
{
    Stop();
    Thread->WaitForCompletion();
}
/**
 * @brief shutdown the thread
 */
void FBBPSOWorker::Shutdown()
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
bool FBBPSOWorker::IsThreadFinished()
{
    if(Runnable) return Runnable->IsFinished();
    return true;
}
