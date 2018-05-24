 
#include "ModuleMotorVector.h"

/**
 * @brief constructor (default)
 */
ModuleMotorVector::ModuleMotorVector() {
    Motor0Angle = 0.0;
    Motor1Angle = 0.0;
    Motor2Angle = 0.0;
}
/**
 * @brief Constructor
 * @param m0 motor 0 angle
 * @param m1 motor 1 angle
 * @param m2 motor 2 angle
 */
ModuleMotorVector::ModuleMotorVector(float m0, float m1, float m2) {
    this->Motor0Angle = m0;
    this->Motor1Angle = m1;
    this->Motor2Angle = m2;
}
/**
 * @brief overloaded element operator
 * @param index index of element
 * @return motor angle for operator
 */
float ModuleMotorVector::operator[](int index) {
    if (index == 0) {
        return Motor0Angle;
    } else if (index == 1) {
        return Motor1Angle;
    } else if (index == 2) {
        return Motor2Angle;
    } else {
        return -1;
    }
}
