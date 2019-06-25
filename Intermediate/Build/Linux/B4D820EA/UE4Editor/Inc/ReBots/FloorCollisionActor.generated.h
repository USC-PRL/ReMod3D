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
#ifdef REBOTS_FloorCollisionActor_generated_h
#error "FloorCollisionActor.generated.h already included, missing '#pragma once' in FloorCollisionActor.h"
#endif
#define REBOTS_FloorCollisionActor_generated_h

#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_RPC_WRAPPERS \
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


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
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


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFloorCollisionActor(); \
	friend struct Z_Construct_UClass_AFloorCollisionActor_Statics; \
public: \
	DECLARE_CLASS(AFloorCollisionActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AFloorCollisionActor)


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_INCLASS \
private: \
	static void StaticRegisterNativesAFloorCollisionActor(); \
	friend struct Z_Construct_UClass_AFloorCollisionActor_Statics; \
public: \
	DECLARE_CLASS(AFloorCollisionActor, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(AFloorCollisionActor)


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AFloorCollisionActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AFloorCollisionActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFloorCollisionActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFloorCollisionActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFloorCollisionActor(AFloorCollisionActor&&); \
	NO_API AFloorCollisionActor(const AFloorCollisionActor&); \
public:


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFloorCollisionActor(AFloorCollisionActor&&); \
	NO_API AFloorCollisionActor(const AFloorCollisionActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFloorCollisionActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFloorCollisionActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFloorCollisionActor)


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__BoxComponent() { return STRUCT_OFFSET(AFloorCollisionActor, BoxComponent); }


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_16_PROLOG
#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_INCLASS \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class AFloorCollisionActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_CustomActors_FloorCollisionActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
