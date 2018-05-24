#pragma once
#include <vector>
#include "ModuleMessage.h"
class ASuperBotModule;
enum SensorType {
	FLOAT_SENSOR,
	FLAG_SENSOR,
	MESSAGE_SENSOR,
	POSE_SENSOR
};
/**
 * 
 */
class REBOTS_API ModuleSensor
{
protected:
	int Name; /**< name of sensor */
	SensorType Type; /**< type of sensor */
public:
	/**
	* @brief get the current  value of the sensor
	* @return current floating point value of the sensor
	*/
	virtual float GetFloatValue(ASuperBotModule* M) { return 0.0; };
	/**
	* @brief get the current  value of the sensor
	* @return current floating point value of the sensor
	*/
	virtual std::vector<bool> GetFlagValue(ASuperBotModule* M) { return std::vector<bool> {false}; };
	/**
	* @brief get the current  value of the sensor
	* @return current floating point value of the sensor
	*/
	virtual FTransform GetTransformValue(ASuperBotModule* M) { return FTransform(FVector(1, 0, 0)); };
	/**
	* @brief get current sensor value
	* @return sensor value
	*/
	virtual std::vector<ModuleMessage> GetMessageValue(ASuperBotModule* M) { return std::vector<ModuleMessage>(); }

	/**
	* @brief set sensor name
	* @param name sensor name
	*/
	void SetName(int name);
	/**
	* @brief get sensor name
	* @return sensor name
	*/
	int GetName();
	/**
	* @brief set type of sensor
	* @param T type of sensor
	*/
	void SetType(SensorType T);
	/**
	* @brief get type of sensor
	* @return type of sensor
	*/
	SensorType GetType();
	/**
	* @brief constructor
	* @param name name of sensor
	*/
	ModuleSensor(int name);
	/**
	* @brief constructor
	*/
	ModuleSensor();
	/**
	* @brief detructor
	*/
	virtual ~ModuleSensor();
};
