// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Pawn.h"
#include "PhysXPublic.h"
#include "Framework/ModuleDock.h"
#include "SuperBotModule.h"
#include "Framework/ModuleMotorVector.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;
using namespace physx;
/**
 * @class SuperbotKinematics
 * @brief Superbot kinematics procedures
 */
class REBOTS_API SuperbotKinematics
{
public:
    constexpr static const float half_width_inner_cube = 26.5;
    constexpr static const float half_height_inner_cube = 31.5;
    constexpr static const float half_depth_inner_cube = 32.0;
    constexpr static const float half_height_outer_box_front_back = 35.0;
    constexpr static const float half_width_outer_box_front_back = 4.0;
    constexpr static const float half_depth_outer_box_front_back = 40.0;
    constexpr static const float half_width_outer_box_left_right = 17.0;
    constexpr static const float half_height_outer_box_left_right = 35.0;
    constexpr static const float half_depth_outer_box_left_right = 4.0;
    constexpr static const float distance_between_inner_cubes = 0.0;
    constexpr static const float radius_of_side_circle = 34.0;
    constexpr static const float half_depth_microcontroller_box = 12.0;
    constexpr static const float half_width_microcontroller_box = 12.0;
    constexpr static const float half_height_microcontroller_box = 1.0;
    constexpr static const float half_distance_between_rounded_parts = 7.0;
    constexpr static const float half_width_dock = 6.0;
    constexpr static const float half_width_module = 2*half_width_outer_box_left_right + radius_of_side_circle +
    half_distance_between_rounded_parts +
    half_width_outer_box_front_back*2.0;
    constexpr static const float half_depth_module_dock = half_width_dock*2.0 + half_depth_outer_box_front_back;
    constexpr static const float half_module_height = half_height_outer_box_front_back;
    /**
     * @brief computing transform to dock
     * @param mod Superbot module
     * @param dock Superbot dock face
     * @return transform from Superbot module to dock
     */
    static FTransform computeTransformToDock(ModuleMotorVector mv, ModuleDockFace dock);
    /**
     * @brief computing transform to dock
     * @param mod Superbot module
     * @param dock Superbot dock face
     * @return transform from Superbot dock to module
     */
    static FTransform computeTransformFromDock(ModuleMotorVector mv, ModuleDockFace dock);
};
