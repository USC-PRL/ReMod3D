 
#include "KinematicEdge.h"
/**
 * @brief constructor
 */
KinematicEdge::KinematicEdge() {}
/**
 * @brief constructor
 * @param m1 module 1 name
 * @param m2 module 2 name
 * @param et edge transform
 */
KinematicEdge::KinematicEdge(int m1, int m2, FTransform et) {
    this->Module1 = m1;
    this->Module2 = m2;
    this->EdgeTransform = et;
}
/**
 * @brief get angles associated with edge
 * @return angles
 */
std::vector<float> KinematicEdge::GetAngles() {
    return this->Angles;
}
/**
 * @brief get module 1 name
 * @return module 1 name
 */
int KinematicEdge::GetModule1() {return this->Module1;}
/**
 * @brief get module 2 name
 * @return module 2 name
 */
int KinematicEdge::GetModule2() {return this->Module2;}
/**
 * @brief get edge transform
 * @return edge transform
 */
FTransform KinematicEdge::GetEdgeTransform() {return this->EdgeTransform;}
/**
 * @brief set module 1
 * @param m1 module 1
 */
void KinematicEdge::SetModule1(int m1) {this->Module1 = m1;}
/**
 * @brief set module 2
 * @param m2 module 2
 */
void KinematicEdge::SetModule2(int m2) {this->Module2 = m2;}
/**
 * @brief set edge transform
 * @param e edge transform
 */
void KinematicEdge::SetEdgeTransform(FTransform e) {this->EdgeTransform = e;}
/**
 * @brief set angles associated with edge
 * @param a angles
 */
void KinematicEdge::SetAngles(std::vector<float> a) {this->Angles = a;}
