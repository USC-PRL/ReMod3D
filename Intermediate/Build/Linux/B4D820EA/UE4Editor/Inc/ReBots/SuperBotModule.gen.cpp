// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/SuperBot/SuperBotModule.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSuperBotModule() {}
// Cross Module References
	REBOTS_API UEnum* Z_Construct_UEnum_ReBots_BehaviorType();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	REBOTS_API UClass* Z_Construct_UClass_ASuperBotModule_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ASuperBotModule();
	REBOTS_API UClass* Z_Construct_UClass_AModularRobot();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister();
// End Cross Module References
	static UEnum* BehaviorType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_ReBots_BehaviorType, Z_Construct_UPackage__Script_ReBots(), TEXT("BehaviorType"));
		}
		return Singleton;
	}
	template<> REBOTS_API UEnum* StaticEnum<BehaviorType>()
	{
		return BehaviorType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_BehaviorType(BehaviorType_StaticEnum, TEXT("/Script/ReBots"), TEXT("BehaviorType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_ReBots_BehaviorType_Hash() { return 411127286U; }
	UEnum* Z_Construct_UEnum_ReBots_BehaviorType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_ReBots();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("BehaviorType"), 0, Get_Z_Construct_UEnum_ReBots_BehaviorType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "B_TWIST", (int64)B_TWIST },
				{ "B_CATERPILLAR", (int64)B_CATERPILLAR },
				{ "B_FK", (int64)B_FK },
				{ "B_FK_IK", (int64)B_FK_IK },
				{ "B_6DDOCK", (int64)B_6DDOCK },
				{ "B_MODMANIPQ", (int64)B_MODMANIPQ },
				{ "B_RECONF", (int64)B_RECONF },
				{ "B_RECONF2", (int64)B_RECONF2 },
				{ "B_SNAKEIK", (int64)B_SNAKEIK },
				{ "B_RECONFIK", (int64)B_RECONFIK },
				{ "B_TREEWALK", (int64)B_TREEWALK },
				{ "B_STACKTOPLANE", (int64)B_STACKTOPLANE },
				{ "B_DIK", (int64)B_DIK },
				{ "B_DIST_KINEMATICS", (int64)B_DIST_KINEMATICS },
				{ "B_THAT", (int64)B_THAT },
				{ "B_NONE", (int64)B_NONE },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "B_6DDOCK.DisplayName", "6D Docking" },
				{ "B_CATERPILLAR.DisplayName", "Caterpillar" },
				{ "B_DIK.DisplayName", "DistributedIK" },
				{ "B_DIST_KINEMATICS.DisplayName", "DistributedKinematics" },
				{ "B_FK.DisplayName", "Forward Kinematics" },
				{ "B_FK_IK.DisplayName", "Foward/Inverse Kinematics" },
				{ "B_MODMANIPQ.DisplayName", "ModManipQ" },
				{ "B_NONE.DisplayName", "None" },
				{ "B_RECONF.DisplayName", "ReconfQ" },
				{ "B_RECONF2.DisplayName", "ReconfQ2" },
				{ "B_RECONFIK.DisplayName", "ReconfIK" },
				{ "B_SNAKEIK.DisplayName", "SnakeIK" },
				{ "B_STACKTOPLANE.DisplayName", "StackToPlane" },
				{ "B_THAT.DisplayName", "Distributed That" },
				{ "B_TREEWALK.DisplayName", "TreeWalk" },
				{ "B_TWIST.DisplayName", "Twist" },
				{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
				{ "ToolTip", "@enum BehaviorType\n@brief behavior type for SuperBot" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_ReBots,
				nullptr,
				"BehaviorType",
				"BehaviorType",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void ASuperBotModule::StaticRegisterNativesASuperBotModule()
	{
	}
	UClass* Z_Construct_UClass_ASuperBotModule_NoRegister()
	{
		return ASuperBotModule::StaticClass();
	}
	struct Z_Construct_UClass_ASuperBotModule_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BehaviorType_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_BehaviorType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderGroundFrame_MetaData[];
#endif
		static void NewProp_RenderGroundFrame_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderGroundFrame;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderBaseFrame_MetaData[];
#endif
		static void NewProp_RenderBaseFrame_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderBaseFrame;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderFinalFK_MetaData[];
#endif
		static void NewProp_RenderFinalFK_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderFinalFK;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderTargetTransform_MetaData[];
#endif
		static void NewProp_RenderTargetTransform_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderTargetTransform;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderDockCollisions_MetaData[];
#endif
		static void NewProp_RenderDockCollisions_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderDockCollisions;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AutoDocking_MetaData[];
#endif
		static void NewProp_AutoDocking_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_AutoDocking;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BehaviorMode_MetaData[];
#endif
		static void NewProp_BehaviorMode_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_BehaviorMode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderBoundingBoxes_MetaData[];
#endif
		static void NewProp_RenderBoundingBoxes_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderBoundingBoxes;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderKGFramesModules_MetaData[];
#endif
		static void NewProp_RenderKGFramesModules_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderKGFramesModules;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderModuleFrame_MetaData[];
#endif
		static void NewProp_RenderModuleFrame_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderModuleFrame;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderDockFrames_MetaData[];
#endif
		static void NewProp_RenderDockFrames_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RenderDockFrames;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RemoteControlMode_MetaData[];
#endif
		static void NewProp_RemoteControlMode_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RemoteControlMode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BehaviorName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_BehaviorName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DownDock_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DownDock;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UpDock_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_UpDock;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RightDock_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RightDock;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LeftDock_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LeftDock;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BackDock_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BackDock;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FrontDock_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FrontDock;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SlaveJoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SlaveJoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MasterJoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MasterJoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InnerJoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InnerJoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SlaveOuter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SlaveOuter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SlaveInner_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SlaveInner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MasterOuter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MasterOuter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MasterInner_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MasterInner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASuperBotModule_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AModularRobot,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SuperBot/SuperBotModule.h" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorType_MetaData[] = {
		{ "Category", "Behavior" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "The type of object the behavior is" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorType = { "BehaviorType", nullptr, (EPropertyFlags)0x0020080000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, BehaviorType), Z_Construct_UEnum_ReBots_BehaviorType, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorType_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderGroundFrame_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotMind" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render end effector?" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderGroundFrame_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderGroundFrame = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderGroundFrame = { "RenderGroundFrame", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderGroundFrame_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderGroundFrame_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderGroundFrame_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBaseFrame_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotMind" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render end effector?" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBaseFrame_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderBaseFrame = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBaseFrame = { "RenderBaseFrame", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBaseFrame_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBaseFrame_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBaseFrame_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderFinalFK_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotMind" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render docking boxes?" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderFinalFK_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderFinalFK = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderFinalFK = { "RenderFinalFK", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderFinalFK_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderFinalFK_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderFinalFK_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderTargetTransform_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotMind" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render docking boxes?" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderTargetTransform_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderTargetTransform = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderTargetTransform = { "RenderTargetTransform", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderTargetTransform_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderTargetTransform_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderTargetTransform_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockCollisions_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotMind" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< auto docking ?" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockCollisions_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderDockCollisions = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockCollisions = { "RenderDockCollisions", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockCollisions_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockCollisions_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockCollisions_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_AutoDocking_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotMind" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< in behavior mode or manual control mode" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_AutoDocking_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->AutoDocking = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_AutoDocking = { "AutoDocking", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_AutoDocking_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_AutoDocking_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_AutoDocking_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorMode_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotMind" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render kinematic graph frames for modules docks f and b" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorMode_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->BehaviorMode = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorMode = { "BehaviorMode", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorMode_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorMode_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorMode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBoundingBoxes_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render kinematic graph frames for modules" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBoundingBoxes_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderBoundingBoxes = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBoundingBoxes = { "RenderBoundingBoxes", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBoundingBoxes_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBoundingBoxes_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBoundingBoxes_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderKGFramesModules_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render frame or not" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderKGFramesModules_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderKGFramesModules = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderKGFramesModules = { "RenderKGFramesModules", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderKGFramesModules_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderKGFramesModules_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderKGFramesModules_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderModuleFrame_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< render frame or not" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderModuleFrame_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderModuleFrame = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderModuleFrame = { "RenderModuleFrame", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderModuleFrame_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderModuleFrame_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderModuleFrame_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockFrames_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< are we in remote control mode?" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockFrames_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RenderDockFrames = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockFrames = { "RenderDockFrames", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockFrames_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockFrames_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockFrames_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RemoteControlMode_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< name of behavior" },
	};
#endif
	void Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RemoteControlMode_SetBit(void* Obj)
	{
		((ASuperBotModule*)Obj)->RemoteControlMode = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RemoteControlMode = { "RemoteControlMode", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASuperBotModule), &Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RemoteControlMode_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RemoteControlMode_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RemoteControlMode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorName_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< front dock component" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorName = { "BehaviorName", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, BehaviorName), METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorName_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_DownDock_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< front dock component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_DownDock = { "DownDock", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, DownDock), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_DownDock_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_DownDock_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_UpDock_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< front dock component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_UpDock = { "UpDock", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, UpDock), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_UpDock_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_UpDock_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RightDock_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< front dock component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RightDock = { "RightDock", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, RightDock), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RightDock_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RightDock_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_LeftDock_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< front dock component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_LeftDock = { "LeftDock", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, LeftDock), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_LeftDock_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_LeftDock_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BackDock_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< front dock component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BackDock = { "BackDock", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, BackDock), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BackDock_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BackDock_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_FrontDock_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< slave joint between slave outer and inner" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_FrontDock = { "FrontDock", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, FrontDock), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_FrontDock_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_FrontDock_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveJoint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< master joint between master outer and inner" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveJoint = { "SlaveJoint", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, SlaveJoint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveJoint_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveJoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterJoint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< inner joint (between slave inner and master inner" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterJoint = { "MasterJoint", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, MasterJoint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterJoint_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterJoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_InnerJoint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< slave outer component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_InnerJoint = { "InnerJoint", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, InnerJoint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_InnerJoint_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_InnerJoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveOuter_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< slave inner component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveOuter = { "SlaveOuter", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, SlaveOuter), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveOuter_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveOuter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveInner_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< master outer component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveInner = { "SlaveInner", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, SlaveInner), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveInner_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveInner_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterOuter_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
		{ "ToolTip", "< master inner component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterOuter = { "MasterOuter", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, MasterOuter), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterOuter_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterOuter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterInner_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotModule.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterInner = { "MasterInner", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotModule, MasterInner), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterInner_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterInner_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASuperBotModule_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderGroundFrame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBaseFrame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderFinalFK,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderTargetTransform,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockCollisions,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_AutoDocking,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderBoundingBoxes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderKGFramesModules,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderModuleFrame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RenderDockFrames,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RemoteControlMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BehaviorName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_DownDock,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_UpDock,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_RightDock,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_LeftDock,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_BackDock,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_FrontDock,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveJoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterJoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_InnerJoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveOuter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_SlaveInner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterOuter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotModule_Statics::NewProp_MasterInner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASuperBotModule_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASuperBotModule>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASuperBotModule_Statics::ClassParams = {
		&ASuperBotModule::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASuperBotModule_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ASuperBotModule_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ASuperBotModule_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASuperBotModule()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASuperBotModule_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASuperBotModule, 2559334177);
	template<> REBOTS_API UClass* StaticClass<ASuperBotModule>()
	{
		return ASuperBotModule::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASuperBotModule(Z_Construct_UClass_ASuperBotModule, &ASuperBotModule::StaticClass, TEXT("/Script/ReBots"), TEXT("ASuperBotModule"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASuperBotModule);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
