 
#include "PSOParticle.h"
/**
 * @brief default constructor
 */
PSOParticle::PSOParticle() {
    this->dim = 0;
	this->isInCollision = false;
}
/**
 * @brief constructor
 * @param dimension dimensionality of particle
 * @param pos initial position of particle
 * @param vel initial velocity of particle
 */
PSOParticle::PSOParticle(int dimension, std::vector<float> pos, std::vector<float> vel) {
    this->dim = dimension;
	this->isInCollision = false;
    this->position = std::vector<float>(this->dim);
    this->velocity = std::vector<float>(this->dim);
    for (int i=0; i<this->dim; i++) {
        this->position[i] = pos[i];
        this->velocity[i] = vel[i];
    }
}
/**
 * @brief constructor (copy)
 * @param p another particle whose position, dimensionality, and velocity will be copied to make this new particle
 */
PSOParticle::PSOParticle(PSOParticle const &p) {
    this->dim = p.dim;
    this->position = std::vector<float>(this->dim);
    this->velocity = std::vector<float>(this->dim);
    for (int i=0; i<this->dim; i++) {
        this->position[i] = p.position[i];
        this->velocity[i] = p.velocity[i];
    }
}
/**
 * @brief set position of particle
 * @param p new position value
 * @param i index of position vector into which to place new value
 */
void PSOParticle::setPositionAtIndex(float p, int i) {
    this->position[i] = p;
}
/**
 * @brief get position of particle
 * @param i index of particle position vector
 * @return position of particle at index i
 */
float PSOParticle::getPositionAtIndex(int i) {
    return this->position[i];
}
/**
 * @brief set velocity of particle
 * @param v new velocity value
 * @param i index of velocity vector into which to place new value
 */
void PSOParticle::setVelocityAtIndex(float v, int i) {
    this->velocity[i] = v;
}
/**
 * @brief get velocity of particle
 * @param i index of particle velocity vector
 * @return velocity of particle at index i
 */
float PSOParticle::getVelocityAtIndex(int i) {
    return this->velocity[i];
}
/**
 * @brief get position of particle
 * @return position vector of particle
 */
std::vector<float> PSOParticle::getPosition() {
    return this->position;
}
/**
 * @brief get velocity of particle
 * @return velocity vector of particle
 */
std::vector<float> PSOParticle::getVelocity() {
    return this->velocity;
}
/**
* @brief set particle is in collision
* @param iic is in collision
*/
void PSOParticle::setIsInCollision(bool iic) {
	this->isInCollision = iic;
}
/**
* @brief get is particle in collision
* @return is particle in collision
*/
bool PSOParticle::getIsInCollision() {
	return this->isInCollision;
}
