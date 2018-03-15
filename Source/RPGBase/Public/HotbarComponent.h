#pragma once

#include "CoreMinimal.h"
#include "ContainerInstanceComponent.h"
#include "GameFramework/PlayerController.h"

#include "HotbarComponent.generated.h"

/* Should be attached to PlayerController */
UCLASS(BlueprintType)
class RPGBASE_API UHotbarComponent
	: public UContainerInstanceComponent
{
	GENERATED_BODY()
	
public:
	/* Defaults to Hotbar1, Hotbar2, etc. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FName> ActionMapping;

	UHotbarComponent();

	// TODO: SetupPlayerInput
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Hotbar")
	bool CanUse(int32 InSlot);
	virtual bool CanUse_Implementation(int32 InSlot);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Hotbar")
	bool Use(int32 InSlot);
	virtual bool Use_Implementation(int32 InSlot);

private:
	APlayerController* GetOwner();
};