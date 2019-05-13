#pragma once

#include "CoreMinimal.h"

#include "RPGPlayerInterface.h"

//#include "ProxySupport.generated.h"

// NOTE: What the hell is this?

class FProxy
{
public:
	virtual void SetContext(UObject* InContext) = 0;
	virtual UObject* GetContext() const = 0;
};

template <typename TContext>
class TProxy
	: public FProxy
{
public:
	void SetContext(UObject* InContext) override { SetContextAs(Cast<TContext>(InContext)); }
	UObject* GetContext() const override { return (UObject*)GetContextAs(); }

	virtual void SetContextAs(TContext* InContext) = 0;
	virtual TContext* GetContextAs() const = 0;
};

template <typename TProxy, typename T>
static TProxy* GetOrCreateProxy(TScriptInterface<IRPGPlayerInterface> InPlayer, T* InContext)
{
	auto Actor = Cast<AActor>(InPlayer.GetObject());
	if (Actor == nullptr)
		return nullptr;

	TArray<UActorComponent*> Components;
	Actor->GetComponents(Components);

	TProxy* Proxy = nullptr;
	if(Components.Num() > 0)
	{
		for(auto& Component : Components)
		{
			Proxy = Cast<TProxy>(Component);
			if (Proxy == nullptr)
				continue;

			if (InContext == Proxy->GetContext())
				return Proxy;
		}
	}

	if(Proxy == nullptr)
	{
		Proxy = T::CreateProxy(InContext);
		Proxy->SetIsReplicated(true);
		Actor->AddInstanceComponent(Proxy);
		Proxy->OnComponentCreated();
		Proxy->RegisterComponent();
	}

	return Proxy;
}

/* Call when unsubscribing! */
template <typename TProxy, typename T>
static void ReleaseProxy(TScriptInterface<IRPGPlayerInterface>& InPlayer, T* InContext)
{
	auto Actor = Cast<AActor>(InPlayer.GetObject());
	if (Actor == nullptr)
		return;

	TArray<UActorComponent*> Components;
	Actor->GetComponents(Components);

	FProxy* Proxy = nullptr;
	if (Components.Num() > 0)
	{
		for (auto& Component : Components)
		{
			Proxy = Cast<FProxy>(Component);
			if (Proxy == nullptr)
				continue;

			if (InContext == Proxy->GetContext())
				Actor->RemoveInstanceComponent(Proxy);
		}
	}
}

template <typename TProxy, typename T>
static bool DoOnProxy(TScriptInterface<IRPGPlayerInterface> InPlayer, T* InContext, TFunction<void(TProxy*)> InFunc)
{
	const auto Proxy = GetOrCreateProxy<TProxy, T>(InPlayer, InContext);
	if (Proxy == nullptr)
		return false;

	InFunc(Proxy);
	return true;
}
