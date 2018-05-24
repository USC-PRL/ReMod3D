// Fill out your copyright notice in the Description page of Project Settings.

 
#include "FRORTWorker.h"
//***********************************************************
//Thread Worker Starts as NULL, prior to being instanced
//		This line is essential! Compiler error without it
FRORTWorker* FRORTWorker::Runnable = NULL;
//***********************************************************
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
FRORTWorker::FRORTWorker(int NumStates, int NDims, int Try,
	std::vector<std::pair<float, float> > PBounds, float D,
	std::function<bool(std::vector<float>)> SV,
	std::function<float(std::vector<float>, std::vector<float>)> Dis,
	std::function<float(PSOParticle, std::vector<float>, std::vector<float>)> F,
	std::vector<float> St,
	std::vector<float> Tar,
	std::vector<std::vector<float> >& SPos,
	float* SFitnessValue) :SolutionPosition(SPos)
{
	this->PositionBounds = PBounds;
	this->MaxNumStates = NumStates;
	this->Target = Tar;
	this->TCLimit = Try;
	this->Start = St;
	this->StateV = SV;
	this->Dist = Dis;
	this->FitnessFunc = F;
	this->NumDimensions = NDims;
	this->Delta = D;
	this->SolutionFitnessValue = SFitnessValue;
	Seed = std::chrono::system_clock::now().time_since_epoch().count();
	Generator = std::mt19937(Seed);
	std::uniform_int_distribution<> IDNumDist(0, std::numeric_limits<int>::max());
	FString WorkerFString = FString::Printf(TEXT("RORTWorker%d"), IDNumDist(Generator));
	this->Thread = FRunnableThread::Create(this, *WorkerFString, 0, TPri_Highest);
}
int FRORTWorker::GetNumStatesOptimized() {
	return RORT.getNumStatesOptimized();
}
int FRORTWorker::GetNumStatesRandomized() {
	return RORT.getNumStatesRandomized();
}
float FRORTWorker::GetPathSize() {
	return RORT.getPathLength();
}
int FRORTWorker::GetGraphSize() {
	return RORT.getNumGraphNodes();
}
/**
* @brief destructor
*/
FRORTWorker::~FRORTWorker() {
	delete Thread;
	Thread = NULL;
}
/**
* @brief initialize thread
* @return whether or not initialization was succesful
*/
bool FRORTWorker::Init() {
	RORT = RORTTree(StateV, FitnessFunc);
	std::cout << "Initializing PASO On Separate Thread" << endl;
	return true;
}
/**
* @brief run thread
* @return return code (int)
*/
uint32 FRORTWorker::Run() {
	SolutionPosition = RORT.rortConnectPathPlanner(Start, Target, PositionBounds, MaxNumStates, Delta);
	HaveFoundSolution = true;
	return 0;
}
/**
* @brief stop the thread
*/
void FRORTWorker::Stop()
{
	StopTaskCounter.Increment();
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
FRORTWorker* FRORTWorker::RORTInit(int NumStates, int NDims, int Try,
	std::vector<std::pair<float, float> > PBounds, float D,
	std::function<bool(std::vector<float>)> SV,
	std::function<float(std::vector<float>, std::vector<float>)> Dis,
	std::function<float(PSOParticle, std::vector<float>, std::vector<float>)> F,
	std::vector<float> St,
	std::vector<float> Tar,
	std::vector<std::vector<float> >& SPos,
	float* SFitnessValue) {
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FRORTWorker(NumStates, NDims, Try, PBounds, D, SV, Dis, F, St, Tar, SPos, SFitnessValue);
	}
	return Runnable;
}
/**
* @brief ensure the completion of the thread
*/
void FRORTWorker::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}
/**
* @brief shutdown the thread
*/
void FRORTWorker::Shutdown()
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
bool FRORTWorker::IsThreadFinished()
{
	if (Runnable) return Runnable->IsFinished();
	return true;
}
