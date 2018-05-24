// Fill out your copyright notice in the Description page of Project Settings.

 
#include "THatDistributed.h"
/**
* @brief update my THat value
*/
void THatDistributed::updateTHat() {
    
}
/**
* @brief pack update string
* @return update string
*/
std::string THatDistributed::packUpdateString() {
	stringstream ss;
    ss << myID << ":" << myRCC << ":" << myCC << ":" << myB << ":"<< myT;
	return ss.str();
}
/**
 * @brief split string on delimiter
 * @param str string
 * @param delim delimiter to split on
 */
vector<string> THatDistributed::split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
/**
 * @brief update data structures with messages
 * @param messages messages
 */
void THatDistributed::updateDataStructures(vector<Message> messages) {
    for (int i=0; i<messages.size(); i++) {
        std::string s = messages[i].getMessageData();
        vector<string> mParts = split(s, ":");
        int idNum = stoi(mParts[0]);
        float rcc = stof(mParts[1]);
        float cc = stof(mParts[2]);
        float b = stof(mParts[3]);
        float t = stof(mParts[4]);
        RCC[idNum] = rcc;
        CC[idNum] = cc;
        B[idNum] = b;
        T[idNum] = t;
    }
}
/**
* @brief communicate values to neighboring modules
*/
void THatDistributed::communicateWithImmediateNeighors(ModuleModel m) {
	for (int i = 0; i < 6; i++) {
		if (m.GetCurrentState().GetDocksEngagedStatus()[i]) {
			std::string message = packUpdateString();
			if (i == DOCK_0) {AddMessageAction(std::pair<ModuleAction,std::string>(SEND_MESSAGE_FRONT_DOCK, message));}
			else if (i == DOCK_1){AddMessageAction(std::pair<ModuleAction,std::string>(SEND_MESSAGE_BACK_DOCK, message));}
			else if (i == DOCK_2){AddMessageAction(std::pair<ModuleAction,std::string>(SEND_MESSAGE_LEFT_DOCK, message));}
			else if (i ==DOCK_3) {AddMessageAction(std::pair<ModuleAction,std::string>(SEND_MESSAGE_RIGHT_DOCK, message));}
			else if (i == DOCK_4) {AddMessageAction(std::pair<ModuleAction,std::string>(SEND_MESSAGE_UP_DOCK, message));}
			else if (i == DOCK_5){AddMessageAction(std::pair<ModuleAction,std::string>(SEND_MESSAGE_DOWN_DOCK, message));}
		}
	}
}

/**
* @brief init program
*/
void THatDistributed::Init() {}
/**
* @brief step function of behavior
* @param jointVals superbot sensor values
* @param desiredVals desired sensor values
* @return action values
*/
void THatDistributed::Tick(ModuleModel model) {
    ClearAllActions();
	if (TickCount == 0) {
		myID = model.GetCurrentState().GetIDNumber();
		myRCC = myID + 1;
		myCC = myID + 2;
		myB = myID + 3;
        myT = myID + 4;
        RCC[myID] = myRCC;
        CC[myID] = myCC;
        B[myID] = myB;
        T[myID] = myT;
	}
	vector<Message> messages = model.GetCurrentState().GetMessages();
    updateDataStructures(messages);
    updateTHat();
	communicateWithImmediateNeighors(model);
	TickCount++;
}
/**
* @brief constructor
*/
THatDistributed::THatDistributed(){}
/**
*@brief destructor
*/
THatDistributed::~THatDistributed(){}
