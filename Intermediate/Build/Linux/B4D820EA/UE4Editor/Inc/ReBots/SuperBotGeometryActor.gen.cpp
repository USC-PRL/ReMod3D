// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/SuperBot/SuperBotGeometryActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSuperBotGeometryActor() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ASuperBotGeometryActor_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ASuperBotGeometryActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void ASuperBotGeometryActor::StaticRegisterNativesASuperBotGeometryActor()
	{
	}
	UClass* Z_Construct_UClass_ASuperBotGeometryActor_NoRegister()
	{
		return ASuperBotGeometryActor::StaticClass();
	}
	struct Z_Construct_UClass_ASuperBotGeometryActor_Statics
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OuterBoxSlave_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OuterBoxSlave;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OuterBoxMaster_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OuterBoxMaster;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InnerBoxMaster_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InnerBoxMaster;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASuperBotGeometryActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotGeometryActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SuperBot/SuperBotGeometryActor.h" },
		{ "ModuleRelativePath", "SuperBot/SuperBotGeometryActor.h" },
		{ "ToolTip", "@class ASuperBotGeometryActor\n@brief geometry actor for superbot" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_SharedRootComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotGeometryBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotGeometryActor.h" },
		{ "ToolTip", "< slave inner box" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_SharedRootComponent = { "SharedRootComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotGeometryActor, SharedRootComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_SharedRootComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_SharedRootComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxSlave_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotGeometryBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotGeometryActor.h" },
		{ "ToolTip", "< slave inner box" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxSlave = { "OuterBoxSlave", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotGeometryActor, OuterBoxSlave), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxSlave_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxSlave_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxMaster_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotGeometryBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotGeometryActor.h" },
		{ "ToolTip", "< master inner box" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxMaster = { "OuterBoxMaster", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotGeometryActor, OuterBoxMaster), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxMaster_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxMaster_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_InnerBoxMaster_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SuperBotGeometryBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SuperBot/SuperBotGeometryActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_InnerBoxMaster = { "InnerBoxMaster", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASuperBotGeometryActor, InnerBoxMaster), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_InnerBoxMaster_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_InnerBoxMaster_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASuperBotGeometryActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_SharedRootComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxSlave,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_OuterBoxMaster,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASuperBotGeometryActor_Statics::NewProp_InnerBoxMaster,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASuperBotGeometryActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASuperBotGeometryActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASuperBotGeometryActor_Statics::ClassParams = {
		&ASuperBotGeometryActor::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASuperBotGeometryActor_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_ASuperBotGeometryActor_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ASuperBotGeometryActor_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ASuperBotGeometryActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASuperBotGeometryActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASuperBotGeometryActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASuperBotGeometryActor, 3523149348);
	template<> REBOTS_API UClass* StaticClass<ASuperBotGeometryActor>()
	{
		return ASuperBotGeometryActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASuperBotGeometryActor(Z_Construct_UClass_ASuperBotGeometryActor, &ASuperBotGeometryActor::StaticClass, TEXT("/Script/ReBots"), TEXT("ASuperBotGeometryActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASuperBotGeometryActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
