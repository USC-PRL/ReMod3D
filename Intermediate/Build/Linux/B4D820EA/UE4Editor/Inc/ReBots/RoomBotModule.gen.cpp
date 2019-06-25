// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/RoomBot/RoomBotModule.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRoomBotModule() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ARoomBotModule_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ARoomBotModule();
	REBOTS_API UClass* Z_Construct_UClass_AModularRobot();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	ENGINE_API UClass* Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void ARoomBotModule::StaticRegisterNativesARoomBotModule()
	{
	}
	UClass* Z_Construct_UClass_ARoomBotModule_NoRegister()
	{
		return ARoomBotModule::StaticClass();
	}
	struct Z_Construct_UClass_ARoomBotModule_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HemJoint1_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_HemJoint1;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomBotHem2_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RoomBotHem2;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomBotHem1_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RoomBotHem1;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARoomBotModule_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AModularRobot,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomBotModule_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "RoomBot/RoomBotModule.h" },
		{ "ModuleRelativePath", "RoomBot/RoomBotModule.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomBotModule_Statics::NewProp_HemJoint1_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "RoomBot/RoomBotModule.h" },
		{ "ToolTip", "< outer component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomBotModule_Statics::NewProp_HemJoint1 = { "HemJoint1", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARoomBotModule, HemJoint1), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomBotModule_Statics::NewProp_HemJoint1_MetaData, ARRAY_COUNT(Z_Construct_UClass_ARoomBotModule_Statics::NewProp_HemJoint1_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem2_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "RoomBot/RoomBotModule.h" },
		{ "ToolTip", "< inner component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem2 = { "RoomBotHem2", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARoomBotModule, RoomBotHem2), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem2_MetaData, ARRAY_COUNT(Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem2_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem1_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "RoomBot/RoomBotModule.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem1 = { "RoomBotHem1", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARoomBotModule, RoomBotHem1), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem1_MetaData, ARRAY_COUNT(Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem1_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARoomBotModule_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomBotModule_Statics::NewProp_HemJoint1,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem2,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomBotModule_Statics::NewProp_RoomBotHem1,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARoomBotModule_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARoomBotModule>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ARoomBotModule_Statics::ClassParams = {
		&ARoomBotModule::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ARoomBotModule_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_ARoomBotModule_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ARoomBotModule_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ARoomBotModule_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ARoomBotModule()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ARoomBotModule_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ARoomBotModule, 1488664377);
	template<> REBOTS_API UClass* StaticClass<ARoomBotModule>()
	{
		return ARoomBotModule::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ARoomBotModule(Z_Construct_UClass_ARoomBotModule, &ARoomBotModule::StaticClass, TEXT("/Script/ReBots"), TEXT("ARoomBotModule"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARoomBotModule);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
