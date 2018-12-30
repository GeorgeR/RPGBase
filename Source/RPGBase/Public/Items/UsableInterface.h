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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	bool CanUse(AActor* TargetUser, FItemInstance& ItemInstance);
	virtual bool CanUse_Implementation(AActor* TargetUser, FItemInstance& ItemInstance) = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	void Use(AActor* TargetUser, FItemInstance& ItemInstance);
	virtual void Use_Implementation(AActor* TargetUser, FItemInstance& ItemInstance) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	void PostUse(FItemInstance& ItemInstance);
	virtual void PostUse_Implementation(FItemInstance& ItemInstance) = 0;
};
