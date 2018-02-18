#pragma once

#include "CoreMinimal.h"

#include "EquippableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEquippableInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IEquippableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Equippable")
	bool CanEquip(AActor* InTargetWearer, FName InTargetSocket, int32 InTargetSlot);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Equippable")
	void Equip(AActor* InTargetWearer, FName InTargetSocket, int32 InTargetSlot);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Equippable")
	void UnEquip(AActor* InWearer, FName InTargetSocket, int32 InTargetSlot);
};