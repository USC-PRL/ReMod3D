// Fill out your copyright notice in the Description page of Project Settings.

 
#include "ModuleMessage.h"
/**
* @brief constructor
*/
ModuleMessage::ModuleMessage() { this->LifeTime = 0; this->Data = ""; }
/**
* @brief constructor
* @param L lifetime
* @param D data
* @param SF sending dock face
* @param RF receiving dock face
*/
ModuleMessage::ModuleMessage(int L, std::string D, ModuleDockFace SF, ModuleDockFace RF) {
	this->LifeTime = L;
	this->Data = D;
	this->SendingFace = SF;
	this->ReceivingFace = RF;
	
}
/**
*  @brief set sending face
*  @param SF sending face
*/
void ModuleMessage::SetSendingDockFace(ModuleDockFace SF) { this->SendingFace = SF; }
/**
* @brief set receiving face
* @param RF receiving face
*/
void ModuleMessage::SetReceivingFace(ModuleDockFace RF) { this->ReceivingFace = RF; }
/**
* @brief set message data
* @param D message data
*/
void ModuleMessage::SetMessageData(std::string D) { this->Data = D; }
/**
* @brief set lifetime
* @param L lifetime of message
*/
void ModuleMessage::SetMessageLifetime(int L) { this->LifeTime = L; }
/**
* @brief decrement message lifetime
* @return true if message still valid, false otherwise
*/
bool ModuleMessage::DecrementMessageLifetime() {
	this->LifeTime--;
	return IsMessageValid();
}
/**
* @brief is message still valid
* @return true of message liftime is greater than 0, false otherwise
*/
bool ModuleMessage::IsMessageValid() { return (this->LifeTime > 0); }
/**
*  @brief set sending face
*  @param SF sending face
*/
ModuleDockFace ModuleMessage::GetSendingDockFace() { return this->SendingFace; }
/**
* @brief set receiving face
* @param RF receiving face
*/
ModuleDockFace ModuleMessage::GetReceivingFace() { return this->ReceivingFace; }
/**
* @brief set message data
* @return D message data
*/
std::string ModuleMessage::GetMessageData() { return this->Data; }
/**
* @brief set lifetime
* @param L lifetime of message
*/
int ModuleMessage::GetMessageLifetime() { return this->LifeTime; }
/**
* @brief destructor
*/
ModuleMessage::~ModuleMessage() {}
