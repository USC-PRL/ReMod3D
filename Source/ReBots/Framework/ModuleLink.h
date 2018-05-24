#pragma once
#include <iostream>
/**
 *  @class ModuleLink
 * @brief representation of the link of a module
 */
class REBOTS_API ModuleLink
{
private:
	std::string ModuleName; /**< name of module */
	std::string LinkName; /**< name of the link*/
	UStaticMeshComponent* Link; /**<representation of the link itself */
public:
	/**
	* @brief set the module name
	* @param name name of module
	*/
	void SetModuleName(std::string name);
	/**
	* @brief set the name of the link
	* @param name name of link
	*/
	void SetLinkName(std::string name);
	/**
	* @brief set link reference
	* @param link link reference
	*/
	void SetLinkReference(UStaticMeshComponent* link);
	/**
	* @brief get module name
	* @return module name
	*/
	std::string GetModuleName();
	/**
	* @brief get link name
	* @return module name
	*/
	std::string GetLinkName();
	/**
	* @brief get link reference
	* @return link reference
	*/
	UStaticMeshComponent* GetLinkReference();
	/**
	* @brief constructor
	*/
	ModuleLink();
	/**
	* @brief constructor
	* @param name module name
	* @param lname link name
	* @param l link reference
	*/
	ModuleLink(std::string name, std::string lname, UStaticMeshComponent* l);
	/**
	* @brief destructor
	*/
	~ModuleLink();
};
