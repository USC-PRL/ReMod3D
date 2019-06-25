// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/CustomActors/DirectionActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDirectionActor() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ADirectionActor_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ADirectionActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
// End Cross Module References
	void ADirectionActor::StaticRegisterNativesADirectionActor()
	{
	}
	UClass* Z_Construct_UClass_ADirectionActor_NoRegister()
	{
		return ADirectionActor::StaticClass();
	}
	struct Z_Construct_UClass_ADirectionActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OriginSphere_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OriginSphere;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SharedRootComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SharedRootComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_XCap_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_XCap;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_XAxis_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_XAxis;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADirectionActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADirectionActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CustomActors/DirectionActor.h" },
		{ "ModuleRelativePath", "CustomActors/DirectionActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADirectionActor_Statics::NewProp_OriginSphere_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/DirectionActor.h" },
		{ "ToolTip", "< shared root" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADirectionActor_Statics::NewProp_OriginSphere = { "OriginSphere", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADirectionActor, OriginSphere), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADirectionActor_Statics::NewProp_OriginSphere_MetaData, ARRAY_COUNT(Z_Construct_UClass_ADirectionActor_Statics::NewProp_OriginSphere_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADirectionActor_Statics::NewProp_SharedRootComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/DirectionActor.h" },
		{ "ToolTip", "< x axis cap" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADirectionActor_Statics::NewProp_SharedRootComponent = { "SharedRootComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADirectionActor, SharedRootComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADirectionActor_Statics::NewProp_SharedRootComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_ADirectionActor_Statics::NewProp_SharedRootComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADirectionActor_Statics::NewProp_XCap_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/DirectionActor.h" },
		{ "ToolTip", "< x axis" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADirectionActor_Statics::NewProp_XCap = { "XCap", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADirectionActor, XCap), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADirectionActor_Statics::NewProp_XCap_MetaData, ARRAY_COUNT(Z_Construct_UClass_ADirectionActor_Statics::NewProp_XCap_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADirectionActor_Statics::NewProp_XAxis_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/DirectionActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADirectionActor_Statics::NewProp_XAxis = { "XAxis", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADirectionActor, XAxis), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADirectionActor_Statics::NewProp_XAxis_MetaData, ARRAY_COUNT(Z_Construct_UClass_ADirectionActor_Statics::NewProp_XAxis_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADirectionActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADirectionActor_Statics::NewProp_OriginSphere,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADirectionActor_Statics::NewProp_SharedRootComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADirectionActor_Statics::NewProp_XCap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADirectionActor_Statics::NewProp_XAxis,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADirectionActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADirectionActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADirectionActor_Statics::ClassParams = {
		&ADirectionActor::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ADirectionActor_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_ADirectionActor_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ADirectionActor_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ADirectionActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADirectionActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADirectionActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADirectionActor, 2913138309);
	template<> REBOTS_API UClass* StaticClass<ADirectionActor>()
	{
		return ADirectionActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADirectionActor(Z_Construct_UClass_ADirectionActor, &ADirectionActor::StaticClass, TEXT("/Script/ReBots"), TEXT("ADirectionActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADirectionActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
