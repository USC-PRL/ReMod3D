// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ReBots/CustomActors/BoundingSphere.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBoundingSphere() {}
// Cross Module References
	REBOTS_API UClass* Z_Construct_UClass_ABoundingSphere_NoRegister();
	REBOTS_API UClass* Z_Construct_UClass_ABoundingSphere();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ReBots();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void ABoundingSphere::StaticRegisterNativesABoundingSphere()
	{
	}
	UClass* Z_Construct_UClass_ABoundingSphere_NoRegister()
	{
		return ABoundingSphere::StaticClass();
	}
	struct Z_Construct_UClass_ABoundingSphere_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Sphere_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Sphere;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABoundingSphere_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ReBots,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABoundingSphere_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CustomActors/BoundingSphere.h" },
		{ "ModuleRelativePath", "CustomActors/BoundingSphere.h" },
		{ "ToolTip", "@class ABoundingSphere\n@brief bounding sphere around some object" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABoundingSphere_Statics::NewProp_Sphere_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "BoundingSphereBody" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CustomActors/BoundingSphere.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABoundingSphere_Statics::NewProp_Sphere = { "Sphere", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABoundingSphere, Sphere), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABoundingSphere_Statics::NewProp_Sphere_MetaData, ARRAY_COUNT(Z_Construct_UClass_ABoundingSphere_Statics::NewProp_Sphere_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABoundingSphere_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoundingSphere_Statics::NewProp_Sphere,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABoundingSphere_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABoundingSphere>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ABoundingSphere_Statics::ClassParams = {
		&ABoundingSphere::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABoundingSphere_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_ABoundingSphere_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ABoundingSphere_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ABoundingSphere_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABoundingSphere()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ABoundingSphere_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ABoundingSphere, 3248348056);
	template<> REBOTS_API UClass* StaticClass<ABoundingSphere>()
	{
		return ABoundingSphere::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ABoundingSphere(Z_Construct_UClass_ABoundingSphere, &ABoundingSphere::StaticClass, TEXT("/Script/ReBots"), TEXT("ABoundingSphere"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABoundingSphere);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
