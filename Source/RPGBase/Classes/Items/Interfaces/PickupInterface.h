#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "Items/RPGItemInstance.h"

#include "PickupInterface.generated.h"

class IRPGUserInterface;

UINTERFACE(MinimalAPI)
class UPickupInterface
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IPickupInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Pickup")
	bool CanPickup(const TScriptInterface<IRPGUserInterface>& Picker, FRPGItemInstance& ItemInstance);
	virtual bool CanPickup_Implementation(const TScriptInterface<IRPGUserInterface>& Picker, FRPGItemInstance& ItemInstance) = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Pickup")
	void Pickup(const TScriptInterface<IRPGUserInterface>& Picker, FRPGItemInstance& ItemInstance);
	virtual void Pickup_Implementation(const TScriptInterface<IRPGUserInterface>& Picker, FRPGItemInstance& ItemInstance) = 0;
};
