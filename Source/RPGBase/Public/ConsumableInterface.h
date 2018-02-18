#pragma once

#include "CoreMinimal.h"

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
	bool CanConsume(AActor* InTargetConsumer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Consumable")
	void Consume(AActor* InTargetConsumer);
};