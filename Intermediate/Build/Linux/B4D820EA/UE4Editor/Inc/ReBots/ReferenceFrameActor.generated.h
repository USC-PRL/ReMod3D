// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_ReferenceFrameActor_generated_h
#error "ReferenceFrameActor.generated.h already included, missing '#pragma once' in ReferenceFrameActor.h"
#endif
#define REBOTS_ReferenceFrameActor_generated_h

#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAReferenceFrameActor(); \
	friend struct Z_Construct_UClass_AReferenceFrameActor_Statics; \
public: \
	DECLARE_CLASS(AReferenceFrameActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AReferenceFrameActor)


#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAReferenceFrameActor(); \
	friend struct Z_Construct_UClass_AReferenceFrameActor_Statics; \
public: \
	DECLARE_CLASS(AReferenceFrameActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AReferenceFrameActor)


#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AReferenceFrameActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AReferenceFrameActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AReferenceFrameActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AReferenceFrameActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AReferenceFrameActor(AReferenceFrameActor&&); \
	NO_API AReferenceFrameActor(const AReferenceFrameActor&); \
public:


#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AReferenceFrameActor(AReferenceFrameActor&&); \
	NO_API AReferenceFrameActor(const AReferenceFrameActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AReferenceFrameActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AReferenceFrameActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AReferenceFrameActor)


#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__XAxis() { return STRUCT_OFFSET(AReferenceFrameActor, XAxis); } \
	FORCEINLINE static uint32 __PPO__YAxis() { return STRUCT_OFFSET(AReferenceFrameActor, YAxis); } \
	FORCEINLINE static uint32 __PPO__ZAxis() { return STRUCT_OFFSET(AReferenceFrameActor, ZAxis); } \
	FORCEINLINE static uint32 __PPO__XCap() { return STRUCT_OFFSET(AReferenceFrameActor, XCap); } \
	FORCEINLINE static uint32 __PPO__YCap() { return STRUCT_OFFSET(AReferenceFrameActor, YCap); } \
	FORCEINLINE static uint32 __PPO__ZCap() { return STRUCT_OFFSET(AReferenceFrameActor, ZCap); } \
	FORCEINLINE static uint32 __PPO__OriginSphere() { return STRUCT_OFFSET(AReferenceFrameActor, OriginSphere); } \
	FORCEINLINE static uint32 __PPO__SharedRootComponent() { return STRUCT_OFFSET(AReferenceFrameActor, SharedRootComponent); }


#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_11_PROLOG
#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_INCLASS \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class AReferenceFrameActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_CustomActors_ReferenceFrameActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
