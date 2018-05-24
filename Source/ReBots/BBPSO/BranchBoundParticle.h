// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
#include <map>
#include <utility>
#include "PSO/PSOParticleFitness.h"
using namespace std;
/**
 * @class BranchBoundParticle
 * @brief branch bound particle implementation for BBPSO
 */
class REBOTS_API BranchBoundParticle
{
private:
    std::vector<float> Position; /**< Position of particle currently */
    std::vector<float> BestPosition; /**< Best Position of particle ever reached */
    std::vector<float> Velocity; /**< velocity of particle */
    std::vector<std::pair<float, float> > PositionBound; /**< position bound of particle */
    std::vector<std::pair<float, float> > VelocityBound; /**< velocity bound of particle */
    int Dimension; /**< dimensionality of search space */
    PSOParticleFitness Fitness; /**< fitness of particle */
public:
    /**
     * @brief constructor
     */
	BranchBoundParticle();
    /**
     * @brief constructor
     * @param Pos position of particle
     * @param Vel velocity of particle
     * @param Dim dimension of particle
     */
    BranchBoundParticle(std::vector<float> Pos, std::vector<float> Vel, int Dim);
    /**
     * @brief constructor
     * @param Pos position of particle
     * @param Vel velocity of particle
     * @param PosBound position bound of particle
     * @param VelBound velocity bound of particle
     * @param Dim dimension of particle
     */
    BranchBoundParticle(std::vector<float> Pos, std::vector<float> Vel, std::vector<std::pair<float,float> > PosBound,
                        std::vector<std::pair<float,float> > VelBound, int Dim);
    /**
     * @brief set position at index
     * @param P position 
     * @param i index
     */
    void SetPositionAtIndex(float P, int i);
    /**
     * @brief set velocity at index
     * @param V position
     * @param i index
     */
    void SetVelocityAtIndex(float V, int i);
    /**
     * @brief set best position at index
     * @param BP best position
     * @parma i index
     */
    void SetBestPositionAtIndex(float BP, int i);
    /**
     * @brief set position of particle
     * @param Pos position of particle
     */
    void SetPosition(std::vector<float> Pos);
    /**
     * @brief get position of particle
     * @return position of particle
     */
    std::vector<float> GetPosition();
    /**
     * @brief set velocity of particle
     * @param Vel velocity of particle
     */
    void SetVelocity(std::vector<float> Vel);
    /**
     * @brief get velocity of particle
     * @return velocity of particle
     */
    std::vector<float> GetVelocity();
    /**
     * @brief set best position of particle
     * @param BP best position of particle
     */
    void SetBestPosition(std::vector<float> BP);
    /**
     * @brief get best position of particle
     * @return best position of particle
     */
    std::vector<float> GetBestPosition();
    /**
     * @brief set particle position bound 
     * @param PosBound position bound of particle
     * @param index index of Pos bound
     */
    void SetPositionBoundForIndex(std::pair<float,float> PosBound, int index);
    /**
     * @brief return position bound
     * @return position bound of particle
     */
    std::vector<std::pair<float,float> > GetPositionBounds();
    /**
     * @brief set velocity bound
     * @param VelBound velocity bound
     */
    void SetVelocityBoundForIndex(std::pair<float,float> VelBound, int index);
    /**
     * @brief set velocity bound
     * @param VelBound velocity bound
     */
    void SetVelocityBounds(std::vector<std::pair<float,float> > VelBound);
    /**
     * @brief set position bound
     * @param PosBound position bound
     */
    void SetPositionBounds(std::vector<std::pair<float,float> > PosBound);
    /**
     * @brief get velocity bound
     * @return velocity bound
     */
    std::vector<std::pair<float,float> > GetVelocityBounds();
    /**
     * @brief set dimension
     * @param Dim dimension of particle
     */
    void SetDimension(int Dim);
    /**
     * @brief get particle dimension 
     * @return particle dimension
     */
    int GetDimension();
    /**
     * @brief Set fitness
     * @param FitVal fitness
     */
    void SetFitness(PSOParticleFitness Fit);
    /**
     * @brief get fitness
     * @return particle fitness
     */
    PSOParticleFitness GetFitness();
    /**
     * @brief clamp positions to bounds
     */
    void ClampPositionToBounds();
    /**
     * @brief clamp velocities to bounds
     */
    void ClampVelocityToBounds();
    /**
     * @brief destructor
     */
	~BranchBoundParticle();
};
