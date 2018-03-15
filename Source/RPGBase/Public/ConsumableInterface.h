#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

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
	virtual bool CanConsume_Implementation(AActor* InTargetConsumer) { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Consumable")
	void Consume(AActor* InTargetConsumer);
	virtual void Consume_Implementation(AActor* InTargetConsumer) { }
};