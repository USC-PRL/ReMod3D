 
#include "BranchBoundPSO.h"
#include <chrono>
/**
 * @brief constructor
 */
BranchBoundPSO::BranchBoundPSO(){}
/**
 * @brief constructor
 * @param NumP number of particles
 * @param NumIt number of iterations
 * @param NumDim number of dimensions
 */
BranchBoundPSO::BranchBoundPSO(int NumP, int NumIt, int NumDim){
    this->NumParticles = NumP;
    this->NumIterations = NumIt;
    this->NumDimensions = NumDim;
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
}
/**
 * @brief destructor
 */
BranchBoundPSO::~BranchBoundPSO(){}
/**
 * @brief initialize PSO BB procedure
 * @param PosB position bounds
 * @param VelB velocity bounds
 * @param D delta
 * @param F fitness function
 * @param st start vector
 * @param tar target vector
 */
void BranchBoundPSO::InitializeBBPSO(std::vector<std::pair<float, float> > PosB, std::vector<std::pair<float, float> > VelB, float D,
                                     std::function<float(BranchBoundParticle,std::vector<float>,std::vector<float>)> F, std::vector<float> st, std::vector<float> tar) {
    this->PosBounds = PosB;
    this->VelBounds = VelB;
    this->Delta = D;
    this->Fitness = F;
    this->Target = tar;
    this->Start = st;
    BranchBoundPartition* RootPartition = new BranchBoundPartition();
    RootPartition->SetBoundsPerDimension(PosBounds);
    RootPartition->SetDimension(this->NumDimensions);
    RootPartition->SetLowerBound(0.0);
    RootPartition->SetUpperBound(-1.0);
    RootPartition->SetPartitionActive(true);
    RootPartition->SetPartitionID(0);
    std::vector<float> CenterPoint(PosB.size());
    std::vector<float> Extents(PosB.size());
    for (int i=0; i<PosB.size(); i++) {
        CenterPoint[i] = (PosB[i].second - PosB[i].first)/2.0;
        Extents[i] = (PosB[i].second - PosB[i].first)/2.0;
    }
    RootPartition->SetPartitionCenter(CenterPoint);
    RootPartition->SetPartitionExtents(Extents);
    ActivePartitions.push_back(RootPartition);
    
}
/**
 * @brief compute velocity bounds for position bounds
 * @param PBounds position bounds
 * @return velocity bounds
 */
std::vector<std::pair<float,float> > BranchBoundPSO::ComputeVelocityBoundsForPositionBounds(std::vector<std::pair<float,float> > PBounds) {
    std::vector<std::pair<float,float> > VelocityBounds(PBounds.size());
    for (int i=0; i<PBounds.size(); i++) {
        float maxVal = fmax(fabs(PBounds[i].first), fabs(PBounds[i].second));
        VelocityBounds[i] = std::pair<float,float>(-maxVal, maxVal);
    }
    return VelocityBounds;
}
/**
 * @brief branch the given partition
 * @param P partition
 */
void BranchBoundPSO::BranchPartition(BranchBoundPartition* P) {
    std::vector<BranchBoundPartition*> NewPartitions = P->CreatePartitionsWithRule();
    UpdatePartitionLists(P, NewPartitions);
}
/**
 * @brief update partition lists to deactive old partition and active the two new partitions in its place
 * @param parentp parent partition
 * @param childrenp children partitions
 */
void BranchBoundPSO::UpdatePartitionLists(BranchBoundPartition *ParentP, std::vector<BranchBoundPartition*> ChildrenP) {
    InactivePartitions.push_back(ParentP);
    ParentP->SetPartitionActive(false);
    for (int i=0; i<ChildrenP.size(); i++) {
        ActivePartitions.push_back(ChildrenP[i]);
    }
    int partitionToRemove = -1;
    for (int i=0; i<ActivePartitions.size(); i++) {
        if (!ActivePartitions[i]->GetPartitionActive()) {
            partitionToRemove = i;
            break;
        }
    }
    if (partitionToRemove != -1) {
        ActivePartitions.erase(ActivePartitions.begin() + partitionToRemove);
    }
    if (DebugPrint) {
        cout<<"Remaining active partitions: "<<ActivePartitions.size()<<endl;
    }
}
/**
 * @brief bound active partition at index
 * @param i index
 * @return best particle
 *
 */
void BranchBoundPSO::BoundPartitionAtIndex(int i) {
    BranchBoundParticleSwarm BPS = BranchBoundParticleSwarm(this->NumParticles, this->NumIterations, this->NumDimensions);
    BPS.InitializeSwarm(ActivePartitions[i]->GetBoundsPerDimension(),
                        ComputeVelocityBoundsForPositionBounds(ActivePartitions[i]->GetBoundsPerDimension()),
                        this->Delta, this->Fitness, this->Start, this->Target, BestGlobalBestParticle, true);
    BranchBoundParticle GBP = BPS.Optimize();
    if (BPS.GetGlobalBestFitness() < CurrentUpperBound) {
        CurrentUpperBound = BPS.GetGlobalBestFitness();
        BestGlobalBestParticle = GBP;
		CurrentBestPartition = i;
    }
    if (DebugPrint) {cout<<"Current Upper Bound: "<<CurrentUpperBound<<endl;}
}
/**
 * @brief optimize using Branch and bound PSO
 */
