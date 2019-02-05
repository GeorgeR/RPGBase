#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"

#include "RPGItemInstance.h"

#include "RPGItemWidget.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API URPGItemWidget
	: public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FRPGItemInstance Context;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 StackSize;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsStackable;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Context")
	FRPGItemInstance& GetContext() { return Context; }

	UFUNCTION(BlueprintCallable, Category = "Context")
	void SetContext(UPARAM(DisplayName = "Context") const FRPGItemInstance& InContext);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SplitStack(int32 Amount);
};
