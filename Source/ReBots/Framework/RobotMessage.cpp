// Fill out your copyright notice in the Description page of Project Settings.

 
#include "RobotMessage.h"
/**
 * @brief set message acked
 * @param A acked state
 */
void RobotMessage::SetMessageAcked(bool A) {
    this->HasBeenAcked = A;
}
/**
 * @brief has message been acked?
 * @return message acked ?
 */
bool RobotMessage::HasMessageBeenAcked() {
    return this->HasBeenAcked;
}
/**
 * @brief set messsage string
 * @param S string
 */
void RobotMessage::SetMessageString(std::string S) {
    this->MessageString = S;
}
/**
 * @brief get messsage string
 * @return message string
 */
std::string RobotMessage::GetMessageString() {
    return this->MessageString;
}
/**
 * @brief set id number
 * @param IDNum id number
 */
void RobotMessage::SetIDNumber(int IDNum) {
    this->IDNumber  = IDNum;
}
/**
 * @brief get id number
 * @return id number
 */
int RobotMessage::GetIDNumber() {
    return this->IDNumber;
}
/**
 * @brief set lifetime
 * @param Life lifetime
 */
void RobotMessage::SetLifeTime(int Life) {
    this->LifeTime = Life;
}
/**
 * @brief get life time
 * @return lifetime
 */
int RobotMessage::GetLifeTime() {
    return this->LifeTime;
}
/**
 * @brief set message valid
 * @param valid valid still
 */
void RobotMessage::SetMessageValid(bool Valid) {
    this->MessageValid = Valid;
}
/**
 * @brief get message valid
 * @return is message still valid
 */
bool RobotMessage::IsMessageValid() {
    return this->MessageValid;
}
/**
 * @brief constructor
 */
RobotMessage::RobotMessage() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, std::numeric_limits<int>::max());
    this->IDNumber = dis(gen);
    this->LifeTime = 10;
    this->MessageValid = true;
    this->HasBeenAcked = false;
    this->MessageString = "DefaultMessage";
}
/**
 * @brief destructor
 */
RobotMessage::~RobotMessage(){}