void BranchBoundPSO::BBPSOOptimize() {
    CurrentUpperBound = std::numeric_limits<float>::max();
    CurrentLowerBound = 0;
    start_time = clock();
    //When difference between current upper bound (best known solution) and current lower bound (known minimum) sufficiently close, we break out of loop
    while ((CurrentUpperBound - CurrentLowerBound) >= Delta && (clock() - start_time)/CLOCKS_PER_SEC < TimeLimitSeconds && ActivePartitions.size() > 0) {
        if (DebugPrint) {
            cout<<"BBPSO: Number of active partions: "<<ActivePartitions.size()<<endl;
            for (int i=0; i<ActivePartitions.size(); i++) {
                ActivePartitions[i]->PrintPartition();
            }
        }
        for (int i=0; i<ActivePartitions.size(); i++) {
            //Bound each partition
            BoundPartitionAtIndex(i);
        }
        if ((CurrentUpperBound - CurrentLowerBound) < Delta) break;
		uniform_real_distribution<> randNum(0, 1);
		int RandPartitionIndex = -1;
		if (randNum(Generator) < BestPartitionBias && CurrentUpperBound < 100.0) {
			RandPartitionIndex = CurrentBestPartition;
		}
		else {
			uniform_int_distribution<> randPartition(0, ActivePartitions.size() - 1);
			RandPartitionIndex = randPartition(Generator);
			//Choose partition to split and branch two new partitions
		}
        BranchPartition(ActivePartitions[RandPartitionIndex]);
        StepCount++;
    }
}
/**
 * @brief perform one step of BBPSO
 * @return true if finished, false otherwise
 */
bool BranchBoundPSO::BBPSOOptimizeStep() {

    if (StepCount == 0) {
        CurrentUpperBound = std::numeric_limits<float>::max();
        CurrentLowerBound = 0;
        start_time = clock();
    }
    StepCount++;
    if ((CurrentUpperBound - CurrentLowerBound) >= Delta && (clock() - start_time)/CLOCKS_PER_SEC < TimeLimitSeconds && ActivePartitions.size() > 0) {
        if (DebugPrint) {
            cout<<"BBPSO: Number of active partions: "<<ActivePartitions.size()<<endl;
            for (int i=0; i<ActivePartitions.size(); i++) {
                ActivePartitions[i]->PrintPartition();
            }
        }
        for (int i=0; i<ActivePartitions.size(); i++) {
            //Bound each partition
            BoundPartitionAtIndex(i);
        }
        if ((CurrentUpperBound - CurrentLowerBound) < Delta) {return true;}
        uniform_int_distribution<> randPartition(0,ActivePartitions.size() - 1);
        int RandPartitionIndex = randPartition(Generator);
        //Choose partition to split and branch two new partitions
        BranchPartition(ActivePartitions[RandPartitionIndex]);
        return false;
    } else {
        return true;
    }
    
}
/**
 * @brief get final optimization solution
 * @return final best particle
 */
BranchBoundParticle BranchBoundPSO::GetFinalSolution() {
    return this->BestGlobalBestParticle;
}
/**
 * @brief get time limit in seconds
 * @return time limit in seconds
 */
int BranchBoundPSO::GetTimeLimitSeconds() {
    return this->TimeLimitSeconds;
}
/**
 * @brief get partition limit
 * @return partition limit
 */
int BranchBoundPSO::GetPartitionLimit() {
    return this->PartitionLimit;
}
/**
 * @brief get delta value
 * @return delta value
 */
float BranchBoundPSO::GetDelta() {
    return this->Delta;
}
/**
 * @brief get current lower bound
 * @return lower bound
 */
float BranchBoundPSO::GetCurrentLowerBound() {
    return this->CurrentLowerBound;
}
/**
 * @brief get current upper bound
 * @return upper bound
 */
float BranchBoundPSO::GetCurrentUpperBound() {
    return this->CurrentUpperBound;
}
/**
 * @brief set time limit in seconds
 * @param TL limit in seconds
 */
void BranchBoundPSO::SetTimeLimitSeconds(int TL) {
    this->TimeLimitSeconds = TL;
}
/**
 * @brief set partition limit
 * @param PL partition limit
 */
void BranchBoundPSO::SetPartitionLimit(int PL) {
    this->PartitionLimit = PL;
}
/**
 * @brief get number of active partitions
 * @return number of active partitions
 */
int BranchBoundPSO::GetNumActivePartitions() {
    return this->ActivePartitions.size();
}
/**
 * @brief set delta value
 * @param D delta value
 */
void BranchBoundPSO::SetDelta(float D) {
    this->Delta = D;
}
/**
 * @brief set current lower bound
 * @param LB lower bound
 */
void BranchBoundPSO::SetCurrentLowerBound(float LB) {
    this->CurrentLowerBound = LB;
}
/**
 * @brief set current upper bound
 * @param UB upper bound
 */
void BranchBoundPSO::SetCurrentUpperBound(float UB) {
    this->CurrentUpperBound = UB;
}
