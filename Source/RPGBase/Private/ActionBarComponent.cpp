#include "ActionBarComponent.h"

#include "Items/Interfaces/UsableInterface.h"

#include "Interfaces/RPGUserInterface.h"

UActionBarComponent::UActionBarComponent()
{
	ActionMapping = {
		TEXT("Hotbar1"),
		TEXT("Hotbar2"),
		TEXT("Hotbar3"),
		TEXT("Hotbar4"),
		TEXT("Hotbar5"),
		TEXT("Hotbar6"),
		TEXT("Hotbar7"),
		TEXT("Hotbar8"),
		TEXT("Hotbar9"),
		TEXT("Hotbar0")};
}

bool UActionBarComponent::CanUse_Implementation(int32 InSlot)
{
	if (!Items.IsValidIndex(InSlot))
		return false;

	auto ItemInstance = Items[InSlot];
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	if (!Item->Implements<UUsableInterface>())
		return false;

	return IUsableInterface::Execute_CanUse(Item, GetUser(), ItemInstance);
}

bool UActionBarComponent::Use_Implementation(int32 InSlot)
{
	if (!CanUse(InSlot))
		return false;

	auto ItemInstance = Items[InSlot];
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	if (!Item->Implements<UUsableInterface>())
		return false;

	IUsableInterface::Execute_Use(Item, GetUser(), ItemInstance);
	return true;
}

TScriptInterface<IRPGUserInterface> UActionBarComponent::GetUser()
{
	return Super::GetOwner();
	//const auto Result = Super::GetOwner();
	//return Result; // This probably fails
	//return Cast<APlayerController>(Result);
}
