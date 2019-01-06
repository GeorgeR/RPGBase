#include "EquippableItem.h"

bool UEquippableItem::CanUse_Implementation(AActor* TargetUser, FItemInstance& ItemInstance)
{
	return CanEquip(TargetUser, ItemInstance);
}

void UEquippableItem::Use_Implementation(AActor* TargetUser, FItemInstance& ItemInstance)
{
	if (CanEquip(TargetUser, ItemInstance))
		Equip(TargetUser, ItemInstance);
}

void UEquippableItem::PostUse_Implementation(FItemInstance& ItemInstance)
{
	ItemInstance.RemoveFromStack(1);
}

bool UEquippableItem::CanEquip_Implementation(AActor* TargetWearer, FItemInstance& ItemInstance, FName TargetSocket /*= TEXT("")*/, int32 TargetSlot /*= -1*/)
{
	// TODO: Check that the wearer is also the owner
	
	return true;
}

void UEquippableItem::Equip_Implementation(AActor* TargetWearer, FItemInstance& ItemInstance, FName TargetSocket /*= TEXT("")*/, int32 TargetSlot /*= -1*/)
{
	// TODO
}

void UEquippableItem::UnEquip_Implementation(AActor* Wearer, FItemInstance& ItemInstance, FName Socket /*= TEXT("")*/, int32 Slot /*= -1*/)
{
	// TODO: Return to inventory?
}
