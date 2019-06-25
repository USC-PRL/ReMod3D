// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/CustomActors/StackableObjectActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStackableObjectActor() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AStackableObjectActor_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AStackableObjectActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void AStackableObjectActor::StaticRegisterNativesAStackableObjectActor()
	{
	}
	UClass* Z_Construct_UClass_AStackableObjectActor_NoRegister()
	{
		return AStackableObjectActor::StaticClass();
	}
	struct Z_Construct_UClass_AStackableObjectActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Box_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Box;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AStackableObjectActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStackableObjectActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CustomActors/StackableObjectActor.h" },
		{ "ModuleRelativePath", "CustomActors/StackableObjectActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AStackableObjectActor_Statics::NewProp_Box_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "ParticleBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/StackableObjectActor.h" },
		{ "ToolTip", "< 3d scale of particle" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStackableObjectActor_Statics::NewProp_Box = { "Box", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AStackableObjectActor, Box), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AStackableObjectActor_Statics::NewProp_Box_MetaData, ARRAY_COUNT(Z_Construct_UClass_AStackableObjectActor_Statics::NewProp_Box_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AStackableObjectActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStackableObjectActor_Statics::NewProp_Box,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AStackableObjectActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStackableObjectActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AStackableObjectActor_Statics::ClassParams = {
		&AStackableObjectActor::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AStackableObjectActor_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AStackableObjectActor_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AStackableObjectActor_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AStackableObjectActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AStackableObjectActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AStackableObjectActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AStackableObjectActor, 892680290);
	template<> REBOTS_API UClass* StaticClass<AStackableObjectActor>()
	{
		return AStackableObjectActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AStackableObjectActor(Z_Construct_UClass_AStackableObjectActor, &AStackableObjectActor::StaticClass, TEXT("/Script/ReBots"), TEXT("AStackableObjectActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AStackableObjectActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
