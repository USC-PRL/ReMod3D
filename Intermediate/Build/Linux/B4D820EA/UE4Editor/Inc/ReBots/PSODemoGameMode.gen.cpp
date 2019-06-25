// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/PSODemoGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePSODemoGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_APSODemoGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_APSODemoGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void APSODemoGameMode::StaticRegisterNativesAPSODemoGameMode()
	{
	}
	UClass* Z_Construct_UClass_APSODemoGameMode_NoRegister()
	{
		return APSODemoGameMode::StaticClass();
	}
	struct Z_Construct_UClass_APSODemoGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APSODemoGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APSODemoGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/PSODemoGameMode.h" },
		{ "ModuleRelativePath", "GameModes/PSODemoGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "@class PSODemoGameMode\n@brief pso demo game mode" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APSODemoGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APSODemoGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_APSODemoGameMode_Statics::ClassParams = {
		&APSODemoGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_APSODemoGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_APSODemoGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APSODemoGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_APSODemoGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APSODemoGameMode, 2956344107);
	template<> REBOTS_API UClass* StaticClass<APSODemoGameMode>()
	{
		return APSODemoGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_APSODemoGameMode(Z_Construct_UClass_APSODemoGameMode, &APSODemoGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("APSODemoGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APSODemoGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
