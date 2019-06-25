// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_SmoresModule_generated_h
#error "SmoresModule.generated.h already included, missing '#pragma once' in SmoresModule.h"
#endif
#define REBOTS_SmoresModule_generated_h

#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASmoresModule(); \
	friend struct Z_Construct_UClass_ASmoresModule_Statics; \
public: \
	DECLARE_CLASS(ASmoresModule, AModularRobot, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ASmoresModule)


#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_INCLASS \
private: \
	static void StaticRegisterNativesASmoresModule(); \
	friend struct Z_Construct_UClass_ASmoresModule_Statics; \
public: \
	DECLARE_CLASS(ASmoresModule, AModularRobot, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ASmoresModule)


#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASmoresModule(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASmoresModule) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASmoresModule); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASmoresModule); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASmoresModule(ASmoresModule&&); \
	NO_API ASmoresModule(const ASmoresModule&); \
public:


#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASmoresModule(ASmoresModule&&); \
	NO_API ASmoresModule(const ASmoresModule&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASmoresModule); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASmoresModule); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASmoresModule)


#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SmoresInner() { return STRUCT_OFFSET(ASmoresModule, SmoresInner); } \
	FORCEINLINE static uint32 __PPO__SmoresOuter() { return STRUCT_OFFSET(ASmoresModule, SmoresOuter); } \
	FORCEINLINE static uint32 __PPO__WheelFront() { return STRUCT_OFFSET(ASmoresModule, WheelFront); } \
	FORCEINLINE static uint32 __PPO__WheelBack() { return STRUCT_OFFSET(ASmoresModule, WheelBack); } \
	FORCEINLINE static uint32 __PPO__WheelLeft() { return STRUCT_OFFSET(ASmoresModule, WheelLeft); } \
	FORCEINLINE static uint32 __PPO__WheelRight() { return STRUCT_OFFSET(ASmoresModule, WheelRight); } \
	FORCEINLINE static uint32 __PPO__InnerJoint() { return STRUCT_OFFSET(ASmoresModule, InnerJoint); } \
	FORCEINLINE static uint32 __PPO__BackWheelJoint() { return STRUCT_OFFSET(ASmoresModule, BackWheelJoint); } \
	FORCEINLINE static uint32 __PPO__LeftWheelJoint() { return STRUCT_OFFSET(ASmoresModule, LeftWheelJoint); } \
	FORCEINLINE static uint32 __PPO__RightWheelJoint() { return STRUCT_OFFSET(ASmoresModule, RightWheelJoint); } \
	FORCEINLINE static uint32 __PPO__SmoresController() { return STRUCT_OFFSET(ASmoresModule, SmoresController); }


#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_59_PROLOG
#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_INCLASS \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_Smores_SmoresModule_h_62_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class ASmoresModule>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_Smores_SmoresModule_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
