// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef REBOTS_SuperBotModule_generated_h
#error "SuperBotModule.generated.h already included, missing '#pragma once' in SuperBotModule.h"
#endif
#define REBOTS_SuperBotModule_generated_h

#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_RPC_WRAPPERS
#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_RPC_WRAPPERS_NO_PURE_DECLS
#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASuperBotModule(); \
	friend struct Z_Construct_UClass_ASuperBotModule_Statics; \
public: \
	DECLARE_CLASS(ASuperBotModule, AModularRobot, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ASuperBotModule)


#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_INCLASS \
private: \
	static void StaticRegisterNativesASuperBotModule(); \
	friend struct Z_Construct_UClass_ASuperBotModule_Statics; \
public: \
	DECLARE_CLASS(ASuperBotModule, AModularRobot, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ReBots"), NO_API) \
	DECLARE_SERIALIZER(ASuperBotModule)


#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASuperBotModule(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASuperBotModule) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASuperBotModule); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASuperBotModule); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASuperBotModule(ASuperBotModule&&); \
	NO_API ASuperBotModule(const ASuperBotModule&); \
public:


#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASuperBotModule(ASuperBotModule&&); \
	NO_API ASuperBotModule(const ASuperBotModule&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASuperBotModule); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASuperBotModule); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASuperBotModule)


#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__MasterInner() { return STRUCT_OFFSET(ASuperBotModule, MasterInner); } \
	FORCEINLINE static uint32 __PPO__MasterOuter() { return STRUCT_OFFSET(ASuperBotModule, MasterOuter); } \
	FORCEINLINE static uint32 __PPO__SlaveInner() { return STRUCT_OFFSET(ASuperBotModule, SlaveInner); } \
	FORCEINLINE static uint32 __PPO__SlaveOuter() { return STRUCT_OFFSET(ASuperBotModule, SlaveOuter); } \
	FORCEINLINE static uint32 __PPO__InnerJoint() { return STRUCT_OFFSET(ASuperBotModule, InnerJoint); } \
	FORCEINLINE static uint32 __PPO__MasterJoint() { return STRUCT_OFFSET(ASuperBotModule, MasterJoint); } \
	FORCEINLINE static uint32 __PPO__SlaveJoint() { return STRUCT_OFFSET(ASuperBotModule, SlaveJoint); } \
	FORCEINLINE static uint32 __PPO__FrontDock() { return STRUCT_OFFSET(ASuperBotModule, FrontDock); } \
	FORCEINLINE static uint32 __PPO__BackDock() { return STRUCT_OFFSET(ASuperBotModule, BackDock); } \
	FORCEINLINE static uint32 __PPO__LeftDock() { return STRUCT_OFFSET(ASuperBotModule, LeftDock); } \
	FORCEINLINE static uint32 __PPO__RightDock() { return STRUCT_OFFSET(ASuperBotModule, RightDock); } \
	FORCEINLINE static uint32 __PPO__UpDock() { return STRUCT_OFFSET(ASuperBotModule, UpDock); } \
	FORCEINLINE static uint32 __PPO__DownDock() { return STRUCT_OFFSET(ASuperBotModule, DownDock); } \
	FORCEINLINE static uint32 __PPO__BehaviorName() { return STRUCT_OFFSET(ASuperBotModule, BehaviorName); } \
	FORCEINLINE static uint32 __PPO__RemoteControlMode() { return STRUCT_OFFSET(ASuperBotModule, RemoteControlMode); } \
	FORCEINLINE static uint32 __PPO__RenderDockFrames() { return STRUCT_OFFSET(ASuperBotModule, RenderDockFrames); } \
	FORCEINLINE static uint32 __PPO__RenderModuleFrame() { return STRUCT_OFFSET(ASuperBotModule, RenderModuleFrame); } \
	FORCEINLINE static uint32 __PPO__RenderKGFramesModules() { return STRUCT_OFFSET(ASuperBotModule, RenderKGFramesModules); } \
	FORCEINLINE static uint32 __PPO__RenderBoundingBoxes() { return STRUCT_OFFSET(ASuperBotModule, RenderBoundingBoxes); } \
	FORCEINLINE static uint32 __PPO__BehaviorMode() { return STRUCT_OFFSET(ASuperBotModule, BehaviorMode); } \
	FORCEINLINE static uint32 __PPO__AutoDocking() { return STRUCT_OFFSET(ASuperBotModule, AutoDocking); } \
	FORCEINLINE static uint32 __PPO__RenderDockCollisions() { return STRUCT_OFFSET(ASuperBotModule, RenderDockCollisions); } \
	FORCEINLINE static uint32 __PPO__RenderTargetTransform() { return STRUCT_OFFSET(ASuperBotModule, RenderTargetTransform); } \
	FORCEINLINE static uint32 __PPO__RenderFinalFK() { return STRUCT_OFFSET(ASuperBotModule, RenderFinalFK); } \
	FORCEINLINE static uint32 __PPO__RenderBaseFrame() { return STRUCT_OFFSET(ASuperBotModule, RenderBaseFrame); } \
	FORCEINLINE static uint32 __PPO__RenderGroundFrame() { return STRUCT_OFFSET(ASuperBotModule, RenderGroundFrame); } \
	FORCEINLINE static uint32 __PPO__BehaviorType() { return STRUCT_OFFSET(ASuperBotModule, BehaviorType); }


#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_118_PROLOG
#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_RPC_WRAPPERS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_INCLASS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_PRIVATE_PROPERTY_OFFSET \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_RPC_WRAPPERS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_INCLASS_NO_PURE_DECLS \
	ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h_127_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> REBOTS_API UClass* StaticClass<class ASuperBotModule>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ReMod3D_Source_ReBots_SuperBot_SuperBotModule_h


#define FOREACH_ENUM_BEHAVIORTYPE(op) \
	op(B_TWIST) \
	op(B_CATERPILLAR) \
	op(B_FK) \
	op(B_FK_IK) \
	op(B_6DDOCK) \
	op(B_MODMANIPQ) \
	op(B_RECONF) \
	op(B_RECONF2) \
	op(B_SNAKEIK) \
	op(B_RECONFIK) \
	op(B_TREEWALK) \
	op(B_STACKTOPLANE) \
	op(B_DIK) \
	op(B_DIST_KINEMATICS) \
	op(B_THAT) \
	op(B_NONE) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
