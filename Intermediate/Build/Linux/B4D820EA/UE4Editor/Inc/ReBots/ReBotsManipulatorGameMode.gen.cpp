// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/ReBotsManipulatorGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeReBotsManipulatorGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AReBotsManipulatorGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AReBotsManipulatorGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void AReBotsManipulatorGameMode::StaticRegisterNativesAReBotsManipulatorGameMode()
	{
	}
	UClass* Z_Construct_UClass_AReBotsManipulatorGameMode_NoRegister()
	{
		return AReBotsManipulatorGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AReBotsManipulatorGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ToMasterKinematics_MetaData[];
#endif
		static void NewProp_ToMasterKinematics_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ToMasterKinematics;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/ReBotsManipulatorGameMode.h" },
		{ "ModuleRelativePath", "GameModes/ReBotsManipulatorGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "@class AReBotsManipulatorGameMode\n@brief manipulator game mode" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::NewProp_ToMasterKinematics_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "GameModeKinematics" },
		{ "ModuleRelativePath", "GameModes/ReBotsManipulatorGameMode.h" },
		{ "ToolTip", "< current bounding spheres" },
	};
#endif
	void Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::NewProp_ToMasterKinematics_SetBit(void* Obj)
	{
		((AReBotsManipulatorGameMode*)Obj)->ToMasterKinematics = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::NewProp_ToMasterKinematics = { "ToMasterKinematics", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AReBotsManipulatorGameMode), &Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::NewProp_ToMasterKinematics_SetBit, METADATA_PARAMS(Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::NewProp_ToMasterKinematics_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::NewProp_ToMasterKinematics_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::NewProp_ToMasterKinematics,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AReBotsManipulatorGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::ClassParams = {
		&AReBotsManipulatorGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AReBotsManipulatorGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AReBotsManipulatorGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AReBotsManipulatorGameMode, 3778125469);
	template<> REBOTS_API UClass* StaticClass<AReBotsManipulatorGameMode>()
	{
		return AReBotsManipulatorGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AReBotsManipulatorGameMode(Z_Construct_UClass_AReBotsManipulatorGameMode, &AReBotsManipulatorGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("AReBotsManipulatorGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AReBotsManipulatorGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
