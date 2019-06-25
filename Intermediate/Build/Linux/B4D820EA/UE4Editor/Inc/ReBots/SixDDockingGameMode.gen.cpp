// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/SixDDockingGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSixDDockingGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ASixDDockingGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ASixDDockingGameMode();
	REBOTS_API UClass* Z_Construct_UClass_AReBotsSimulatorGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void ASixDDockingGameMode::StaticRegisterNativesASixDDockingGameMode()
	{
	}
	UClass* Z_Construct_UClass_ASixDDockingGameMode_NoRegister()
	{
		return ASixDDockingGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ASixDDockingGameMode_Statics
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
	UObject* (*const Z_Construct_UClass_ASixDDockingGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AReBotsSimulatorGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASixDDockingGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/SixDDockingGameMode.h" },
		{ "ModuleRelativePath", "GameModes/SixDDockingGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "@class ASixDDockingGameMode\n@brief six d docking game mode" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASixDDockingGameMode_Statics::NewProp_ToMasterKinematics_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "GameModeKinematics" },
		{ "ModuleRelativePath", "GameModes/SixDDockingGameMode.h" },
		{ "ToolTip", "< current bounding spheres" },
	};
#endif
	void Z_Construct_UClass_ASixDDockingGameMode_Statics::NewProp_ToMasterKinematics_SetBit(void* Obj)
	{
		((ASixDDockingGameMode*)Obj)->ToMasterKinematics = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASixDDockingGameMode_Statics::NewProp_ToMasterKinematics = { "ToMasterKinematics", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASixDDockingGameMode), &Z_Construct_UClass_ASixDDockingGameMode_Statics::NewProp_ToMasterKinematics_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASixDDockingGameMode_Statics::NewProp_ToMasterKinematics_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASixDDockingGameMode_Statics::NewProp_ToMasterKinematics_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASixDDockingGameMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASixDDockingGameMode_Statics::NewProp_ToMasterKinematics,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASixDDockingGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASixDDockingGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASixDDockingGameMode_Statics::ClassParams = {
		&ASixDDockingGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASixDDockingGameMode_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_ASixDDockingGameMode_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ASixDDockingGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ASixDDockingGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASixDDockingGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASixDDockingGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASixDDockingGameMode, 2354888806);
	template<> REBOTS_API UClass* StaticClass<ASixDDockingGameMode>()
	{
		return ASixDDockingGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASixDDockingGameMode(Z_Construct_UClass_ASixDDockingGameMode, &ASixDDockingGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("ASixDDockingGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASixDDockingGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
