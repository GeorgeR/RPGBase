#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "PanelWidget.h"

#include "Items/RPGContainerInstanceComponent.h"
#include "RPGItemWidget.h"

#include "RPGContainerWidget.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API URPGContainerWidget
	: public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	URPGContainerInstanceComponent* Context;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Context")
	URPGContainerInstanceComponent* GetContext() const { return Context; }

	UFUNCTION(BlueprintCallable, Category = "Context")
	void SetContext(UPARAM(DisplayName = "Context") URPGContainerInstanceComponent* InContext);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* ItemsPanel;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<URPGItemWidget> ItemWidgetClass;

private:
	UFUNCTION()
	void OnItemAdded(const FRPGItemInstance& Item, UPARAM(DisplayName = "Slot") int32 InSlot) const;

	UFUNCTION()
	void OnItemRemoved(const FRPGItemInstance& Item, UPARAM(DisplayName = "Slot") int32 InSlot) const;
};
