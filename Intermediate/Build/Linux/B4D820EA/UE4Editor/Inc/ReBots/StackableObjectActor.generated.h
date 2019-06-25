// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_StackableObjectActor_generated_h
#error "StackableObjectActor.generated.h already included, missing '#pragma once' in StackableObjectActor.h"
#endif
#define REBOTS_StackableObjectActor_generated_h

#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAStackableObjectActor(); \
	friend struct Z_Construct_UClass_AStackableObjectActor_Statics; \
public: \
	DECLARE_CLASS(AStackableObjectActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AStackableObjectActor)


#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_INCLASS \
private: \
	static void StaticRegisterNativesAStackableObjectActor(); \
	friend struct Z_Construct_UClass_AStackableObjectActor_Statics; \
public: \
	DECLARE_CLASS(AStackableObjectActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AStackableObjectActor)


#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStackableObjectActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStackableObjectActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStackableObjectActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStackableObjectActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStackableObjectActor(AStackableObjectActor&&); \
	NO_API AStackableObjectActor(const AStackableObjectActor&); \
public:


#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AStackableObjectActor(AStackableObjectActor&&); \
	NO_API AStackableObjectActor(const AStackableObjectActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStackableObjectActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStackableObjectActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AStackableObjectActor)


#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Box() { return STRUCT_OFFSET(AStackableObjectActor, Box); }


#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_6_PROLOG
#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_INCLASS \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class AStackableObjectActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_CustomActors_StackableObjectActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
