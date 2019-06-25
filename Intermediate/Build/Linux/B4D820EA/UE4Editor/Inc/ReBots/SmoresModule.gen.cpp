// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/Smores/SmoresModule.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSmoresModule() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ASmoresModule_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ASmoresModule();
	REBOTS_API UClass* Z_Construct_UClass_AModularRobot();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister();
// End Cross Module References
	void ASmoresModule::StaticRegisterNativesASmoresModule()
	{
	}
	UClass* Z_Construct_UClass_ASmoresModule_NoRegister()
	{
		return ASmoresModule::StaticClass();
	}
	struct Z_Construct_UClass_ASmoresModule_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SmoresController_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SmoresController;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RightWheelJoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RightWheelJoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LeftWheelJoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LeftWheelJoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BackWheelJoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BackWheelJoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InnerJoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InnerJoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WheelRight_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WheelRight;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WheelLeft_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WheelLeft;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WheelBack_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WheelBack;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WheelFront_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WheelFront;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SmoresOuter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SmoresOuter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SmoresInner_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SmoresInner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASmoresModule_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AModularRobot,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Smores/SmoresModule.h" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresController_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< slave joint between slave outer and inner" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresController = { "SmoresController", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, SmoresController), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresController_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresController_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_RightWheelJoint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< master joint between master outer and inner" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_RightWheelJoint = { "RightWheelJoint", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, RightWheelJoint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_RightWheelJoint_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_RightWheelJoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_LeftWheelJoint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< slave joint between slave outer and inner" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_LeftWheelJoint = { "LeftWheelJoint", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, LeftWheelJoint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_LeftWheelJoint_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_LeftWheelJoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_BackWheelJoint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< inner joint (between slave inner and master inner" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_BackWheelJoint = { "BackWheelJoint", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, BackWheelJoint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_BackWheelJoint_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_BackWheelJoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_InnerJoint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< right wheel component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_InnerJoint = { "InnerJoint", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, InnerJoint), Z_Construct_UClass_UPhysicsConstraintComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_InnerJoint_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_InnerJoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelRight_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< left wheel component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelRight = { "WheelRight", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, WheelRight), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelRight_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelRight_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelLeft_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< back wheel component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelLeft = { "WheelLeft", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, WheelLeft), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelLeft_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelLeft_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelBack_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< front wheel component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelBack = { "WheelBack", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, WheelBack), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelBack_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelBack_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelFront_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< outer component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelFront = { "WheelFront", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, WheelFront), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelFront_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelFront_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresOuter_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
		{ "ToolTip", "< inner component of module" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresOuter = { "SmoresOuter", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, SmoresOuter), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresOuter_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresOuter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresInner_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "SmoresBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Smores/SmoresModule.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresInner = { "SmoresInner", nullptr, (EPropertyFlags)0x00200800000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASmoresModule, SmoresInner), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresInner_MetaData, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresInner_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASmoresModule_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresController,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_RightWheelJoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_LeftWheelJoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_BackWheelJoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_InnerJoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelRight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelLeft,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelBack,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_WheelFront,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresOuter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASmoresModule_Statics::NewProp_SmoresInner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASmoresModule_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASmoresModule>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASmoresModule_Statics::ClassParams = {
		&ASmoresModule::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASmoresModule_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ASmoresModule_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ASmoresModule_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASmoresModule()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASmoresModule_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASmoresModule, 3166510392);
	template<> REBOTS_API UClass* StaticClass<ASmoresModule>()
	{
		return ASmoresModule::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASmoresModule(Z_Construct_UClass_ASmoresModule, &ASmoresModule::StaticClass, TEXT("/Script/ReBots"), TEXT("ASmoresModule"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASmoresModule);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
