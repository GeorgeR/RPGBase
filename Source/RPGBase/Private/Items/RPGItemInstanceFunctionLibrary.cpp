#include "Items/RPGItemInstanceFunctionLibrary.h"

#include "Items/RPGItem.h"
#include "Items/RPGItemInstance.h"

#pragma region Accessors
const FString& URPGItemInstanceFunctionLibrary::GetName(const FRPGItemInstance& ItemInstance)
{
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	return Item->Name;
}

const FText& URPGItemInstanceFunctionLibrary::GetDisplayName(const FRPGItemInstance& ItemInstance)
{
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	return Item->GetDisplayName(ItemInstance);
}

const FText& URPGItemInstanceFunctionLibrary::GetDescription(const FRPGItemInstance& ItemInstance)
{
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	return Item->Description;
}

UTexture2D* URPGItemInstanceFunctionLibrary::GetIcon(const FRPGItemInstance& ItemInstance)
{
	// #todo Replace with async loader?
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	return Item->Icon.LoadSynchronous();
}

bool URPGItemInstanceFunctionLibrary::GetIsStackable(const FRPGItemInstance& ItemInstance)
{
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	return Item->bIsStackable;
}

int32 URPGItemInstanceFunctionLibrary::GetMaxStackSize(const FRPGItemInstance& ItemInstance)
{
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	return Item->MaxStackSize;
}

bool URPGItemInstanceFunctionLibrary::ImplementsInterface(const FRPGItemInstance& ItemInstance, TSubclassOf<UInterface> Interface)
{
	auto Item = ItemInstance.GetItem();
	ensure(Item);

	return Item->GetClass()->ImplementsInterface(Interface);
}
#pragma endregion Accessors

#pragma region Functions
int32 URPGItemInstanceFunctionLibrary::AddToStack(FRPGItemInstance& ItemInstance, int32 Amount)
{
	return ItemInstance.AddToStack(Amount);
}

int32 URPGItemInstanceFunctionLibrary::RemoveFromStack(FRPGItemInstance& ItemInstance, int32 Amount)
{
	return ItemInstance.RemoveFromStack(Amount);
}

FRPGItemInstance URPGItemInstanceFunctionLibrary::SplitStack(FRPGItemInstance& ItemInstance, int32 Amount)
{
	return ItemInstance.SplitStack(Amount);
}

FRPGItemInstance URPGItemInstanceFunctionLibrary::Clone(FRPGItemInstance& ItemInstance, int32 StackSize)
{
	return ItemInstance.Clone(StackSize);
}

URPGItem* URPGItemInstanceFunctionLibrary::GetItem(const FRPGItemInstance& ItemInstance)
{
	return ItemInstance.GetItem();
}
#pragma endregion Functions
