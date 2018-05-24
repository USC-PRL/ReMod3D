// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
/**
 * @class ModuleBehaviorTask
 * @brief module behavior task representation
 */
class REBOTS_API ModuleBehaviorTask
{
private:
	std::vector<bool> Flags; /**< boolean flags for tracking task progress */
	std::vector<int> Counters; /**< integer counters for tracking task progress */
public:
	/**
	* @brief constructor
	*/
	ModuleBehaviorTask();
	/**
	* @brief destructor
	*/
	~ModuleBehaviorTask();
};
