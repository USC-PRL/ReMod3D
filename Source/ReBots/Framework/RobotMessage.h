// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <random>
/**
 * @class RobotMessage
 * @brief superbot message superclass
 */
class REBOTS_API RobotMessage
{
protected:
    int IDNumber; /**< id number */
    int LifeTime; /**< number of ticks before message expires */
    bool MessageValid; /**< is message still valid */
    bool HasBeenAcked; /**< have we received an ack for this message */
    std::string MessageString; /**< message string */
public:
    /**
     * @brief set message acked
     * @param A acked state
     */
    void SetMessageAcked(bool A);
    /**
     * @brief has message been acked?
     * @return message acked ?
     */
    bool HasMessageBeenAcked();
    /**
     * @brief set messsage string
     * @param S string
     */
    void SetMessageString(std::string S);
    /**
     * @brief get messsage string
     * @return message string
     */
    std::string GetMessageString();
    /**
     * @brief set id number
     * @param IDNum id number
     */
    void SetIDNumber(int IDNum);
    /**
     * @brief get id number
     * @return id number
     */
    int GetIDNumber();
    /**
     * @brief set lifetime
     * @param Life lifetime
     */
    void SetLifeTime(int Life);
    /**
     * @brief get life time
     * @return lifetime
     */
    int GetLifeTime();
    /**
     * @brief set message valid
     * @param valid valid still
     */
    void SetMessageValid(bool Valid);
    /**
     * @brief get message valid
     * @return is message still valid
     */
    bool IsMessageValid();
    /**
     * @brief constructor
     */
	RobotMessage();
    /**
     * @brief destructor
     */
	~RobotMessage();
};
