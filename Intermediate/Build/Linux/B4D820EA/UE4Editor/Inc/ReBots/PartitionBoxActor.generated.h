// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_PartitionBoxActor_generated_h
#error "PartitionBoxActor.generated.h already included, missing '#pragma once' in PartitionBoxActor.h"
#endif
#define REBOTS_PartitionBoxActor_generated_h

#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPartitionBoxActor(); \
	friend struct Z_Construct_UClass_APartitionBoxActor_Statics; \
public: \
	DECLARE_CLASS(APartitionBoxActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(APartitionBoxActor)


#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_INCLASS \
private: \
	static void StaticRegisterNativesAPartitionBoxActor(); \
	friend struct Z_Construct_UClass_APartitionBoxActor_Statics; \
public: \
	DECLARE_CLASS(APartitionBoxActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(APartitionBoxActor)


#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APartitionBoxActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APartitionBoxActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APartitionBoxActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APartitionBoxActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APartitionBoxActor(APartitionBoxActor&&); \
	NO_API APartitionBoxActor(const APartitionBoxActor&); \
public:


#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APartitionBoxActor(APartitionBoxActor&&); \
	NO_API APartitionBoxActor(const APartitionBoxActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APartitionBoxActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APartitionBoxActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APartitionBoxActor)


#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Box() { return STRUCT_OFFSET(APartitionBoxActor, Box); } \
	FORCEINLINE static uint32 __PPO__SharedRoot() { return STRUCT_OFFSET(APartitionBoxActor, SharedRoot); }


#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_21_PROLOG
#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_INCLASS \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class APartitionBoxActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_CustomActors_PartitionBoxActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
