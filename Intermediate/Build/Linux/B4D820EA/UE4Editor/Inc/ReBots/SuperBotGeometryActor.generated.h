// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_SuperBotGeometryActor_generated_h
#error "SuperBotGeometryActor.generated.h already included, missing '#pragma once' in SuperBotGeometryActor.h"
#endif
#define REBOTS_SuperBotGeometryActor_generated_h

#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASuperBotGeometryActor(); \
	friend struct Z_Construct_UClass_ASuperBotGeometryActor_Statics; \
public: \
	DECLARE_CLASS(ASuperBotGeometryActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ASuperBotGeometryActor)


#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_INCLASS \
private: \
	static void StaticRegisterNativesASuperBotGeometryActor(); \
	friend struct Z_Construct_UClass_ASuperBotGeometryActor_Statics; \
public: \
	DECLARE_CLASS(ASuperBotGeometryActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ASuperBotGeometryActor)


#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASuperBotGeometryActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASuperBotGeometryActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASuperBotGeometryActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASuperBotGeometryActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASuperBotGeometryActor(ASuperBotGeometryActor&&); \
	NO_API ASuperBotGeometryActor(const ASuperBotGeometryActor&); \
public:


#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASuperBotGeometryActor(ASuperBotGeometryActor&&); \
	NO_API ASuperBotGeometryActor(const ASuperBotGeometryActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASuperBotGeometryActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASuperBotGeometryActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASuperBotGeometryActor)


#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__InnerBoxMaster() { return STRUCT_OFFSET(ASuperBotGeometryActor, InnerBoxMaster); } \
	FORCEINLINE static uint32 __PPO__OuterBoxMaster() { return STRUCT_OFFSET(ASuperBotGeometryActor, OuterBoxMaster); } \
	FORCEINLINE static uint32 __PPO__OuterBoxSlave() { return STRUCT_OFFSET(ASuperBotGeometryActor, OuterBoxSlave); } \
	FORCEINLINE static uint32 __PPO__SharedRootComponent() { return STRUCT_OFFSET(ASuperBotGeometryActor, SharedRootComponent); }


#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_13_PROLOG
#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_INCLASS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class ASuperBotGeometryActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_SuperBot_SuperBotGeometryActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
