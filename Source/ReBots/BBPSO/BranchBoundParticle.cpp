// Fill out your copyright notice in the Description page of Project Settings.

 
#include "BranchBoundParticle.h"
#include <math.h>

/**
 * @brief constructor
 */
BranchBoundParticle::BranchBoundParticle() {this->Dimension = 0;}
/**
 * @brief constructor
 * @param Pos position of particle
 * @param Vel velocity of particle
 * @param Dim dimension of particle
 */
BranchBoundParticle::BranchBoundParticle(std::vector<float> Pos, std::vector<float> Vel, int Dim) {
    this->Position = Pos;
    this->BestPosition = Pos;
    this->Velocity = Vel;
    this->Dimension = Dim;
    this->PositionBound = std::vector<std::pair<float, float> >(this->Dimension);
    this->VelocityBound = std::vector<std::pair<float, float> >(this->Dimension);
}
/**
 * @brief constructor
 * @param Pos position of particle
 * @param Vel velocity of particle
 * @param PosBound position bound of particle
 * @param VelBound velocity bound of particle
 * @param Dim dimension of particle
 */
BranchBoundParticle::BranchBoundParticle(std::vector<float> Pos, std::vector<float> Vel, std::vector<std::pair<float,float> > PosBound,
                                         std::vector<std::pair<float,float> > VelBound, int Dim) {
    this->Position = Pos;
    this->PositionBound = PosBound;
    this->BestPosition = Pos;
    this->Velocity = Vel;
    this->VelocityBound = VelBound;
    this->Dimension = Dim;
}
/**
 * @brief clamp positions to bounds
 */
void BranchBoundParticle::ClampPositionToBounds() {
    for (int i=0; i<this->Dimension; i++) {
        this->Position[i] = fmin(fmax(this->PositionBound[i].first, this->Position[i]),this->PositionBound[i].second);
        this->BestPosition[i] = fmin(fmax(this->PositionBound[i].first, this->BestPosition[i]),this->PositionBound[i].second);
    }
}
/**
 * @brief clamp velocities to bounds
 */
void BranchBoundParticle::ClampVelocityToBounds() {
    for (int i=0; i<this->Dimension; i++) {
        this->Velocity[i] = fmin(fmax(this->VelocityBound[i].first, this->Velocity[i]),this->VelocityBound[i].second);
    }
}
/**
 * @brief set best position at index
 * @param BP best position
 * @parma i index
 */
void BranchBoundParticle::SetBestPositionAtIndex(float BP, int i) {
    this->BestPosition[i] = BP;
}
/**
 * @brief set position of particle
 * @param Pos position of particle
 */
void BranchBoundParticle::SetPosition(std::vector<float> Pos) {
    this->Position = Pos;
}
/**
 * @brief get position of particle
 * @return position of particle
 */
std::vector<float> BranchBoundParticle::GetPosition() {
    return this->Position;
}
/**
 * @brief set velocity of particle
 * @param Vel velocity of particle
 */
void BranchBoundParticle::SetVelocity(std::vector<float> Vel) {
    this->Velocity = Vel;
}
/**
 * @brief get velocity of particle
 * @return velocity of particle
 */
std::vector<float> BranchBoundParticle::GetVelocity() {
    return this->Velocity;
}
/**
 * @brief set particle position bound
 * @param PosBound position bound of particle
 */
void BranchBoundParticle::SetPositionBounds(std::vector<std::pair<float,float> > PosBound) {
    this->PositionBound = PosBound;
}
/**
 * @brief return position bound
 * @return position bound of particle
 */
std::vector<std::pair<float,float> > BranchBoundParticle::GetPositionBounds() {
    return this->PositionBound;
}
/**
 * @brief set velocity bound
 * @param VelBound velocity bound
 */
void BranchBoundParticle::SetVelocityBounds(std::vector<std::pair<float,float> > VelBound) {
    this->VelocityBound = VelBound;
}
/**
 * @brief get velocity bound
 * @return velocity bound
 */
std::vector<std::pair<float,float> > BranchBoundParticle::GetVelocityBounds() {
    return this->VelocityBound;
}
/**
 * @brief set dimension
 * @param Dim dimension of particle
 */
void BranchBoundParticle::SetDimension(int Dim) {
    this->Dimension = Dim;
}
/**
 * @brief get particle dimension
 * @return particle dimension
 */
int BranchBoundParticle::GetDimension() {
    return this->Dimension;
}
/**
 * @brief Set fitness
 * @param FitVal fitness
 */
void BranchBoundParticle::SetFitness(PSOParticleFitness Fit) {
    this->Fitness = Fit;
}
/**
 * @brief get fitness
 * @return particle fitness
 */
PSOParticleFitness BranchBoundParticle::GetFitness() {
    return this->Fitness;
}
/**
 * @brief set best position of particle
 * @param BP best position of particle
 */
void BranchBoundParticle::SetBestPosition(std::vector<float> BP) {
    this->BestPosition = BP;
}
/**
 * @brief get best position of particle
 * @return best position of particle
 */
std::vector<float> BranchBoundParticle::GetBestPosition() {
    return this->BestPosition;
}
/**
 * @brief set particle position bound
 * @param PosBound position bound of particle
 * @param index index of Pos bound
 */
void BranchBoundParticle::SetPositionBoundForIndex(std::pair<float,float> PosBound, int index) {
    this->PositionBound[index] = PosBound;
}
/**
 * @brief set velocity bound
 * @param VelBound velocity bound
 */
void BranchBoundParticle::SetVelocityBoundForIndex(std::pair<float,float> VelBound, int index) {
    this->VelocityBound[index] = VelBound;
}
/**
 * @brief set position at index
 * @param P position
 * @param i index
 */
void BranchBoundParticle::SetPositionAtIndex(float P, int i) {
    this->Position[i] = P;
}
/**
 * @brief set velocity at index
 * @param V position
 * @param i index
 */
void BranchBoundParticle::SetVelocityAtIndex(float V, int i) {
    this->Velocity[i] = V;
}
/**
 * @brief destructor
 */
BranchBoundParticle::~BranchBoundParticle() {}
