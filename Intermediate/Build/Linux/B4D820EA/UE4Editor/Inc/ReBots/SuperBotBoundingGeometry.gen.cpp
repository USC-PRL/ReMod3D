// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/CustomActors/SuperBotBoundingGeometry.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSuperBotBoundingGeometry() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ASuperBotBoundingGeometry_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ASuperBotBoundingGeometry();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ReBots();
// End Cross Module References
	void ASuperBotBoundingGeometry::StaticRegisterNativesASuperBotBoundingGeometry()
	{
	}
	UClass* Z_Construct_UClass_ASuperBotBoundingGeometry_NoRegister()
	{
		return ASuperBotBoundingGeometry::StaticClass();
	}
	struct Z_Construct_UClass_ASuperBotBoundingGeometry_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASuperBotBoundingGeometry_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotBoundingGeometry_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CustomActors/SuperBotBoundingGeometry.h" },
		{ "ModuleRelativePath", "CustomActors/SuperBotBoundingGeometry.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASuperBotBoundingGeometry_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASuperBotBoundingGeometry>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASuperBotBoundingGeometry_Statics::ClassParams = {
		&ASuperBotBoundingGeometry::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ASuperBotBoundingGeometry_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ASuperBotBoundingGeometry_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASuperBotBoundingGeometry()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASuperBotBoundingGeometry_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASuperBotBoundingGeometry, 855966327);
	template<> REBOTS_API UClass* StaticClass<ASuperBotBoundingGeometry>()
	{
		return ASuperBotBoundingGeometry::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASuperBotBoundingGeometry(Z_Construct_UClass_ASuperBotBoundingGeometry, &ASuperBotBoundingGeometry::StaticClass, TEXT("/Script/ReBots"), TEXT("ASuperBotBoundingGeometry"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASuperBotBoundingGeometry);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
