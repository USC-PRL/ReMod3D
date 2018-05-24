// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include <vector>
#include <utility>
#include <map>
#include "ModuleLink.h"
#include "ModuleJoint.h"
#include "ModuleSensor.h"
#include "ModuleActuator.h"
#include "ModuleConnector.h"
#include "ModuleDockFace.h"
#include "ModularRobotType.h"
#include "ModularRobot.generated.h"

UCLASS()
class REBOTS_API AModularRobot : public APawn
{
	GENERATED_BODY()
protected:
    int ModuleID; /**< module ID number */
    ModularRobotType Type; /**< type of module */
    std::map<int, ModuleLink> ModuleLinks; /**< module links */
    std::map<int, ModuleJoint> ModuleJoints; /**< module joints */
    std::map<int, ModuleSensor*> Sensors; /**< module sensors */
    std::map<int, ModuleActuator*> Actuators; /**< module actuators */
    std::map<int, ModuleConnector> Connectors; /**< module connectors */
public:
	/**
     * @brief constructor
     */
	AModularRobot();
    /**
     * @brief constructor
     * @param IDNum module id number
     */
    AModularRobot(int IDNum, ModularRobotType T);
    /**
     * @brief set robot type
     * @param T type
     */
    void SetRobotType(ModularRobotType T);
    /**
     * @brief get robot type
     * @return robot type
     */
    ModularRobotType GetRobotType();
    /**
     * @brief add link to map
     * @param i index
     * @param L link
     */
    void AddLink(int i, ModuleLink L);
    /**
     * @brief add joint to map
     * @param i index
     * @param J joint
     */
    void AddJoint(int i, ModuleJoint J);
    /**
     * @brief add sensor to map
     * @param i index
     * @param S sensor
     */
    void AddSensor(int i, ModuleSensor* S);
    /**
     * @brief add actuator to map
     * @param i index
     * @param A actuator
     */
    void AddActuator(int i, ModuleActuator* A);
    /**
     * @brief add connector to map
     * @param i index
     * @param C connector
     */
    void AddConnector(int i, ModuleConnector C);
    /**
     * @brief get link at index
     * @param i index
     * @return link at index
     */
    ModuleLink GetLinkAtIndex(int i);
    /**
     * @brief get joint at index
     * @param i index
     * @return joint at index
     */
    ModuleJoint GetJointAtIndex(int i);
    /**
     * @brief get sensor at index
     * @param i index
     * @return sensor at index
     */
    ModuleSensor* GetSensorAtIndex(int i);
    /**
     * @brief get actuator at index
     * @param i index
     * @return actuator at index
     */
    ModuleActuator* GetActuatorAtIndex(int i);
    /**
     * @brief get connector at index
     * @param i index 
     * @return connector at index
     */
    ModuleConnector GetConnectorAtIndex(int i);
    /**
     * @brief clear links map
     */
    void ClearLinks();
    /**
     * @brief clear joints map
     */
    void ClearJoints();
    /**
     * @brief clear sensors map
     */
    void ClearSensors();
    /**
     * @brief clear actuators map
     */
    void ClearActuators();
    /**
     * @brief clear connectors map
     */
    void ClearConnectors();
	/**
     * @brief begin playing event handler
     */
	virtual void BeginPlay() override;
    /**
     * @brief event handler called every tick
     * @param DeltaSeconds change in seconds since last call to tick
     */
	virtual void Tick( float DeltaSeconds ) override;
    /**
     * @brief event handler called to bind functionality to input
     * @param InputComponent input component
     */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
