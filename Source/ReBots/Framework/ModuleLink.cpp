 
#include "ModuleLink.h"
/**
* @brief set the module name
* @param name name of module
*/
void ModuleLink::SetModuleName(std::string name) {
	this->ModuleName = name;
}
/**
* @brief set the name of the link
* @param name name of link
*/
void ModuleLink::SetLinkName(std::string name) {
	this->LinkName = name;
}
/**
* @brief set link reference
* @param link link reference
*/
void ModuleLink::SetLinkReference(UStaticMeshComponent* link) {
	this->Link = link;
}
/**
* @brief get module name
* @return module name
*/
std::string ModuleLink::GetModuleName() {
	return this->ModuleName;
}
/**
* @brief get link name
* @return module name
*/
std::string ModuleLink::GetLinkName() {
	return this->LinkName;
}
/**
* @brief get link reference
* @return link reference
*/
UStaticMeshComponent* ModuleLink::GetLinkReference() {
	return this->Link;
}
/**
* @brief constructor
*/
ModuleLink::ModuleLink() {
	this->ModuleName = "";
	this->LinkName = "";
	this->Link = NULL;

}
/**
* @brief constructor
* @param name module name
* @param lname link name
* @param l link reference
*/
ModuleLink::ModuleLink(std::string name, std::string lname, UStaticMeshComponent* l) {
	this->ModuleName = name;
	this->LinkName = lname;
	this->Link = l;
}
/**
* @brief destructor
*/
ModuleLink::~ModuleLink() {}
