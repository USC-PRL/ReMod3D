// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include "ModuleDockFace.h"
/**
 * @class ModuleMessage
 * @brief module message representation
 */
class REBOTS_API ModuleMessage
{
private:
	ModuleDockFace SendingFace; /**< sending dock face */
	ModuleDockFace ReceivingFace; /**< receiving dock face */
	std::string Data; /**< message data */
	int LifeTime; /**< message lifetime */
public:
	/**
	* @brief constructor
	*/
	ModuleMessage();
	/**
	* @brief constructor
	* @param L lifetime
	* @param D data
	* @param SF sending dock face
	* @param RF receiving dock face
	*/
	ModuleMessage(int L, std::string D, ModuleDockFace SF, ModuleDockFace RF);
	/**
	*  @brief set sending face
	*  @param SF sending face
	*/
	void SetSendingDockFace(ModuleDockFace SF);
	/**
	* @brief set receiving face
	* @param RF receiving face
	*/
	void SetReceivingFace(ModuleDockFace RF);
	/**
	* @brief set message data
	* @param D message data
	*/
	void SetMessageData(std::string D);
	/**
	* @brief set lifetime
	* @param L lifetime of message
	*/
	void SetMessageLifetime(int L);
	/**
	* @brief decrement message lifetime
	* @return true if message still valid, false otherwise
	*/
	bool DecrementMessageLifetime();
	/**
	* @brief is message still valid
	* @return true of message liftime is greater than 0, false otherwise
	*/
	bool IsMessageValid();
	/**
	*  @brief set sending face
	*  @param SF sending face
	*/
	ModuleDockFace GetSendingDockFace();
	/**
	* @brief set receiving face
	* @param RF receiving face
	*/
	ModuleDockFace GetReceivingFace();
	/**
	* @brief set message data
	* @return D message data
	*/
	std::string GetMessageData();
	/**
	* @brief set lifetime
	* @param L lifetime of message
	*/
	int GetMessageLifetime();
	/**
	* @brief destructor
	*/
	~ModuleMessage();
};
