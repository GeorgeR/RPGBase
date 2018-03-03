#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInstance.h"

#include "ItemInstanceActor.generated.h"

UCLASS()
class RPGBASE_API AItemActor
	: public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FItemInstance ItemInstance;
};