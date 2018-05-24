#pragma once
#include <vector>
#include "PSOParticleFitness.h"
#include <utility>
/**
 * @class PSOParticle
 * @brief pso particle 
 */
class REBOTS_API PSOParticle {
private:
    std::vector<float> position; /**< position of particle */
    std::vector<float> velocity; /**< velocity of particle */
    int dim; /**< dimension of particle */
	bool isInCollision; /**< is particle in collision */
public:
    /**
     * @brief default constructor
     */
    PSOParticle();
    /**
     * @brief constructor
     * @param dimension dimensionality of particle
     * @param pos initial position of particle
     * @param vel initial velocity of particle
     */
    PSOParticle(int dimension, std::vector<float> pos, std::vector<float> vel);
    /**
     * @brief constructor (copy)
     * @param p another particle whose position, dimensionality, and velocity will be copied to make this new particle
     */
    PSOParticle(PSOParticle const &p);
    /**
     * @brief set position of particle
     * @param p new position value
     * @param i index of position vector into which to place new value
     */
    void setPositionAtIndex(float p, int i);
    /**
     * @brief get position of particle
     * @param i index of particle position vector
     * @return position of particle at index i
     */
    float getPositionAtIndex(int i);
    /**
     * @brief set velocity of particle
     * @param v new velocity value
     * @param i index of velocity vector into which to place new value
     */
    void setVelocityAtIndex(float v, int i);
    /**
     * @brief get velocity of particle
     * @param i index of particle velocity vector
     * @return velocity of particle at index i
     */
    float getVelocityAtIndex(int i);
    /**
     * @brief get position of particle
     * @return position vector of particle
     */
    std::vector<float> getPosition();
    /**
     * @brief get velocity of particle
     * @return velocity vector of particle
     */
    std::vector<float> getVelocity();
	/**
	* @brief set particle is in collision
	* @param iic is in collision
	*/
	void setIsInCollision(bool iic);
	/**
	* @brief get is particle in collision
	* @return is particle in collision
	*/
	bool getIsInCollision();

};
