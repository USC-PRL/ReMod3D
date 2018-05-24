// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include <random>
#include <utility>
#include <iostream>
using namespace std;
/**
 * @enum Branching rule
 * @brief branch and bound BBPSO branching rule (how many and how to produce branches)
 */
enum BranchingRule {
    TWO_SPLIT,
    TWO_TO_D_SPLIT,
};
/**
 * @class BranchBoundPartition
 * @brief branch and bound partition for BBPSO
 */
class REBOTS_API BranchBoundPartition
{
private:
    bool Active; /**< is partition active ? */
    int Dimension; /**< dimensionality of partition */
    int IDNumber; /**< id of partition */
    float LowerBoundValue; /**< Lower bound value */
    float UpperBoundValue; /**< upper bound value */
    std::vector<std::pair<float,float> > BoundsPerDimension; /**< bounds for each dimension */
    unsigned Seed; /**< r seed value */
    std::mt19937 Generator; /**< random number generator */
    std::vector<float> Extents; /**< bounds of the partition */
    std::vector<float> Center; /**< center of the partition */
    static int CurrentPartitionNumber; /**< current partition number for splitting */
public:
    /**
     * @brief constructor
     */
	BranchBoundPartition();
    /**
     * @brief set lower bound
     * @param L lower bound
     */
    void SetLowerBound(float L);
    /**
     * @brief get lower bound
     * @return lower bound
     */
    float GetLowerBound();
    /**
     * @brief set upper bound
     * @param L upper bound
     */
    void SetUpperBound(float U);
    /**
     * @brief get upper bound
     * @return upper bound
     */
    float GetUpperBound();
    /**
     * @brief set partition id
     * @param IDN id number of partition
     */
    void SetPartitionID(int IDN);
    /**
     * @brief get partition id
     * @return id number of partition
     */
    int GetPartitionID();
    /**
     * @brief set Bounds of partition
     * @param bounds
     */
    void SetPartitionExtents(std::vector<float> E);
    /**
     * @brief get partition bounds
     * @return partition bounds
     */
    std::vector<float> GetPartitionExtents();
    /**
     * @brief set Bounds of partition
     * @param bounds
     */
    void SetPartitionCenter(std::vector<float> C);
    /**
     * @brief get partition bounds
     * @return partition bounds
     */
    std::vector<float> GetPartitionCenter();
    /**
     * @brief set partition active 
     * @param PA partition active
     */
    void SetPartitionActive(bool PA);
    /**
     * @brief get is partition active
     * @return is partition active
     */
    bool GetPartitionActive();
    /**
     * @brief set bounds per dimension
     * @param BoundsDim bounds per dimension
     */
    void SetBoundsPerDimension(std::vector<std::pair<float,float> > BoundsDim);
    /**
     * @brief get bounds per dimension
     * @return bounds per dimension
     */
    std::vector<std::pair<float,float> > GetBoundsPerDimension();
    /**
     * @brief set dimension 
     * @param Dim dimension
     */
    void SetDimension(int Dim);
    /**
     * @brief get dimension
     * @return dimension
     */
    int GetDimension();
    /**
     * @brief create new partitions with the given rule
     * @param Rule branching rule
     */
    std::vector<BranchBoundPartition*> CreatePartitionsWithRule(BranchingRule Rule = TWO_SPLIT);
    /**
     * @brief print partition bounds
     */
    void PrintPartition();
    /**
     * @brief destructor
     */
	~BranchBoundPartition();
};
