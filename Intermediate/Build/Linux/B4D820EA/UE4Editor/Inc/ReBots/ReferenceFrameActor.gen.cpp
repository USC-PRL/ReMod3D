// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/CustomActors/ReferenceFrameActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeReferenceFrameActor() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_AReferenceFrameActor_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_AReferenceFrameActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void AReferenceFrameActor::StaticRegisterNativesAReferenceFrameActor()
	{
	}
	UClass* Z_Construct_UClass_AReferenceFrameActor_NoRegister()
	{
		return AReferenceFrameActor::StaticClass();
	}
	struct Z_Construct_UClass_AReferenceFrameActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SharedRootComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SharedRootComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OriginSphere_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OriginSphere;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZCap_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ZCap;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_YCap_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_YCap;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_XCap_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_XCap;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ZAxis_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ZAxis;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_YAxis_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_YAxis;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_XAxis_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_XAxis;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AReferenceFrameActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "@class AReferenceFrameActor\n@brief represents a visualization of a reference frame" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_SharedRootComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "< z axis" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_SharedRootComponent = { "SharedRootComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, SharedRootComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_SharedRootComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_SharedRootComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_OriginSphere_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "< z axis cap" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_OriginSphere = { "OriginSphere", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, OriginSphere), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_OriginSphere_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_OriginSphere_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZCap_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "< y axis cap" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZCap = { "ZCap", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, ZCap), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZCap_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZCap_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YCap_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "< x axis cap" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YCap = { "YCap", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, YCap), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YCap_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YCap_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XCap_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "< z axis" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XCap = { "XCap", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, XCap), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XCap_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XCap_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZAxis_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "< y axis" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZAxis = { "ZAxis", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, ZAxis), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZAxis_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZAxis_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YAxis_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
		{ "ToolTip", "< x axis" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YAxis = { "YAxis", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, YAxis), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YAxis_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YAxis_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XAxis_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "FrameBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/ReferenceFrameActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XAxis = { "XAxis", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AReferenceFrameActor, XAxis), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XAxis_MetaData, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XAxis_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AReferenceFrameActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_SharedRootComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_OriginSphere,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZCap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YCap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XCap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_ZAxis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_YAxis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AReferenceFrameActor_Statics::NewProp_XAxis,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AReferenceFrameActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AReferenceFrameActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AReferenceFrameActor_Statics::ClassParams = {
		&AReferenceFrameActor::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AReferenceFrameActor_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AReferenceFrameActor_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AReferenceFrameActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AReferenceFrameActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AReferenceFrameActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AReferenceFrameActor, 1281268291);
	template<> REBOTS_API UClass* StaticClass<AReferenceFrameActor>()
	{
		return AReferenceFrameActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AReferenceFrameActor(Z_Construct_UClass_AReferenceFrameActor, &AReferenceFrameActor::StaticClass, TEXT("/Script/ReBots"), TEXT("AReferenceFrameActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AReferenceFrameActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
