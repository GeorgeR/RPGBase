#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "ItemInstance.h"

#include "ConsumableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UConsumableInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IConsumableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Consumable")
	bool CanConsume(AActor* InTargetConsumer, FItemInstance& InInstance);
	virtual bool CanConsume_Implementation(AActor* InTargetConsumer, FItemInstance& InInstance) { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Consumable")
	void Consume(AActor* InTargetConsumer, FItemInstance& InInstance);
	virtual void Consume_Implementation(AActor* InTargetConsumer, FItemInstance& InInstance) { }
};