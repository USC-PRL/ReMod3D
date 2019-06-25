// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/ReBotsSimulatorGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeReBotsSimulatorGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AReBotsSimulatorGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AReBotsSimulatorGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void AReBotsSimulatorGameMode::StaticRegisterNativesAReBotsSimulatorGameMode()
	{
	}
	UClass* Z_Construct_UClass_AReBotsSimulatorGameMode_NoRegister()
	{
		return AReBotsSimulatorGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AReBotsSimulatorGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AReBotsSimulatorGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReBotsSimulatorGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/ReBotsSimulatorGameMode.h" },
		{ "ModuleRelativePath", "GameModes/ReBotsSimulatorGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AReBotsSimulatorGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AReBotsSimulatorGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AReBotsSimulatorGameMode_Statics::ClassParams = {
		&AReBotsSimulatorGameMode::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AReBotsSimulatorGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AReBotsSimulatorGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AReBotsSimulatorGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AReBotsSimulatorGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AReBotsSimulatorGameMode, 3740544995);
	template<> REBOTS_API UClass* StaticClass<AReBotsSimulatorGameMode>()
	{
		return AReBotsSimulatorGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AReBotsSimulatorGameMode(Z_Construct_UClass_AReBotsSimulatorGameMode, &AReBotsSimulatorGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("AReBotsSimulatorGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AReBotsSimulatorGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
