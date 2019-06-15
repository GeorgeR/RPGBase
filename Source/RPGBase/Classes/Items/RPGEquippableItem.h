#pragma once

#include "CoreMinimal.h"

#include "Items/RPGItem.h"
#include "Items/Interfaces/UsableInterface.h"
#include "Items/Interfaces/EquippableInterface.h"

#include "RPGEquippableItem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class URPGEquippableItem
	: public URPGItem,
	public IUsableInterface,
	public IEquippableInterface
{
	GENERATED_BODY()

public:
	/* IUsableInterface */
	virtual bool CanUse_Implementation(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance) override;
	virtual void Use_Implementation(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance) override;
	virtual void PostUse_Implementation(FRPGItemInstance& ItemInstance) override;

	/* IEquippableInterface */
	virtual bool CanEquip_Implementation(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1) override;
	virtual void Equip_Implementation(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1) override;
	virtual void UnEquip_Implementation(const TScriptInterface<IRPGUserInterface>& Wearer, FRPGItemInstance& ItemInstance, FName Socket = TEXT(""), int32 Slot = -1) override;
};
