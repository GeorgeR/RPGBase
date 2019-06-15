#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Items/RPGContainerInstanceComponent.h"

#include "ActionBarComponent.generated.h"

class IRPGUserInterface;

/* Should be attached to PlayerController */
UCLASS(BlueprintType)
class RPGBASE_API UActionBarComponent
	: public URPGContainerInstanceComponent
{
	GENERATED_BODY()
	
public:
	/* Defaults to Hotbar1, Hotbar2, etc. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FName> ActionMapping;

	UActionBarComponent();

	// #todo SetupPlayerInput
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Hotbar")
	bool CanUse(int32 Slot);
	virtual bool CanUse_Implementation(int32 Slot);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Hotbar")
	bool Use(int32 Slot);
	virtual bool Use_Implementation(int32 Slot);

private:
	TScriptInterface<IRPGUserInterface> GetUser();
};
