#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "ItemInstance.h"

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
	bool CanEquip(AActor* InTargetWearer, FItemInstance& InInstance, FName InTargetSocket = TEXT(""), int32 InTargetSlot = -1);
	virtual bool CanEquip_Implementation(AActor* InTargetWearer, FItemInstance& InInstance, FName InTargetSocket = TEXT(""), int32 InTargetSlot = -1) { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Equippable")
	void Equip(AActor* InTargetWearer, FItemInstance& InInstance, FName InTargetSocket = TEXT(""), int32 InTargetSlot = -1);
	virtual void Equip_Implementation(AActor* InTargetWearer, FItemInstance& InInstance, FName InTargetSocket = TEXT(""), int32 InTargetSlot = -1) { }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Equippable")
	void UnEquip(AActor* InWearer, FItemInstance& InInstance, FName InSocket, int32 InSlot);
	virtual void UnEquip_Implementation(AActor* InWearer, FItemInstance& InInstance, FName InSocket = TEXT(""), int32 InSlot = -1) { }
};