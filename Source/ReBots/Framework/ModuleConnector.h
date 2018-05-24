#pragma once
#include "ModuleDockFace.h"
#include "PhysXPublic.h"
#include "ModuleLink.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"

/**
 * @class ModuleConnector
 * @brief representaation of the connector of a self-reconfigurable module
 */
class REBOTS_API ModuleConnector
{
private: 
	ModuleLink Link; /**< representation of module link */
	ModuleDockFace DockFace; /**< module dock face */
	std::string BoneName; /**< name of bone */
public:
	/**
	* @brief set module link
	* @param link module link
	*/
	void SetModuleLink(ModuleLink link);
	/**
	* @brief set dock face
	* @param face dock face
	*/
	void SetDockFace( ModuleDockFace d);
	/**
	* @brief set name of bone
	* @param BN bone name
	*/
	void SetBoneName(std::string BN);
	/**
	* @brief get module link
	* @return module link reference
	*/
	ModuleLink GetModuleLink();
	/**
	* @brief get dock face
	* @return dock face
	*/
	 ModuleDockFace GetDockFace();
	/**
	* @brief get bone name
	* @return bone name
	*/
	std::string GetBoneName();
	/**
	* @brief constructor
	* @param l module link
	* @param d module dock face
	* @param b bone name
	*/
	ModuleConnector(ModuleLink l,  ModuleDockFace d, std::string b);
	/**
	*  @brief constructor
	*/
	ModuleConnector();
	/**
	* @brief destructor
	*/
	~ModuleConnector();
};
