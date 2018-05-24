// Fill out your copyright notice in the Description page of Project Settings.

 
#include "PSOParticleFitness.h"
/**
 * @brief constructor
 */
PSOParticleFitness::PSOParticleFitness(){
    this->FitnessValue = -1;
    this->ParticleValid = false;
}
/**
 * @brief constructor
 * @param FV fitness value
 * @param PV particle valid?
 */
PSOParticleFitness::PSOParticleFitness(float FV, bool PV) {
    this->FitnessValue = FV;
    this->ParticleValid = PV;
}
/**
 * @brief get the fitness value
 * @return fitness value
 */
float PSOParticleFitness::GetFitnessValue() {return this->FitnessValue;}
/**
 * @brief get particle valid
 * @return particle valid
 */
bool PSOParticleFitness::GetParticleValid() {return this->ParticleValid;}
/**
 * @brief set particle fitness value
 * @param FV fitness value
 */
void PSOParticleFitness::SetFitnessValue(float FV) {this->FitnessValue = FV;}
/**
 * @brief set particle valid
 * @param PV particle valid
 */
void PSOParticleFitness::SetParticleValid(bool PV) {this->ParticleValid = PV;}
/**
 * @brief destructor
 */
PSOParticleFitness::~PSOParticleFitness(){}
