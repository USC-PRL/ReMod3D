// Fill out your copyright notice in the Description page of Project Settings.

 
#include "Message.h"

/**
 *	@brief	Message class constructor
 *	@param 	messageData 	contents of the message
 *	@param 	sendDock 	sending dock object
 *	@param 	receiveDock 	receiving dock object
 *  @param lc life counter
 *	@return	Message object
 */
Message::Message(std::string mData, ModuleDock sendDock, ModuleDock receiveDock, int lc) {
    this->messageData = mData;
    this->sendingDock = sendDock;
    this->receivingDock = receiveDock;
    this->lifeCount = lc;
}
/**
 *	@brief	Message class constructor
 *	@param 	messageData 	contents of the message
 *	@param 	sendDock 	sending dock object
 *	@param 	receiveDock 	receiving dock object
 *	@return	Message object
 */
Message::Message(std::string mData, ModuleDock sendDock, ModuleDock receiveDock) {
    this->messageData = mData;
    this->sendingDock = sendDock;
    this->receivingDock = receiveDock;
    this->lifeCount = 0;
}
/**
 *	@brief	Getter for messageData
 *	@return	returns the data in the message
 */
std::string Message::getMessageData() {
    return this->messageData;
}
/**
 *	@brief	Getter for sendingDock
 *	@return	returns the object representing the sending dock
 */
ModuleDock Message::getSendingDock() {
    return this->sendingDock;
}
/**
 *	@brief	Getter for receivingDock
 *	@return	returns the object representing the receiving dock
 */
ModuleDock Message::getReceivingDock() {
    return this->receivingDock;
}
/**
 * @brief set life counter
 * @param lc life counter
 */
void Message::setLifeCount(int lc) {
    this->lifeCount = lc;
}
/**
 * @brief get life counter
 * @return life counter
 */
int Message::getLifeCount() {
    return this->lifeCount;
}
/**
 * @brief increment life count
 */
void Message::incrementLifeCount() {
    this->lifeCount = this->lifeCount + 1;
}
/**
 * @brief decrement life count
 */
void Message::decrementLifeCount() {
    this->lifeCount = this->lifeCount - 1;
}
