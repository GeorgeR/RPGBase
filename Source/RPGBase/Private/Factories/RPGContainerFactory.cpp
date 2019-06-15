#include "Factories/RPGContainerFactory.h"

#include "Items/RPGContainer.h"
#include "Items/RPGContainerInstanceComponent.h"
#include "Items/Interfaces/RPGContainerInstanceInterface.h"
#include "Factories/UniqueIdFactory.h"

URPGContainerFactory::URPGContainerFactory()
{
	UniqueIdFactory = CreateDefaultSubobject<UUniqueIdFactory>(TEXT("UniqueIdFactory"));
}

bool URPGContainerFactory::CreateInstance_Implementation(const TScriptInterface<IRPGUserInterface>& Owner, TSubclassOf<URPGContainer> ContainerClass, TScriptInterface<IRPGContainerInstanceInterface>& ContainerInstance)
{
	check(ContainerClass);
	check(ContainerInstance);

	ContainerInstance->Create(*ContainerClass, UniqueIdFactory->GetNewId(TEXT("ContainerInstance")), Owner);

	return true;
}

bool URPGContainerFactory::LoadInstance_Implementation(const FString& Id, TScriptInterface<IRPGContainerInstanceInterface>& ContainerInstance)
{
	check(ContainerInstance);

	// #todo Read from persistent store, write data to the instance

	return true;
}
