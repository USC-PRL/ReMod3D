 
#include "ConstraintMonitor.h"
/**
 * @brief constructor
 */
ConstraintMonitor::ConstraintMonitor() {}
/**
 * @brief destructor
 */
ConstraintMonitor::~ConstraintMonitor() {}
/**
 * @brief add constraint
 * @param mod superbot module
 * @param dock1 dock1
 * @param dock2 dock2
 */
void ConstraintMonitor::AddConstraint(std::string name1, std::string name2, ModuleDockFace dock1, ModuleDockFace dock2) {
    CurrentConstraints[std::pair<std::string, ModuleDockFace>(name1,dock1)] =
    std::pair<std::string, ModuleDockFace>(name2,dock2);
}
/**
 * @brief add constraint
 * @param mod superbot module
 * @param dock dock
 */
void ConstraintMonitor::RemoveConstraint(std::string name, ModuleDockFace dock) {
    CurrentConstraints[std::pair<std::string, ModuleDockFace>(name,dock)] =
    std::pair<std::string, ModuleDockFace>("",DOCK_9);
}
/**
 * @brief get constraints
 * @return constraints in world
 */
std::map<std::pair<std::string,ModuleDockFace>, std::pair<std::string,ModuleDockFace> > ConstraintMonitor::GetConstraints() {
    return this->CurrentConstraints;
}
/**
 * @brief manage constraints
 */
void ConstraintMonitor::ManageConstraints() {
    
}
