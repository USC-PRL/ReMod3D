#pragma once
#include <vector>
using namespace std;
/**
 * @class KinematicEdge
 * @brief edge in a kinematic data structure
 */
class REBOTS_API KinematicEdge {
private:
    int Module1; /**< module 1 name */
    int Module2; /**< module 2 name */
    FTransform EdgeTransform; /**< transform along edge */
    std::vector<float> Angles; /**< angles associated with transform */
public:
    /**
     * @brief constructor
     */
    KinematicEdge();
    /**
     * @brief constructor
     * @param m1 module 1 name
     * @param m2 module 2 name
     * @param et edge transform
     */
    KinematicEdge(int m1, int m2, FTransform et);
    /**
     * @brief get module 1 name
     * @return module 1 name
     */
    int GetModule1();
    /**
     * @brief get module 2 name
     * @return module 2 name
     */
    int GetModule2();
    /**
     * @brief get edge transform
     * @return edge transform
     */
    FTransform GetEdgeTransform();
    /**
     * @brief get angles associated with edge
     * @return angles
     */
    std::vector<float> GetAngles();
    /**
     * @brief set module 1
     * @param m1 module 1
     */
    void SetModule1(int m1);
    /**
     * @brief set module 2
     * @param m2 module 2
     */
    void SetModule2(int m2);
    /**
     * @brief set edge transform
     * @param e edge transform
     */
    void SetEdgeTransform(FTransform e);
    /**
     * @brief set angles associated with edge
     * @param a angles
     */
    void SetAngles(std::vector<float> a);
    
};
