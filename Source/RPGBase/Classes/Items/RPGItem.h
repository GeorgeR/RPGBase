#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "Engine/DataAsset.h"

#include "RPGItemInstance.h"

#include "RPGItem.generated.h"

class UThumbnailInfo;

/* Base class for an item. Create a child blueprint to create a new item. */
UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API URPGItem 
	: public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/* Type of this item, set in native parent class */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	FPrimaryAssetType AssetType;

	/* Name or short name of the item, should be unique */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	FString Name;

	/* Localized name */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	FText DisplayNameSingular;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	FText DisplayNamePlural;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	bool bIsStackable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item", meta = (EditCondition = bIsStackable))
	int32 MaxStackSize;

	/* Will return the singular or plural name depending on stack size */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Base|Item")
	const FText& GetDisplayName(const FRPGItemInstance& ItemInstance) const;

	/* Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = "RPG Base|Item")
	FString GetIdentifierString() const { return GetPrimaryAssetId().ToString(); }

	/* Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
