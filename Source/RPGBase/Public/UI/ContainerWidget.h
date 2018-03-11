#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "ContainerInstanceComponent.h"
#include "ItemWidget.h"
#include "PanelWidget.h"

#include "ContainerWidget.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UContainerWidget
	: public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UContainerInstanceComponent* Context;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Context")
	UContainerInstanceComponent* GetContext() const { return Context; }

	UFUNCTION(BlueprintCallable, Category = "Context")
	void SetContext(UContainerInstanceComponent* InContext);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* ItemsPanel;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UItemWidget> ItemWidgetClass;

private:
	UFUNCTION()
	void OnItemAdded(const FItemInstance& InItem, int32 InSlot) const;

	UFUNCTION()
	void OnItemRemoved(const FItemInstance& InItem, int32 InSlot) const;
};