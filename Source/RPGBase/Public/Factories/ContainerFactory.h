#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ContainerFactory.generated.h"

class UContainerInstanceComponent;
class UContainer;

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UContainerFactory
	: public UObject
{
	GENERATED_BODY()

public:
	/* Injects data into the provided instance (you create it first) */
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "Factory|Container")
	bool CreateInstance(TSubclassOf<UContainer> InContainerClass, UContainerInstanceComponent* InOutInstance);
	virtual bool CreateInstance_Implementation(TSubclassOf<UContainer> InContainerClass, UContainerInstanceComponent* InOutInstance);

	/* Injects data into the provided instance (you create it first) */
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "Factory|Container")
	bool LoadInstance(FName InId, UContainerInstanceComponent* InOutInstance);
	virtual bool LoadInstance_Implementation(FName InId, UContainerInstanceComponent* InOutInstance) { return false; }
};