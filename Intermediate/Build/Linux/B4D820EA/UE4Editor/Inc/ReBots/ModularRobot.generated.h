// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_ModularRobot_generated_h
#error "ModularRobot.generated.h already included, missing '#pragma once' in ModularRobot.h"
#endif
#define REBOTS_ModularRobot_generated_h

#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAModularRobot(); \
	friend struct Z_Construct_UClass_AModularRobot_Statics; \
public: \
	DECLARE_CLASS(AModularRobot, APawn, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AModularRobot)


#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_INCLASS \
private: \
	static void StaticRegisterNativesAModularRobot(); \
	friend struct Z_Construct_UClass_AModularRobot_Statics; \
public: \
	DECLARE_CLASS(AModularRobot, APawn, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AModularRobot)


#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AModularRobot(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AModularRobot) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AModularRobot); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AModularRobot); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AModularRobot(AModularRobot&&); \
	NO_API AModularRobot(const AModularRobot&); \
public:


#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AModularRobot(AModularRobot&&); \
	NO_API AModularRobot(const AModularRobot&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AModularRobot); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AModularRobot); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AModularRobot)


#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_PRIVATE_PROPERTY_OFFSET
#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_18_PROLOG
#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_INCLASS \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_Framework_ModularRobot_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class AModularRobot>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_Framework_ModularRobot_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
