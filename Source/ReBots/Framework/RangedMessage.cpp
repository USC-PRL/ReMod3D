 
#include "RangedMessage.h"
/**
 *	@brief	RangedMessage constructor
 *	@param 	messageData 	data held in the message
 *	@param 	range 	radius of message outside module COM
 *	@return	RangedMessage object
 */
RangedMessage::RangedMessage(std::string mData, float r){
    this->messageData = mData;
    this->range = r;
}
/**
 *	@brief	Returns message data
 *	@return	the data held in the message
 */
std::string RangedMessage::getMessageData() {
    return this->messageData;
}
/**
 *	@brief	Returns range of message
 *  @return radius of message outside module COM
 */
float RangedMessage::getRange() {
    return this->range;
}
