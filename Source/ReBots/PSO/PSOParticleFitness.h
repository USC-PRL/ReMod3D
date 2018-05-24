#pragma once

/**
 * @class PSOParticleFitness
 * @brief pso particle fitness
 */
class REBOTS_API PSOParticleFitness
{
private:
    float FitnessValue; /**< associated fitness value */
    bool ParticleValid; /**< is the particle valid according to constraints */
public:
    /**
     * @brief constructor
     */
	PSOParticleFitness();
    /**
     * @brief constructor
     * @param FV fitness value
     * @param PV particle valid?
     */
    PSOParticleFitness(float FV, bool PV);
    /**
     * @brief get the fitness value
     * @return fitness value
     */
    float GetFitnessValue();
    /**
     * @brief get particle valid
     * @return particle valid
     */
    bool GetParticleValid();
    /**
     * @brief set particle fitness value
     * @param FV fitness value
     */
    void SetFitnessValue(float FV);
    /**
     * @brief set particle valid
     * @param PV particle valid
     */
    void SetParticleValid(bool PV);
    /**
     * @brief destructor
     */
	~PSOParticleFitness();
};
