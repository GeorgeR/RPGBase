#pragma once

#include "CoreMinimal.h"

#include "Items/RPGItemInstance.h"

#include "RPGItemFactory.generated.h"

class URPGItem;
class UUniqueIdFactory;

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API URPGItemFactory
	: public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Container")
	UUniqueIdFactory* UniqueIdFactory;

	URPGItemFactory();

	/* Returns one or more instances for the given item. Providing a greater count than the MaxStackSize will result in more instances. */
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	bool CreateInstance(TSubclassOf<URPGItem> ItemClass, int32 Count, TArray<FRPGItemInstance>& ItemInstances);
	virtual bool CreateInstance_Implementation(TSubclassOf<URPGItem> ItemClass, int32 Count, TArray<FRPGItemInstance>& ItemInstance);
	
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Item", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	bool CreateActorFor(UObject* WorldContextObject, const FRPGItemInstance& ItemInstance, AActor* Actor);
	virtual bool CreateActorFor_Implementation(UObject* WorldContextObject, const FRPGItemInstance& ItemInstance, AActor* Actor);

	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "RPG Base|Item")
	bool LoadInstance(const FString& Id, FRPGItemInstance& ItemInstance);
	virtual bool LoadInstance_Implementation(const FString& Id, FRPGItemInstance& ItemInstance);
};
