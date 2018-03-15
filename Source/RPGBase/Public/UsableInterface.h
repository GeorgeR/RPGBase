#pragma once

#include "CoreMinimal.h"

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
	bool CanUse(AActor* InTargetUser);
	virtual bool CanUser_Implementation(AActor* InTargetUser);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Usable")
	void Use(AActor* InTargetUser);
	virtual void Use_Implementation(AActor* InTargetUser);
};