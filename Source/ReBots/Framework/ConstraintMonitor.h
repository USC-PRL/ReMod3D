// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include <utility>
#include <map>
#include "Framework/ModuleDockFace.h"
using namespace std;
/**
 * @class ConstraintMonitor
 * @brief keeps track of the constraints in the simulated world
 */
class REBOTS_API ConstraintMonitor
{
private:
    std::map<std::pair<std::string,ModuleDockFace>, std::pair<std::string,ModuleDockFace> > CurrentConstraints;
    /**< current constraints in sim */
public:
    /**
     * @brief add constraint
     * @param mod superbot module
     * @param dock1 dock1
     * @param dock2 dock2
     */
    void AddConstraint(std::string name1, std::string name2, ModuleDockFace dock1, ModuleDockFace dock2);
    /**
     * @brief add constraint
     * @param mod superbot module
     * @param dock dock
     */
    void RemoveConstraint(std::string mod, ModuleDockFace dock);
    /**
     * @brief get constraints
     * @return constraints in world
     */
    std::map<std::pair<std::string, ModuleDockFace>, std::pair<std::string, ModuleDockFace> > GetConstraints();
    /**
     * @brief manage constraints
     */
    void ManageConstraints();
    /**
     * @brief Constructor
     */
	ConstraintMonitor();
    /**
     * @brief destructor
     */
	~ConstraintMonitor();
};
