// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModularRobot.h"


/**
 * @brief constructor
 */
AModularRobot::AModularRobot()
{
	PrimaryActorTick.bCanEverTick = true;

}
/**
 * @brief constructor
 * @param IDNum module id number
 */
AModularRobot::AModularRobot(int IDNum, ModularRobotType T) {
    this->ModuleID = IDNum;
    this->Type = T;
    PrimaryActorTick.bCanEverTick = true;
}
/**
 * @brief set robot type
 * @param T type
 */
void AModularRobot::SetRobotType(ModularRobotType T) {
    this->Type = T;
}
/**
 * @brief get robot type
 * @return robot type
 */
ModularRobotType AModularRobot::GetRobotType() {
    return this->Type;
}
/**
 * @brief add link to map
 * @param i index
 * @param L link
 */
void AModularRobot::AddLink(int i, ModuleLink L) {
    ModuleLinks[i] = L;
}
/**
 * @brief add joint to map
 * @param i index
 * @param J joint
 */
void AModularRobot::AddJoint(int i, ModuleJoint J) {
    ModuleJoints[i] = J;
}
/**
 * @brief add sensor to map
 * @param i index
 * @param S sensor
 */
void AModularRobot::AddSensor(int i, ModuleSensor* S) {
    Sensors[i] = S;
}
/**
 * @brief add actuator to map
 * @param i index
 * @param A actuator
 */
void AModularRobot::AddActuator(int i, ModuleActuator* A) {
    Actuators[i] = A;
}
/**
 * @brief add connector to map
 * @param i index
 * @param C connector
 */
void AModularRobot::AddConnector(int i, ModuleConnector C) {
    Connectors[i] = C;
}
/**
 * @brief get link at index
 * @param i index
 * @return link at index
 */
ModuleLink AModularRobot::GetLinkAtIndex(int i) {
    return ModuleLinks[i];
}
/**
 * @brief get joint at index
 * @param i index
 * @return joint at index
 */
ModuleJoint AModularRobot::GetJointAtIndex(int i) {
    return ModuleJoints[i];
}
/**
 * @brief get sensor at index
 * @param i index
 * @return sensor at index
 */
ModuleSensor* AModularRobot::GetSensorAtIndex(int i) {
    return Sensors[i];
}
/**
 * @brief get actuator at index
 * @param i index
 * @return actuator at index
 */
ModuleActuator* AModularRobot::GetActuatorAtIndex(int i) {
    return Actuators[i];
}
/**
 * @brief get connector at index
 * @param i index
 * @return connector at index
 */
ModuleConnector AModularRobot::GetConnectorAtIndex(int i) {
    return Connectors[i];
}
/**
 * @brief clear links map
 */
void AModularRobot::ClearLinks() {
    ModuleLinks.clear();
}
/**
 * @brief clear joints map
 */
void AModularRobot::ClearJoints() {
    ModuleJoints.clear();
}
/**
 * @brief clear sensors map
 */
void AModularRobot::ClearSensors() {
    Sensors.clear();
}
/**
 * @brief clear actuators map
 */
void AModularRobot::ClearActuators() {
    Actuators.clear();
}
/**
 * @brief clear connectors map
 */
void AModularRobot::ClearConnectors() {
    Connectors.clear();
}
/**
 * @brief begin playing event handler
 */
void AModularRobot::BeginPlay()
{
	Super::BeginPlay();
	
}
/**
 * @brief event handler called every tick
 * @param DeltaSeconds change in seconds since last call to tick
 */
void AModularRobot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
/**
 * @brief event handler called to bind functionality to input
 * @param InputComponent input component
 */
void AModularRobot::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}
