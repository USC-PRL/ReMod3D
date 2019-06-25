// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_BoundingSphere_generated_h
#error "BoundingSphere.generated.h already included, missing '#pragma once' in BoundingSphere.h"
#endif
#define REBOTS_BoundingSphere_generated_h

#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABoundingSphere(); \
	friend struct Z_Construct_UClass_ABoundingSphere_Statics; \
public: \
	DECLARE_CLASS(ABoundingSphere, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ABoundingSphere)


#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_INCLASS \
private: \
	static void StaticRegisterNativesABoundingSphere(); \
	friend struct Z_Construct_UClass_ABoundingSphere_Statics; \
public: \
	DECLARE_CLASS(ABoundingSphere, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ABoundingSphere)


#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ABoundingSphere(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ABoundingSphere) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABoundingSphere); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABoundingSphere); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABoundingSphere(ABoundingSphere&&); \
	NO_API ABoundingSphere(const ABoundingSphere&); \
public:


#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABoundingSphere(ABoundingSphere&&); \
	NO_API ABoundingSphere(const ABoundingSphere&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABoundingSphere); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABoundingSphere); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABoundingSphere)


#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Sphere() { return STRUCT_OFFSET(ABoundingSphere, Sphere); }


#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_20_PROLOG
#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_INCLASS \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class ABoundingSphere>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_CustomActors_BoundingSphere_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
