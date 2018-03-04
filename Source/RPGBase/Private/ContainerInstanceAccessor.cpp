#include "ContainerInstanceAccessor.h"
#include "ContainerInstanceComponent.h"

// All these do is essentially ensure the wrapped calls are run on the server
bool UContainerInstanceAccessor::Server_AddItem_Validate(UContainerInstanceComponent* InContext, const FItemInstance& InItem, int32 InSlot /*= -1*/) { return true; }
void UContainerInstanceAccessor::Server_AddItem_Implementation(UContainerInstanceComponent* InContext, const FItemInstance& InItem, int32 InSlot /*= -1*/) { InContext->AddItem(InItem, InSlot); }

bool UContainerInstanceAccessor::Server_RemoveItem_Validate(UContainerInstanceComponent* InContext, int32 InSlot) { return true; }
void UContainerInstanceAccessor::Server_RemoveItem_Implementation(UContainerInstanceComponent* InContext, int32 InSlot) { InContext->RemoveItem(InSlot); }

bool UContainerInstanceAccessor::Server_SwapItems_Validate(UContainerInstanceComponent* InContext, int32 InSourceSlot, int32 InDestinationSlot) { return true; }
void UContainerInstanceAccessor::Server_SwapItems_Implementation(UContainerInstanceComponent* InContext, int32 InSourceSlot, int32 InDestinationSlot) { InContext->SwapItems(InSourceSlot, InDestinationSlot); }

bool UContainerInstanceAccessor::Server_TransferItem_Validate(UContainerInstanceComponent* InContext, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot) { return true; }
void UContainerInstanceAccessor::Server_TransferItem_Implementation(UContainerInstanceComponent* InContext, int32 InSourceSlot, UContainerInstanceComponent* InDestinationContainer, int32 InDestinationSlot) { InContext->TransferItem(InSourceSlot, InDestinationContainer, InDestinationSlot); }