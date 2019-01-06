// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Abilities/RPGAbilityTask_PlayMontageAndWaitForEvent.h"

#include "Abilities/RPGAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimInstance.h"

URPGAbilityTask_PlayMontageAndWaitForEvent::URPGAbilityTask_PlayMontageAndWaitForEvent()
	: Rate(1.0f),
	bStopWhenAbilityEnds(true) { }

void URPGAbilityTask_PlayMontageAndWaitForEvent::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (Ability && Ability->GetCurrentMontage() == MontageToPlay)
	{
		if (Montage == MontageToPlay)
		{
			AbilitySystemComponent->ClearAnimatingAbility(Ability);

			// Reset AnimRootMotionTranslationScale
			auto Character = Cast<ACharacter>(GetAvatarActor());
			if (Character && (Character->Role == ROLE_Authority ||(Character->Role == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
				Character->SetAnimRootMotionTranslationScale(1.f);
		}
	}

	if (bInterrupted)
		if (ShouldBroadcastAbilityTaskDelegates())
			OnInterrupted.Broadcast(FGameplayTag(), FGameplayEventData());
	else
		if (ShouldBroadcastAbilityTaskDelegates())
			OnBlendOut.Broadcast(FGameplayTag(), FGameplayEventData());
}

void URPGAbilityTask_PlayMontageAndWaitForEvent::OnAbilityCancelled()
{
	// TODO: Merge this fix back to engine, it was calling the wrong callback
	if (StopPlayingMontage())
	{
		// Let the BP handle the interrupt as well
		if (ShouldBroadcastAbilityTaskDelegates())
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
	}
}

void URPGAbilityTask_PlayMontageAndWaitForEvent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
		if (ShouldBroadcastAbilityTaskDelegates())
			OnCompleted.Broadcast(FGameplayTag(), FGameplayEventData());

	EndTask();
}

void URPGAbilityTask_PlayMontageAndWaitForEvent::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *Payload;
		TempData.EventTag = EventTag;

		EventReceived.Broadcast(EventTag, TempData);
	}
}

URPGAbilityTask_PlayMontageAndWaitForEvent* URPGAbilityTask_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(UGameplayAbility* OwningAbility,
	FName TaskInstanceName, UAnimMontage* MontageToPlay, FGameplayTagContainer EventTags, float Rate, FName StartSection, bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	auto Result = NewAbilityTask<URPGAbilityTask_PlayMontageAndWaitForEvent>(OwningAbility, TaskInstanceName);
	Result->MontageToPlay = MontageToPlay;
	Result->EventTags = EventTags;
	Result->Rate = Rate;
	Result->StartSection = StartSection;
	Result->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	Result->bStopWhenAbilityEnds = bStopWhenAbilityEnds;

	return Result;
}

void URPGAbilityTask_PlayMontageAndWaitForEvent::Activate()
{
	if (Ability == nullptr)
		return;

	bool bPlayedMontage = false;
	auto AbilitySystemComponent = GetTargetAbilitySystemComponent<UAbilitySystemComponent>();

	if (AbilitySystemComponent)
	{
		const auto ActorInfo = Ability->GetCurrentActorInfo();
		auto AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			// Bind to event callback
			EventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(EventTags, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &URPGAbilityTask_PlayMontageAndWaitForEvent::OnGameplayEvent));

			if (AbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection) > 0.f)
			{
				// Playing a montage could potentially fire off a callback into game code which could kill this ability! Early out if we are  pending kill.
				if (ShouldBroadcastAbilityTaskDelegates() == false)
					return;

				CancelledHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &URPGAbilityTask_PlayMontageAndWaitForEvent::OnAbilityCancelled);

				BlendingOutDelegate.BindUObject(this, &URPGAbilityTask_PlayMontageAndWaitForEvent::OnMontageBlendingOut);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

				MontageEndedDelegate.BindUObject(this, &URPGAbilityTask_PlayMontageAndWaitForEvent::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

				auto Character = Cast<ACharacter>(GetAvatarActor());
				if (Character && (Character->Role == ROLE_Authority || (Character->Role == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
					Character->SetAnimRootMotionTranslationScale(AnimRootMotionTranslationScale);

				bPlayedMontage = true;
			}
		}
		else
			ABILITY_LOG(Warning, TEXT("URPGAbilityTask_PlayMontageAndWaitForEvent call to PlayMontage failed!"));
	}
	else
		ABILITY_LOG(Warning, TEXT("URPGAbilityTask_PlayMontageAndWaitForEvent called on invalid AbilitySystemComponent"));

	if (!bPlayedMontage)
	{
		ABILITY_LOG(Warning, TEXT("URPGAbilityTask_PlayMontageAndWaitForEvent called in Ability %s failed to play montage %s; Task Instance Name %s."), *Ability->GetName(), *GetNameSafe(MontageToPlay), *InstanceName.ToString());
		if (ShouldBroadcastAbilityTaskDelegates())
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
	}

	SetWaitingOnAvatar();
}

void URPGAbilityTask_PlayMontageAndWaitForEvent::ExternalCancel()
{
	check(AbilitySystemComponent);

	OnAbilityCancelled();

	Super::ExternalCancel();
}

void URPGAbilityTask_PlayMontageAndWaitForEvent::OnDestroy(bool AbilityEnded)
{
	// Note: Clearing montage end delegate isn't necessary since its not a multicast and will be cleared when the next montage plays.
	// (If we are destroyed, it will detect this and not do anything)

	// This delegate, however, should be cleared as it is a multicast
	if (Ability)
	{
		Ability->OnGameplayAbilityCancelled.Remove(CancelledHandle);
		if (AbilityEnded && bStopWhenAbilityEnds)
			StopPlayingMontage();
	}

	auto AbilitySystemComponent = GetTargetAbilitySystemComponent<UAbilitySystemComponent>();
	if (AbilitySystemComponent)
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);

	Super::OnDestroy(AbilityEnded);
}

bool URPGAbilityTask_PlayMontageAndWaitForEvent::StopPlayingMontage()
{
	const auto ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo)
		return false;

	auto AnimInstance = ActorInfo->GetAnimInstance();
	if (AnimInstance == nullptr)
		return false;

	// Check if the montage is still playing
	// The ability would have been interrupted, in which case we should automatically stop the montage
	if (AbilitySystemComponent && Ability)
	{
		if (AbilitySystemComponent->GetAnimatingAbility() == Ability && AbilitySystemComponent->GetCurrentMontage() == MontageToPlay)
		{
			// Unbind delegates so they don't get called as well
			auto MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageInstance)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}

			AbilitySystemComponent->CurrentMontageStop();
			return true;
		}
	}

	return false;
}

FString URPGAbilityTask_PlayMontageAndWaitForEvent::GetDebugString() const
{
	UAnimMontage* PlayingMontage = nullptr;
	if (Ability)
	{
		const auto ActorInfo = Ability->GetCurrentActorInfo();
		auto AnimInstance = ActorInfo->GetAnimInstance();

		if (AnimInstance != nullptr)
			PlayingMontage = AnimInstance->Montage_IsActive(MontageToPlay) ? MontageToPlay : AnimInstance->GetCurrentActiveMontage();
	}

	return FString::Printf(TEXT("PlayMontageAndWaitForEvent. MontageToPlay: %s  (Currently Playing): %s"), *GetNameSafe(MontageToPlay), *GetNameSafe(PlayingMontage));
}
