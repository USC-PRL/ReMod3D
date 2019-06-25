// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/ReBotsModuleGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeReBotsModuleGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AReBotsModuleGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AReBotsModuleGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void AReBotsModuleGameMode::StaticRegisterNativesAReBotsModuleGameMode()
	{
	}
	UClass* Z_Construct_UClass_AReBotsModuleGameMode_NoRegister()
	{
		return AReBotsModuleGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AReBotsModuleGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AReBotsModuleGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReBotsModuleGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/ReBotsModuleGameMode.h" },
		{ "ModuleRelativePath", "GameModes/ReBotsModuleGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AReBotsModuleGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AReBotsModuleGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AReBotsModuleGameMode_Statics::ClassParams = {
		&AReBotsModuleGameMode::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AReBotsModuleGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AReBotsModuleGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AReBotsModuleGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AReBotsModuleGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AReBotsModuleGameMode, 380402465);
	template<> REBOTS_API UClass* StaticClass<AReBotsModuleGameMode>()
	{
		return AReBotsModuleGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AReBotsModuleGameMode(Z_Construct_UClass_AReBotsModuleGameMode, &AReBotsModuleGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("AReBotsModuleGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AReBotsModuleGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
