// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/BranchBoundTestGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBranchBoundTestGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ABranchBoundTestGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ABranchBoundTestGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void ABranchBoundTestGameMode::StaticRegisterNativesABranchBoundTestGameMode()
	{
	}
	UClass* Z_Construct_UClass_ABranchBoundTestGameMode_NoRegister()
	{
		return ABranchBoundTestGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ABranchBoundTestGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABranchBoundTestGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABranchBoundTestGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/BranchBoundTestGameMode.h" },
		{ "ModuleRelativePath", "GameModes/BranchBoundTestGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "@class ABranchBoundTestGameMode\n@brief branch bound testing game mode" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABranchBoundTestGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABranchBoundTestGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ABranchBoundTestGameMode_Statics::ClassParams = {
		&ABranchBoundTestGameMode::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ABranchBoundTestGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ABranchBoundTestGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABranchBoundTestGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ABranchBoundTestGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ABranchBoundTestGameMode, 3453777011);
	template<> REBOTS_API UClass* StaticClass<ABranchBoundTestGameMode>()
	{
		return ABranchBoundTestGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ABranchBoundTestGameMode(Z_Construct_UClass_ABranchBoundTestGameMode, &ABranchBoundTestGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("ABranchBoundTestGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABranchBoundTestGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
