#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "RPGItemInstance.h"

#include "RPGItemInstanceActor.generated.h"

UCLASS()
class RPGBASE_API ARPGItemActor
	: public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FRPGItemInstance ItemInstance;
};
