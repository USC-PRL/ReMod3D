#pragma once
#include <iostream>
#include <vector>
#include "Framework/ModuleDock.h"
#include "Framework/RobotMessage.h"
/**
 * @class Message
 * @brief message to send between modules
 */
class REBOTS_API Message : public RobotMessage
{
private:
    std::string messageData; /**< message contents */
    ModuleDock sendingDock; /**< sending dock */
    ModuleDock receivingDock; /**< receiving dock */
    int lifeCount; /**< life counter */
public:
    /**
     *	@brief	Message class constructor
     *	@param 	messageData 	contents of the message
     *	@param 	sendDock 	sending dock object
     *	@param 	receiveDock 	receiving dock object
     *  @param lc life counter
     *	@return	Message object
     */
    Message(std::string mData, ModuleDock sendDock, ModuleDock receiveDock, int lc);
    /**
     *	@brief	Message class constructor
     *	@param 	messageData 	contents of the message
     *	@param 	sendDock 	sending dock object
     *	@param 	receiveDock 	receiving dock object
     *	@return	Message object
     */
    Message(std::string mData, ModuleDock sendDock, ModuleDock receiveDock);
    /**
     *	@brief	Getter for messageData
     *	@return	returns the data in the message
     */
    std::string getMessageData();
    /**
     *	@brief	Getter for sendingDock
     *	@return	returns the object representing the sending dock
     */
    ModuleDock getSendingDock();
    /**
     *	@brief	Getter for receivingDock
     *	@return	returns the object representing the receiving dock
     */
    ModuleDock getReceivingDock();
    /**
     * @brief set life counter
     * @param lc life counter
     */
    void setLifeCount(int lc);
    /**
     * @brief get life counter
     * @return life counter
     */
    int getLifeCount();
    /**
     * @brief increment life count
     */
    void incrementLifeCount();
    /**
     * @brief decrement life count
     */
    void decrementLifeCount();
};
