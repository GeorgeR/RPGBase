#include "Items/RPGEquippableItem.h"

bool URPGEquippableItem::CanUse_Implementation(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance)
{
	return CanEquip(TargetUser, ItemInstance);
}

void URPGEquippableItem::Use_Implementation(const TScriptInterface<IRPGUserInterface>&TargetUser, FRPGItemInstance& ItemInstance)
{
	if (CanEquip(TargetUser, ItemInstance))
		Equip(TargetUser, ItemInstance);
}

void URPGEquippableItem::PostUse_Implementation(FRPGItemInstance& ItemInstance)
{
	ItemInstance.RemoveFromStack(1);
}

bool URPGEquippableItem::CanEquip_Implementation(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket /*= TEXT("")*/, int32 TargetSlot /*= -1*/)
{
	// #todo Check that the wearer is also the owner
	
	return true;
}

void URPGEquippableItem::Equip_Implementation(const TScriptInterface<IRPGUserInterface>& TargetWearer, FRPGItemInstance& ItemInstance, FName TargetSocket /*= TEXT("")*/, int32 TargetSlot /*= -1*/)
{
	// TODO
}

void URPGEquippableItem::UnEquip_Implementation(const TScriptInterface<IRPGUserInterface>& Wearer, FRPGItemInstance& ItemInstance, FName Socket /*= TEXT("")*/, int32 Slot /*= -1*/)
{
	// #todo Return to inventory?
}
