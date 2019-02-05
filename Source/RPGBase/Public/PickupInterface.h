#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "RPGItemInstance.h"

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
	bool CanPickup(AActor* Picker, FRPGItemInstance& ItemInstance);
	virtual bool CanPickup_Implementation(AActor* Picker, FRPGItemInstance& ItemInstance) = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Pickup")
	void Pickup(AActor* Picker, FRPGItemInstance& ItemInstance);
	virtual void Pickup_Implementation(AActor* Picker, FRPGItemInstance& ItemInstance) = 0;
};
