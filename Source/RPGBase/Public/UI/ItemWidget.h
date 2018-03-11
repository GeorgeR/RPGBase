#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "ItemInstance.h"

#include "ItemWidget.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UItemWidget
	: public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FItemInstance Context;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 StackSize;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Context")
	FItemInstance& GetContext() { return Context; }

	UFUNCTION(BlueprintCallable, Category = "Context")
	void SetContext(const FItemInstance& InContext);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SplitStack(int32 InAmount);
};