#include "UsableInterface.h"
#include "ConsumableInterface.h"
#include "EquippableInterface.h"

// TODO: Don't reference sub-interfaces here!!

bool IUsableInterface::CanUse_Implementation(AActor* InTargetUser, FItemInstance& ItemInstance)
{
	auto Consumable = Cast<IConsumableInterface>(this);
	if(Consumable)
		return Consumable->CanConsume(InTargetUser, ItemInstance);
	
	auto Equippable = Cast<IEquippableInterface>(this);
	if(Equippable)
		return Equippable->CanEquip(InTargetUser, ItemInstance);
	
	return false;
}

void IUsableInterface::Use_Implementation(AActor* InTargetUser, FItemInstance& ItemInstance)
{
	auto Consumable = Cast<IConsumableInterface>(this);
	if(Consumable)
		if(Consumable->CanConsume(InTargetUser, ItemInstance))
			Consumable->Consume(InTargetUser, ItemInstance);
	
	auto Equippable = Cast<IEquippableInterface>(this);
	if(Equippable)
		if(Equippable->CanEquip(InTargetUser, ItemInstance))
			Equippable->Equip(InTargetUser, ItemInstance);
}
