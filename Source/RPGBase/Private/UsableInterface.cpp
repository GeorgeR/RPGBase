#include "UsableInterface.h"
#include "ConsumableInterface.h"
#include "EquippableInterface.h"

bool IUsableInterface::CanUser_Implementation(AActor* InTargetUser)
{
	auto Consumable = Cast<IConsumableInterface>(this);
	if(Consumable)
		return Consumable->CanConsume(InTargetUser);
	
	auto Equippable = Cast<IEquippableInterface>(this);
	if(Equippable)
		return Equippable->CanEquip(InTargetUser);
	
	return false;
}

void IUsableInterface::Use_Implementation(AActor* InTargetUser)
{
	auto Consumable = Cast<IConsumableInterface>(this);
	if(Consumable)
		if(Consumable->CanConsume(InTargetUser))
			Consumable->Consume(InTargetUser);
	
	auto Equippable = Cast<IEquippableInterface>(this);
	if(Equippable)
		if(Equippable->CanEquip(InTargetUser))
			Equippable->Equip(InTargetUser);
}