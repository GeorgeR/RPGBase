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
	bool CanPickup(AActor* Picker, FItemInstance& ItemInstance);
	virtual bool CanPickup_Implementation(AActor* Picker, FItemInstance& ItemInstance) = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Pickup")
	void Pickup(AActor* Picker, FItemInstance& ItemInstance);
	virtual void Pickup_Implementation(AActor* Picker, FItemInstance& ItemInstance) = 0;
};
