#include "ContainerInstanceComponent.h"
#include "ContainerInstanceProxyComponent.h"
#include "RPGPlayerInterface.h"

bool UContainerInstanceComponent::AddItem_MP(APlayerController* InPlayer, const FRPGItemInstance& InItem, const int32 InSlot /*= -1*/)
{
	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(InPlayer, 
		this, 
		[&](UContainerInstanceProxyComponent* InProxy)-> void 
	{
			InProxy->Server_AddItem(InItem, InSlot); 
	});

	return false;
}

void UContainerInstanceComponent::RemoveItem_MP(APlayerController* InPlayer, const int32 InSlot)
{
	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(InPlayer,
		this,
		[&](UContainerInstanceProxyComponent* InProxy)-> void 
	{
		InProxy->Server_RemoveItem(InSlot);
	});
}

void UContainerInstanceComponent::SwapItems_MP(APlayerController* InPlayer, const int32 InSourceSlot, const int32 InDestinationSlot)
{
	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(InPlayer,
		this,
		[&](UContainerInstanceProxyComponent* InProxy)-> void
	{
		InProxy->Server_SwapItems(InSourceSlot, InDestinationSlot);
	});
}

bool UContainerInstanceComponent::TransferItem_MP(APlayerController* InPlayer, const int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, const int32 InDestinationSlot)
{
	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(InPlayer,
		this,
		[&](UContainerInstanceProxyComponent* InProxy)-> void
	{
		InProxy->Server_TransferItem(InSourceSlot, InDestinationContainer, InDestinationSlot);
	});

	return false;
}

UContainerInstanceProxyComponent* UContainerInstanceComponent::CreateProxy(UContainerInstanceComponent* InContainerInstance)
{
	auto Result = NewObject<UContainerInstanceProxyComponent>(nullptr);
	Result->SetContext(InContainerInstance);
	return Result;
}
