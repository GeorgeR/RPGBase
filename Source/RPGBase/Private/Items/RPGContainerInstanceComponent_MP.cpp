#include "Items/RPGContainerInstanceComponent.h"

//#include "Items/RPGContainerInstanceProxyComponent.h"
#include "Interfaces/RPGPlayerInterface.h"
//
//bool UContainerInstanceComponent::AddItem_MP(APlayerController* Player, const FRPGItemInstance& Item, const int32 Slot)
//{
//	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(Player, 
//		this, 
//		[&](UContainerInstanceProxyComponent* InProxy)-> void 
//	{
//			InProxy->Server_AddItem(Item, Slot); 
//	});
//
//	return false;
//}
//
//void UContainerInstanceComponent::RemoveItem_MP(APlayerController* Player, const int32 Slot)
//{
//	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(Player,
//		this,
//		[&](UContainerInstanceProxyComponent* InProxy)-> void 
//	{
//		InProxy->Server_RemoveItem(Slot);
//	});
//}
//
//void UContainerInstanceComponent::SwapItems_MP(APlayerController* Player, const int32 SourceSlot, const int32 DestinationSlot)
//{
//	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(Player,
//		this,
//		[&](UContainerInstanceProxyComponent* InProxy)-> void
//	{
//		InProxy->Server_SwapItems(SourceSlot, DestinationSlot);
//	});
//}
//
//bool UContainerInstanceComponent::TransferItem_MP(APlayerController* Player, const int32 SourceSlot, UContainerInstanceComponent* DestinationContainer, const int32 DestinationSlot)
//{
//	DoOnProxy<UContainerInstanceProxyComponent, UContainerInstanceComponent>(Player,
//		this,
//		[&](UContainerInstanceProxyComponent* InProxy)-> void
//	{
//		InProxy->Server_TransferItem(SourceSlot, DestinationContainer, DestinationSlot);
//	});
//
//	return false;
//}
//
//UContainerInstanceProxyComponent* UContainerInstanceComponent::CreateProxy(UContainerInstanceComponent* ContainerInstance)
//{
//	auto Result = NewObject<UContainerInstanceProxyComponent>(nullptr);
//	Result->SetContext(ContainerInstance);
//	return Result;
//}
