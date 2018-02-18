#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ItemActor.generated.h"

class UItem;

UCLASS()
class RPGBASE_API AItemActor
	: public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UItem* Item;
};