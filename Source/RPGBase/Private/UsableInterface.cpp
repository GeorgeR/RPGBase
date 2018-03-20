#include "UsableInterface.h"
#include "ConsumableInterface.h"
#include "EquippableInterface.h"

bool IUsableInterface::CanUse_Implementation(AActor* InTargetUser, FItemInstance& InInstance)
{
	auto Consumable = Cast<IConsumableInterface>(this);
	if(Consumable)
		return Consumable->CanConsume(InTargetUser, InInstance);
	
	auto Equippable = Cast<IEquippableInterface>(this);
	if(Equippable)
		return Equippable->CanEquip(InTargetUser, InInstance);
	
	return false;
}

void IUsableInterface::Use_Implementation(AActor* InTargetUser, FItemInstance& InInstance)
{
	auto Consumable = Cast<IConsumableInterface>(this);
	if(Consumable)
		if(Consumable->CanConsume(InTargetUser, InInstance))
			Consumable->Consume(InTargetUser, InInstance);
	
	auto Equippable = Cast<IEquippableInterface>(this);
	if(Equippable)
		if(Equippable->CanEquip(InTargetUser, InInstance))
			Equippable->Equip(InTargetUser, InInstance);
}