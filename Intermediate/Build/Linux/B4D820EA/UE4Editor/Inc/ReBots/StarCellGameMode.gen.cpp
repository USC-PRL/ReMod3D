// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/GameModes/StarCellGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStarCellGameMode() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AStarCellGameMode_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AStarCellGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void AStarCellGameMode::StaticRegisterNativesAStarCellGameMode()
	{
	}
	UClass* Z_Construct_UClass_AStarCellGameMode_NoRegister()
	{
		return AStarCellGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AStarCellGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AStarCellGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStarCellGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameModes/StarCellGameMode.h" },
		{ "ModuleRelativePath", "GameModes/StarCellGameMode.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "@class AStarCellGameMode\n@brief star cell game mode" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AStarCellGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStarCellGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AStarCellGameMode_Statics::ClassParams = {
		&AStarCellGameMode::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_AStarCellGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AStarCellGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AStarCellGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AStarCellGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AStarCellGameMode, 1285276202);
	template<> REBOTS_API UClass* StaticClass<AStarCellGameMode>()
	{
		return AStarCellGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AStarCellGameMode(Z_Construct_UClass_AStarCellGameMode, &AStarCellGameMode::StaticClass, TEXT("/Script/ReBots"), TEXT("AStarCellGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AStarCellGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
