#pragma once
#include <iostream>
#include <vector>
#include "Framework/RobotMessage.h"
/**
 * @class RangedMessage
 * @brief message to send between modules (ranged)
 */
class REBOTS_API RangedMessage: public RobotMessage {
private:
    std::string messageData; /**< message data */
    float range; /**< radius of message outside of module center of mass (in all directions) */
public:
    /**
     *	@brief	RangedMessage constructor
     *	@param 	messageData 	data held in the message
     *	@param 	range 	radius of message outside module COM
     *	@return	RangedMessage object
     */
    RangedMessage(std::string mData, float r);
    /**
     *	@brief	Returns message data
     *	@return	the data held in the message
     */
    std::string getMessageData();
    /**
     *	@brief	Returns range of message
     *  @return radius of message outside module COM
     */
    float getRange();
};
