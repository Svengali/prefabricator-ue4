//$ Copyright 2015-18, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "PrefabricatorAsset.generated.h"

UCLASS()
class PREFABRICATORRUNTIME_API UPrefabricatorProperty : public UObject {
	GENERATED_BODY()
public:
	UPROPERTY()
	FString PropertyName;

	UPROPERTY()
	FString ExportedValue;
};

USTRUCT()
struct PREFABRICATORRUNTIME_API FPrefabricatorComponentData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FTransform RelativeTransform;

	UPROPERTY()
	FString ComponentName;

	UPROPERTY()
	TArray<UPrefabricatorProperty*> Properties;
};

USTRUCT()
struct PREFABRICATORRUNTIME_API FPrefabricatorActorData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FGuid PrefabItemID;

	UPROPERTY()
	FTransform RelativeTransform;

	UPROPERTY()
	FString ClassPath;

	UPROPERTY()
	TArray<UPrefabricatorProperty*> Properties;

	UPROPERTY()
	TArray<FPrefabricatorComponentData> Components;
};

struct FPrefabAssetSelectionConfig {
	int32 Seed = 0;
};

UCLASS(Blueprintable)
class PREFABRICATORRUNTIME_API UPrefabricatorAssetInterface : public UObject {
	GENERATED_BODY()

public:
	virtual class UPrefabricatorAsset* GetPrefabAsset(const FPrefabAssetSelectionConfig& InConfig) { return nullptr; }
};

UCLASS(Blueprintable)
class PREFABRICATORRUNTIME_API UPrefabricatorAsset : public UPrefabricatorAssetInterface {
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY()
	TArray<FPrefabricatorActorData> ActorData;

	UPROPERTY()
	TEnumAsByte<EComponentMobility::Type> PrefabMobility;

	// The ID that is regenerated on every update
	// This allows prefab actors to test against their own LastUpdateID and determine if a refresh is needed
	UPROPERTY()
	FGuid LastUpdateID;


	/** Information for thumbnail rendering */
	UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, Category = StaticMesh)
	class UThumbnailInfo* ThumbnailInfo;

public:
	virtual UPrefabricatorAsset* GetPrefabAsset(const FPrefabAssetSelectionConfig& InConfig) override;
};


USTRUCT(BlueprintType)
struct PREFABRICATORRUNTIME_API FPrefabricatorAssetCollectionItem {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Prefabricator")
	UPrefabricatorAsset* PrefabAsset;

	UPROPERTY(EditAnywhere, Category = "Prefabricator")
	float Weight = 1.0f;
};

UCLASS(Blueprintable)
class PREFABRICATORRUNTIME_API UPrefabricatorAssetCollection : public UPrefabricatorAssetInterface {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Prefabricator")
	TArray<FPrefabricatorAssetCollectionItem> Prefabs;

public:
	virtual UPrefabricatorAsset* GetPrefabAsset(const FPrefabAssetSelectionConfig& InConfig) override;
};


class PREFABRICATORRUNTIME_API FPrefabricatorAssetUtils {
public:
	static FVector FindPivot(const TArray<AActor*>& InActors);
	static EComponentMobility::Type FindMobility(const TArray<AActor*>& InActors);
	
};

