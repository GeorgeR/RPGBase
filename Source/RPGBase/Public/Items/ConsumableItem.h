#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ConsumableInterface.h"
#include "UsableInterface.h"

#include "ConsumableItem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class RPGBASE_API UConsumableItem
	: public UItem,
	public IUsableInterface,
	public IConsumableInterface
{
	GENERATED_BODY()

public:
	UConsumableItem();

	/* IUsableInterface */
	virtual bool CanUse_Implementation(AActor* TargetUser, FItemInstance& ItemInstance) override;
	virtual void Use_Implementation(AActor* TargetUser, FItemInstance& ItemInstance) override;
	virtual void PostUse_Implementation(FItemInstance& ItemInstance) override;

	/* IConsumableInterface */
	virtual bool CanConsume_Implementation(AActor* TargetConsumer, FItemInstance& ItemInstance) override;
	virtual void Consume_Implementation(AActor* TargetConsumer, FItemInstance& ItemInstance) override;
};
