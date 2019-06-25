// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_RoomBotModule_generated_h
#error "RoomBotModule.generated.h already included, missing '#pragma once' in RoomBotModule.h"
#endif
#define REBOTS_RoomBotModule_generated_h

#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARoomBotModule(); \
	friend struct Z_Construct_UClass_ARoomBotModule_Statics; \
public: \
	DECLARE_CLASS(ARoomBotModule, AModularRobot, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ARoomBotModule)


#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_INCLASS \
private: \
	static void StaticRegisterNativesARoomBotModule(); \
	friend struct Z_Construct_UClass_ARoomBotModule_Statics; \
public: \
	DECLARE_CLASS(ARoomBotModule, AModularRobot, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ARoomBotModule)


#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ARoomBotModule(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ARoomBotModule) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARoomBotModule); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARoomBotModule); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARoomBotModule(ARoomBotModule&&); \
	NO_API ARoomBotModule(const ARoomBotModule&); \
public:


#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARoomBotModule(ARoomBotModule&&); \
	NO_API ARoomBotModule(const ARoomBotModule&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARoomBotModule); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARoomBotModule); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARoomBotModule)


#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__RoomBotHem1() { return STRUCT_OFFSET(ARoomBotModule, RoomBotHem1); } \
	FORCEINLINE static uint32 __PPO__RoomBotHem2() { return STRUCT_OFFSET(ARoomBotModule, RoomBotHem2); } \
	FORCEINLINE static uint32 __PPO__HemJoint1() { return STRUCT_OFFSET(ARoomBotModule, HemJoint1); }


#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_59_PROLOG
#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_INCLASS \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h_62_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class ARoomBotModule>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_RoomBot_RoomBotModule_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
