#include "RPGContainerFactory.h"

#include "RPGContainer.h"
#include "ContainerInstanceComponent.h"
#include "ContainerInstanceInterface.h"
#include "UniqueIdFactory.h"

URPGContainerFactory::URPGContainerFactory()
{
	UniqueIdFactory = CreateDefaultSubobject<UUniqueIdFactory>(TEXT("UniqueIdFactory"));
}

bool URPGContainerFactory::CreateInstance_Implementation(const TScriptInterface<IRPGOwnerInterface>& Owner, TSubclassOf<URPGContainer> ContainerClass, TScriptInterface<IContainerInstanceInterface>& ContainerInstance)
{
	check(ContainerClass);
	check(ContainerInstance);

	ContainerInstance->Create(*ContainerClass, UniqueIdFactory->GetNewId(TEXT("ContainerInstance")), Owner);

	return true;
}

bool URPGContainerFactory::LoadInstance_Implementation(const FString& Id, TScriptInterface<IContainerInstanceInterface>& ContainerInstance)
{
	check(ContainerInstance);

	// TODO: Read from persistent store, write data to the instance

	return true;
}
