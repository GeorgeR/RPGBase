#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "RPGItemInstance.h"
#include "UsableInterface.h"

#include "EquippableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEquippableInterface 
	: public UUsableInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IEquippableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Equippable")
	bool CanEquip(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1);
	virtual bool CanEquip_Implementation(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Equippable")
	void Equip(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1);
	virtual void Equip_Implementation(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Equippable")
	void UnEquip(const TScriptInterface<IRPGUserInterface>& Wearer, FRPGItemInstance& ItemInstance, FName Socket, int32 Slot);
	virtual void UnEquip_Implementation(const TScriptInterface<IRPGUserInterface>& Wearer, FRPGItemInstance& ItemInstance, FName Socket = TEXT(""), int32 Slot = -1) = 0;
};
