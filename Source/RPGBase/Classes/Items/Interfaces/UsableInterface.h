#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Items/RPGItemInstance.h"

#include "UsableInterface.generated.h"

class IRPGUserInterface;

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
	bool CanUse(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance);
	virtual bool CanUse_Implementation(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance) = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	void Use(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance);
	virtual void Use_Implementation(const TScriptInterface<IRPGUserInterface>& TargetUser, FRPGItemInstance& ItemInstance) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Item|Usable")
	void PostUse(FRPGItemInstance& ItemInstance);
	virtual void PostUse_Implementation(FRPGItemInstance& ItemInstance) = 0;
};
