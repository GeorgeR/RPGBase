#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "ItemInstance.h"
#include "UsableInterface.h"

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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Consumable")
	bool CanConsume(AActor* TargetConsumer, FItemInstance& ItemInstance);
	virtual bool CanConsume_Implementation(AActor* TargetConsumer, FItemInstance& ItemInstance) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Consumable")
	void Consume(AActor* TargetConsumer, FItemInstance& ItemInstance);
	virtual void Consume_Implementation(AActor* TargetConsumer, FItemInstance& ItemInstance) = 0;
};
