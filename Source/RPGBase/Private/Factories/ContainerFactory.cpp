#include "ContainerFactory.h"

#include "Container.h"
#include "ContainerInstanceComponent.h"
#include "ContainerInstanceInterface.h"
#include "UniqueIdFactory.h"

UContainerFactory::UContainerFactory()
{
	UniqueIdFactory = CreateDefaultSubobject<UUniqueIdFactory>(TEXT("UniqueIdFactory"));
}

bool UContainerFactory::CreateInstance_Implementation(const TScriptInterface<IRPGOwnerInterface>& Owner, TSubclassOf<UContainer> ContainerClass, TScriptInterface<IContainerInstanceInterface>& ContainerInstance)
{
	check(ContainerClass);
	check(ContainerInstance);

	ContainerInstance->Create(*ContainerClass, UniqueIdFactory->GetNewId(TEXT("ContainerInstance")), Owner);

	return true;
}

bool UContainerFactory::LoadInstance_Implementation(const FString& Id, TScriptInterface<IContainerInstanceInterface>& ContainerInstance)
{
	check(ContainerInstance);

	// TODO: Read from persistent store, write data to the instance

	return true;
}
