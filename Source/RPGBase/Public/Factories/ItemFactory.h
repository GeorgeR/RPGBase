#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"

#include "ItemFactory.generated.h"

class UItem;
class UUniqueIdFactory;

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UItemFactory
	: public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Container")
	UUniqueIdFactory* UniqueIdFactory;

	UItemFactory();

	/* Returns one or more instances for the given item. Providing a greater count than the MaxStackSize will result in more instances. */
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	bool CreateInstance(TSubclassOf<UItem> ItemClass, int32 Count, TArray<FItemInstance>& ItemInstances);
	virtual bool CreateInstance_Implementation(TSubclassOf<UItem> ItemClass, int32 Count, TArray<FItemInstance>& ItemInstance);
	
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Item", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	bool CreateActorFor(UObject* WorldContextObject, const FItemInstance& ItemInstance, AActor* Actor);
	virtual bool CreateActorFor_Implementation(UObject* WorldContextObject, const FItemInstance& ItemInstance, AActor* Actor);

	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	bool LoadInstance(const FString& Id, FItemInstance& ItemInstance);
	virtual bool LoadInstance_Implementation(const FString& Id, FItemInstance& ItemInstance);
};
