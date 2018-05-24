#pragma once
/**
 * @class ModuleMotorVector
 * @brief vector of superbot motor angles
 * @date 5-18-2015
 * @author Thomas Collins
 */
class REBOTS_API ModuleMotorVector{
public:
    float Motor0Angle; /**< motor 0 angle */
    float Motor1Angle; /**< motor 1 angle */
    float Motor2Angle; /**< motor 2 angle */
    /**
     * @brief constructor (default)
     */
    ModuleMotorVector();
    /**
     * @brief Constructor
     * @param m0 motor 0 angle
     * @param m1 motor 1 angle
     * @param m2 motor 2 angle
     */
    ModuleMotorVector(float m0, float m1, float m2);
    /**
     * @brief overloaded element operator
     * @param index index of element
     * @return motor angle for operator
     */
    float operator[](int index);
};
