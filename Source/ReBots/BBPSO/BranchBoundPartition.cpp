// Fill out your copyright notice in the Description page of Project Settings.

 
#include "BranchBoundPartition.h"

/**
 * @brief constructor
 */
BranchBoundPartition::BranchBoundPartition() {
    Seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator = std::mt19937(Seed);
}
/**
 * @brief set lower bound
 * @param L lower bound
 */
void BranchBoundPartition::SetLowerBound(float L) {
    this->LowerBoundValue = L;
}
/**
 * @brief get lower bound
 * @return lower bound
 */
float BranchBoundPartition::GetLowerBound() {
    return this->LowerBoundValue;
}
/**
 * @brief set upper bound
 * @param L upper bound
 */
void BranchBoundPartition::SetUpperBound(float U) {
    this->UpperBoundValue = U;
}
/**
 * @brief get upper bound
 * @return upper bound
 */
float BranchBoundPartition::GetUpperBound() {
    return this->UpperBoundValue;
}
/**
 * @brief set partition active
 * @param PA partition active
 */
void BranchBoundPartition::SetPartitionActive(bool PA) {
    this->Active = PA;
}
/**
 * @brief get is partition active
 * @return is partition active
 */
bool BranchBoundPartition::GetPartitionActive() {
    return this->Active;
}
/**
 * @brief set bounds per dimension
 * @param BoundsDim bounds per dimension
 */
void BranchBoundPartition::SetBoundsPerDimension(std::vector<std::pair<float,float> > BoundsDim) {
    this->BoundsPerDimension = BoundsDim;
}
/**
 * @brief get bounds per dimension
 * @return bounds per dimension
 */
std::vector<std::pair<float,float> > BranchBoundPartition::GetBoundsPerDimension() {
    return this->BoundsPerDimension;
}
/**
 * @brief set Bounds of partition
 * @param bounds
 */
void BranchBoundPartition::SetPartitionExtents(std::vector<float> E) {
    this->Extents = E;
}
/**
 * @brief get partition bounds
 * @return partition bounds
 */
std::vector<float> BranchBoundPartition::GetPartitionExtents() {
    return this->Extents;
}
/**
 * @brief set Bounds of partition
 * @param bounds
 */
void BranchBoundPartition::SetPartitionCenter(std::vector<float> C) {
    this->Center = C;
}
/**
 * @brief get partition bounds
 * @return partition bounds
 */
std::vector<float> BranchBoundPartition::GetPartitionCenter() {
    return this->Center;
}
/**
 * @brief set dimension
 * @param Dim dimension
 */
void BranchBoundPartition::SetDimension(int Dim) {
    this->Dimension = Dim;
}
/**
 * @brief get dimension
 * @return dimension
 */
int BranchBoundPartition::GetDimension() {
    return this->Dimension;
}
/**
 * @brief create new partitions with the given rule
 * @param Rule branching rule
 */
std::vector<BranchBoundPartition*> BranchBoundPartition::CreatePartitionsWithRule(BranchingRule Rule) {
    std::vector<BranchBoundPartition*> NewPartitions;
    if (Rule == TWO_SPLIT) {
        std::uniform_int_distribution<> RandomDim(0,this->Dimension - 1);
        int RandomDimension = RandomDim(Generator);
        std::vector<std::pair<float, float> > Bounds1 = this->BoundsPerDimension;
        std::vector<std::pair<float, float> > Bounds2 = this->BoundsPerDimension;
        float LowBound = this->BoundsPerDimension[RandomDimension].first;
        float HighBound = this->BoundsPerDimension[RandomDimension].second;
        float Mid = (LowBound + HighBound)/2.0;
        Bounds1[RandomDimension].first = LowBound;
        Bounds1[RandomDimension].second = Mid;
        Bounds2[RandomDimension].first = Mid;
        Bounds2[RandomDimension].second = HighBound;
        int B1ID = CurrentPartitionNumber + 1;
        int B2ID = CurrentPartitionNumber + 2;
        CurrentPartitionNumber = CurrentPartitionNumber + 2;
        BranchBoundPartition *B1 = new BranchBoundPartition();
        B1->SetDimension(this->Dimension);
        B1->SetPartitionActive(true);
        B1->SetBoundsPerDimension(Bounds1);
        B1->SetPartitionID(B1ID);
        std::vector<float> B1Center = this->Center;
        std::vector<float> B1Extents = this->Extents;
        B1Extents[RandomDimension] = B1Extents[RandomDimension]/2.0;
        B1Center[RandomDimension] = (Bounds1[RandomDimension].first + Bounds1[RandomDimension].second)/2.0;
        B1->SetPartitionExtents(B1Extents);
        B1->SetPartitionCenter(B1Center);
        BranchBoundPartition *B2 = new BranchBoundPartition();
        B2->SetDimension(this->Dimension);
        B2->SetPartitionActive(true);
        B2->SetBoundsPerDimension(Bounds2);
        B2->SetPartitionID(B2ID);
        std::vector<float> B2Center = this->Center;
        std::vector<float> B2Extents = this->Extents;
        B2Extents[RandomDimension] = B2Extents[RandomDimension]/2.0;
        B2Center[RandomDimension] = (Bounds2[RandomDimension].first + Bounds2[RandomDimension].second)/2.0;
        B2->SetPartitionExtents(B2Extents);
        B2->SetPartitionCenter(B2Center);
        NewPartitions.push_back(B1);
        NewPartitions.push_back(B2);
    }
    return NewPartitions;
}
/**
 * @brief set partition id
 * @param IDN id number of partition
 */
void BranchBoundPartition::SetPartitionID(int IDN) {
    this->IDNumber = IDN;
}
/**
 * @brief get partition id
 * @return id number of partition
 */
int BranchBoundPartition::GetPartitionID() {
    return this->IDNumber;
}
/**
 * @brief print partition bounds
 */
void BranchBoundPartition::PrintPartition() {
    std::cout<<"Partition ID: "<<this->IDNumber<<std::endl;
    for (int i=0; i<this->Dimension; i++) {
        std::cout<<"Dimension: "<<(i + 1)<<"; L: "<<this->BoundsPerDimension[i].first<<"; H: "<<this->BoundsPerDimension[i].second<<std::endl;
    }
    std::cout<<"Center: ";
    for (int i=0; i<this->Dimension; i++) {
        std::cout<<this->Center[i];
        if (i < this->Dimension - 1) cout<<",";
    }
    cout<<endl;
    std::cout<<"Extents: ";
    for (int i=0; i<this->Dimension; i++) {
        std::cout<<this->Extents[i];
        if (i < this->Dimension - 1) cout<<",";
    }
    cout<<endl;
    
    
}
/**
 * @brief destructor
 */
BranchBoundPartition::~BranchBoundPartition() {}

int BranchBoundPartition::CurrentPartitionNumber = 0; /**< current partition number for splitting */
