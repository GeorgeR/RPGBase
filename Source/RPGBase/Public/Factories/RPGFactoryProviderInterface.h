#pragma once

#include "CoreMinimal.h"

#include "RPGFactoryProviderInterface.generated.h"

UINTERFACE(MinimalAPI)
class URPGFactoryProviderInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IRPGFactoryProviderInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Factory")
	class UUniqueIdFactory* GetUniqueIdFactory() const;
	virtual class UUniqueIdFactory* GetUniqueIdFactory_Implementation() const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Factory")
	class URPGItemFactory* GetItemFactory() const;
	virtual class URPGItemFactory* GetItemFactory_Implementation() const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Factory")
	class URPGContainerFactory* GetContainerFactory() const;
	virtual class URPGContainerFactory* GetContainerFactory_Implementation() const = 0;
};
