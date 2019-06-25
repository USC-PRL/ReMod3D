// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/ReBotsPileGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeReBotsPileGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AReBotsPileGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AReBotsPileGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void AReBotsPileGameMode::StaticRegisterNativesAReBotsPileGameMode()
	{
	}
	UClass* Z_Construct_UClass_AReBotsPileGameMode_NoRegister()
	{
		return AReBotsPileGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AReBotsPileGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AReBotsPileGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReBotsPileGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/ReBotsPileGameMode.h" },
		{ "ModuleRelativePath", "GameModes/ReBotsPileGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AReBotsPileGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AReBotsPileGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AReBotsPileGameMode_Statics::ClassParams = {
		&AReBotsPileGameMode::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AReBotsPileGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AReBotsPileGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AReBotsPileGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AReBotsPileGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AReBotsPileGameMode, 2647567678);
	template<> REBOTS_API UClass* StaticClass<AReBotsPileGameMode>()
	{
		return AReBotsPileGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AReBotsPileGameMode(Z_Construct_UClass_AReBotsPileGameMode, &AReBotsPileGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("AReBotsPileGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AReBotsPileGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
