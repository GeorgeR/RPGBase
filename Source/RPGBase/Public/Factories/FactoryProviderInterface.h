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
	class UItemFactory* GetItemFactory() const;
	virtual class UItemFactory* GetItemFactory_Implementation() const { return nullptr; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RPG Base|Factory")
	class UContainerFactory* GetContainerFactory() const;
	virtual class UContainerFactory* GetContainerFactory_Implementation() const { return nullptr; }
};