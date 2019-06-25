// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_ManipulatorObjectActor_generated_h
#error "ManipulatorObjectActor.generated.h already included, missing '#pragma once' in ManipulatorObjectActor.h"
#endif
#define REBOTS_ManipulatorObjectActor_generated_h

#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAManipulatorObjectActor(); \
	friend struct Z_Construct_UClass_AManipulatorObjectActor_Statics; \
public: \
	DECLARE_CLASS(AManipulatorObjectActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AManipulatorObjectActor)


#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAManipulatorObjectActor(); \
	friend struct Z_Construct_UClass_AManipulatorObjectActor_Statics; \
public: \
	DECLARE_CLASS(AManipulatorObjectActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AManipulatorObjectActor)


#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AManipulatorObjectActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AManipulatorObjectActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AManipulatorObjectActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AManipulatorObjectActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AManipulatorObjectActor(AManipulatorObjectActor&&); \
	NO_API AManipulatorObjectActor(const AManipulatorObjectActor&); \
public:


#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AManipulatorObjectActor(AManipulatorObjectActor&&); \
	NO_API AManipulatorObjectActor(const AManipulatorObjectActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AManipulatorObjectActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AManipulatorObjectActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AManipulatorObjectActor)


#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Box() { return STRUCT_OFFSET(AManipulatorObjectActor, Box); }


#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_9_PROLOG
#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_INCLASS \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class AManipulatorObjectActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_CustomActors_ManipulatorObjectActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
