#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "ItemInstance.h"

#include "PickupInterface.generated.h"

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
	bool CanPickup(AActor* InPicker, FItemInstance& InInstance);
	virtual bool CanPickup_Implementation(AActor* InPicker, FItemInstance& InInstance) { return false; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Pickup")
	void Pickup(AActor* InPicker, FItemInstance& InInstance);
	virtual void Pickup_Implementation(AActor* InPicker, FItemInstance& InInstance) { }
};