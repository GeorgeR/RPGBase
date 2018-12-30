#pragma once

#include "CoreMinimal.h"

#include "FactoryProviderInterface.generated.h"

UINTERFACE(MinimalAPI)
class UFactoryProviderInterface 
: public UInterface
{
	GENERATED_BODY()
};

class RPGBASE_API IFactoryProviderInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Factory")
	class UUniqueIdFactory* GetUniqueIdFactory() const;
	virtual class UUniqueIdFactory* GetUniqueIdFactory_Implementation() const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Factory")
	class UItemFactory* GetItemFactory() const;
	virtual class UItemFactory* GetItemFactory_Implementation() const = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Factory")
	class UContainerFactory* GetContainerFactory() const;
	virtual class UContainerFactory* GetContainerFactory_Implementation() const = 0;
};
