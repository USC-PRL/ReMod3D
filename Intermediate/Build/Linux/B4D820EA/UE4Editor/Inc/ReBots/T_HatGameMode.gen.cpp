// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/T_HatGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeT_HatGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AT_HatGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AT_HatGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void AT_HatGameMode::StaticRegisterNativesAT_HatGameMode()
	{
	}
	UClass* Z_Construct_UClass_AT_HatGameMode_NoRegister()
	{
		return AT_HatGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AT_HatGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AT_HatGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AT_HatGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/T_HatGameMode.h" },
		{ "ModuleRelativePath", "GameModes/T_HatGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AT_HatGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AT_HatGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AT_HatGameMode_Statics::ClassParams = {
		&AT_HatGameMode::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AT_HatGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AT_HatGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AT_HatGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AT_HatGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AT_HatGameMode, 292493827);
	template<> REBOTS_API UClass* StaticClass<AT_HatGameMode>()
	{
		return AT_HatGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AT_HatGameMode(Z_Construct_UClass_AT_HatGameMode, &AT_HatGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("AT_HatGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AT_HatGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
