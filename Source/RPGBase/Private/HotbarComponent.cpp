#include "HotbarComponent.h"

#include "Items/UsableInterface.h"

#include "RPGUserInterface.h"

UHotbarComponent::UHotbarComponent()
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
		TEXT("Hotbar0") };
}

bool UHotbarComponent::CanUse_Implementation(int32 InSlot)
{
	auto Usable = Cast<IUsableInterface>(Items[InSlot].GetItem());
	if (Usable == nullptr)
		return false;

	return Usable->CanUse(GetUser(), Items[InSlot]);
}

bool UHotbarComponent::Use_Implementation(int32 InSlot)
{
	if (!CanUse(InSlot))
		return false;

	auto Usable = Cast<IUsableInterface>(Items[InSlot].GetItem());
	if (Usable == nullptr)
		return false;

	Usable->Use(GetUser(), Items[InSlot]);

	return true;
}

TScriptInterface<IRPGUserInterface> UHotbarComponent::GetUser()
{
	return Super::GetOwner();
	//const auto Result = Super::GetOwner();
	//return Result; // This probably fails
	//return Cast<APlayerController>(Result);
}
