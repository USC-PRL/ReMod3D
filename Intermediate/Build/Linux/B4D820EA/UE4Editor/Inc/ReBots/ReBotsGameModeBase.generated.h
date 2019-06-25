// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_ReBotsGameModeBase_generated_h
#error "ReBotsGameModeBase.generated.h already included, missing '#pragma once' in ReBotsGameModeBase.h"
#endif
#define REBOTS_ReBotsGameModeBase_generated_h

#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAReBotsGameModeBase(); \
	friend struct Z_Construct_UClass_AReBotsGameModeBase_Statics; \
public: \
	DECLARE_CLASS(AReBotsGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AReBotsGameModeBase)


#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAReBotsGameModeBase(); \
	friend struct Z_Construct_UClass_AReBotsGameModeBase_Statics; \
public: \
	DECLARE_CLASS(AReBotsGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AReBotsGameModeBase)


#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AReBotsGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AReBotsGameModeBase) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AReBotsGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AReBotsGameModeBase); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AReBotsGameModeBase(AReBotsGameModeBase&&); \
	NO_API AReBotsGameModeBase(const AReBotsGameModeBase&); \
public:


#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AReBotsGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AReBotsGameModeBase(AReBotsGameModeBase&&); \
	NO_API AReBotsGameModeBase(const AReBotsGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AReBotsGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AReBotsGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AReBotsGameModeBase)


#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET
#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_12_PROLOG
#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_INCLASS \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_ReBotsGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class AReBotsGameModeBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_ReBotsGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
