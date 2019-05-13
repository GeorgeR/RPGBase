#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "RPGContainerFactory.generated.h"

class IRPGUserInterface;
class IRPGContainerInstanceInterface;
class URPGContainer;
class UUniqueIdFactory;

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API URPGContainerFactory
	: public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Container")
	UUniqueIdFactory* UniqueIdFactory;

	URPGContainerFactory();
	
	/* Injects data into the provided instance (you create it first) */
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool CreateInstance(const TScriptInterface<IRPGUserInterface>& Owner, TSubclassOf<URPGContainer> ContainerClass, TScriptInterface<IRPGContainerInstanceInterface>& ContainerInstance);
	virtual bool CreateInstance_Implementation(const TScriptInterface<IRPGUserInterface>& Owner, TSubclassOf<URPGContainer> ContainerClass, TScriptInterface<IRPGContainerInstanceInterface>& ContainerInstance);

	/* Injects data into the provided instance (you create it first) */
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Container")
	bool LoadInstance(const FString& Id, TScriptInterface<IRPGContainerInstanceInterface>& ContainerInstance);
	virtual bool LoadInstance_Implementation(const FString& Id, TScriptInterface<IRPGContainerInstanceInterface>& ContainerInstance);
};
