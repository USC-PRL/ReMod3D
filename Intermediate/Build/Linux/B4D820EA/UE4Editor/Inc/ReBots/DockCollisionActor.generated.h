// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef REBOTS_DockCollisionActor_generated_h
#error "DockCollisionActor.generated.h already included, missing '#pragma once' in DockCollisionActor.h"
#endif
#define REBOTS_DockCollisionActor_generated_h

#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execStartOverlap) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_ThisComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->StartOverlap(Z_Param_ThisComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execStartOverlap) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_ThisComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_PROPERTY(UIntProperty,Z_Param_OtherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->StartOverlap(Z_Param_ThisComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	}


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADockCollisionActor(); \
	friend struct Z_Construct_UClass_ADockCollisionActor_Statics; \
public: \
	DECLARE_CLASS(ADockCollisionActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ADockCollisionActor)


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_INCLASS \
private: \
	static void StaticRegisterNativesADockCollisionActor(); \
	friend struct Z_Construct_UClass_ADockCollisionActor_Statics; \
public: \
	DECLARE_CLASS(ADockCollisionActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ADockCollisionActor)


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADockCollisionActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADockCollisionActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADockCollisionActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADockCollisionActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADockCollisionActor(ADockCollisionActor&&); \
	NO_API ADockCollisionActor(const ADockCollisionActor&); \
public:


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADockCollisionActor(ADockCollisionActor&&); \
	NO_API ADockCollisionActor(const ADockCollisionActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADockCollisionActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADockCollisionActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADockCollisionActor)


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__BoxComponent() { return STRUCT_OFFSET(ADockCollisionActor, BoxComponent); }


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_15_PROLOG
#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_INCLASS \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class ADockCollisionActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_CustomActors_DockCollisionActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
