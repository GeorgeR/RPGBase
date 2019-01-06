#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "EquippableInterface.h"
#include "UsableInterface.h"

#include "EquippableItem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UEquippableItem
	: public UItem,
	public IUsableInterface,
	public IEquippableInterface
{
	GENERATED_BODY()

public:
	/* IUsableInterface */
	virtual bool CanUse_Implementation(AActor* TargetUser, FItemInstance& ItemInstance) override;
	virtual void Use_Implementation(AActor* TargetUser, FItemInstance& ItemInstance) override;
	virtual void PostUse_Implementation(FItemInstance& ItemInstance) override;

	/* IEquippableInterface */
	virtual bool CanEquip_Implementation(AActor* TargetWearer, FItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1) override;
	virtual void Equip_Implementation(AActor* TargetWearer, FItemInstance& ItemInstance, FName TargetSocket = TEXT(""), int32 TargetSlot = -1) override;
	virtual void UnEquip_Implementation(AActor* Wearer, FItemInstance& ItemInstance, FName Socket = TEXT(""), int32 Slot = -1) override;
};
