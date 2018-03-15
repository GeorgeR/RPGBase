#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"

#include "ItemFactory.generated.h"

class UItem;

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UItemFactory
	: public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "Factory|Item")
	bool CreateInstance(TSubclassOf<UItem> InItemClass, int32 InCount, TArray<FItemInstance>& OutItemInstances);
	virtual bool CreateInstance_Implementation(TSubclassOf<UItem> InItemClass, int32 InCount, TArray<FItemInstance>& OutItemInstance);
	
	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "Factory|Item", meta = (HidePin = "InWorldContextObject", DefaultToSelf = "InWorldContextObject"))
	bool CreateActorFor(UObject* InWorldContextObject, FItemInstance& InItemInstance, AActor* OutActor);
	virtual bool CreateActorFor_Implementation(UObject* InWorldContextObject, FItemInstance& InItemInstance, AActor* OutActor);

	UFUNCTION(Blueprintcallable, BlueprintNativeEvent, Category = "Factory|Item")
	bool LoadInstance(FName InId, FItemInstance& OutItemInstance);
	virtual bool LoadInstance_Implementation(FName InId, FItemInstance& OutItemInstance) { return false; }
};