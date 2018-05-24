#pragma once
#include <queue>
#include <vector>
#include <iostream>
#include "Framework/RobotModuleBehavior.h"
#include <sstream>
#include <map>
using namespace std;
/**
 * 
 */
class REBOTS_API THatDistributed : public RobotModuleBehavior
{
private:
    /**< my id number */
	int myID;
    /**< my RCC value */
	float myRCC;
    /**< my T value */
	float myCC;
    /**< my B value */
	float myB;
    /**< my T value */
    float myT;
    /**< rcc of neighbors */
	map<int, float> RCC;
    /**< cc of neighbors */
	map<int, float> CC;
    /**< b of neighbors */
	map<int, float> B;
    /**< t values of neighbors */
	map<int, float> T;
    /**< simulation tick counter */
	int TickCount = 0;
public:
    /**
     * @brief perform That update algorithm
     */
	void updateTHat();
    /**
     * @brief communicate with immediate neighors to share values
     * @param m model
     */
	void communicateWithImmediateNeighors(ModuleModel m);
    /**
     * @brief update data structures with messages from neighbors
     * @param messages messages from neighbors
     */
    void updateDataStructures(vector<Message> messages);
    /**
     * @brief split string on delimiter
     * @param str string
     * @param delim delimiter to split on
     */
    vector<string> split(const string& str, const string& delim);
    /**
     * @brief package update string
     */
	std::string packUpdateString();
	/**
	* @brief init program
	*/
	void Init();
	/**
	* @brief step function of behavior
	* @param jointVals superbot sensor values
	* @param desiredVals desired sensor values
	* @return action values
	*/
	virtual void Tick(ModuleModel model);
	/**
	* @brief constructor
	*/
	THatDistributed();
	/**
	* @brief destructor
	*/
	virtual ~THatDistributed();
};
