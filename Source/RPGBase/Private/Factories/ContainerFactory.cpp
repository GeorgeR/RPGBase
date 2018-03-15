#include "ContainerFactory.h"

#include "Container.h"
#include "ContainerInstanceComponent.h"

bool UContainerFactory::CreateInstance_Implementation(TSubclassOf<UContainer> InContainerClass,	UContainerInstanceComponent* InOutInstance)
{
	InOutInstance->ContainerClass = FSoftClassPath(InContainerClass);

	// TODO: Set Id

	return true;
}