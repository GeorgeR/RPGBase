#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "RPGItemInstance.h"

#include "UsableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UUsableInterface
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IUsableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	bool CanUse(AActor* TargetUser, FRPGItemInstance& ItemInstance);
	virtual bool CanUse_Implementation(AActor* TargetUser, FRPGItemInstance& ItemInstance) = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	void Use(AActor* TargetUser, FRPGItemInstance& ItemInstance);
	virtual void Use_Implementation(AActor* TargetUser, FRPGItemInstance& ItemInstance) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	void PostUse(FRPGItemInstance& ItemInstance);
	virtual void PostUse_Implementation(FRPGItemInstance& ItemInstance) = 0;
};
