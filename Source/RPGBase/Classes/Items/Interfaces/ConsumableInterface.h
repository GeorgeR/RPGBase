#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "Items/RPGItemInstance.h"
#include "Items/Interfaces/UsableInterface.h"

#include "ConsumableInterface.generated.h"

class IRPGUserInterface;

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
	bool CanConsume(const TScriptInterface<IRPGUserInterface>& TargetConsumer, FRPGItemInstance& ItemInstance);
	virtual bool CanConsume_Implementation(const TScriptInterface<IRPGUserInterface>& TargetConsumer, FRPGItemInstance& ItemInstance) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Consumable")
	void Consume(const TScriptInterface<IRPGUserInterface>& TargetConsumer, FRPGItemInstance& ItemInstance);
	virtual void Consume_Implementation(const TScriptInterface<IRPGUserInterface>& TargetConsumer, FRPGItemInstance& ItemInstance) = 0;
};
