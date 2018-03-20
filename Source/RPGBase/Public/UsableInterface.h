#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "ItemInstance.h"

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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Usable")
	bool CanUse(AActor* InTargetUser, FItemInstance& InInstance);
	virtual bool CanUse_Implementation(AActor* InTargetUser, FItemInstance& InInstance);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Usable")
	void Use(AActor* InTargetUser, FItemInstance& InInstance);
	virtual void Use_Implementation(AActor* InTargetUser, FItemInstance& InInstance);
};