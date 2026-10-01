// Copyright Epic Games, Inc. All Rights Reserved.

#include "Abilities/EclipseAbilitySystemComponent.h"
#include "Abilities/EclipseGameplayAbility.h"

namespace
{
	const UEclipseGameplayAbility* GetEclipseAbility(const FGameplayAbilitySpec& Spec)
	{
		return Cast<UEclipseGameplayAbility>(Spec.Ability);
	}
}

void UEclipseAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	// Collect first: activating an ability must not happen while iterating the activatable list.
	TArray<FGameplayAbilitySpecHandle> ToActivate;
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		const UEclipseGameplayAbility* Ability = GetEclipseAbility(Spec);
		if (!Ability || !Ability->GetInputTag().MatchesTagExact(InputTag))
		{
			continue;
		}

		if (Spec.IsActive())
		{
			// Lets WaitInputPress / combo logic inside the running ability see the press.
			AbilitySpecInputPressed(Spec);
		}
		else if (Ability->GetActivationPolicy() != EEclipseAbilityActivationPolicy::OnSpawn)
		{
			ToActivate.Add(Spec.Handle);
		}
	}

	for (const FGameplayAbilitySpecHandle& Handle : ToActivate)
	{
		TryActivateAbility(Handle);
	}
}

void UEclipseAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> ToCancel;
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		const UEclipseGameplayAbility* Ability = GetEclipseAbility(Spec);
		if (!Ability || !Ability->GetInputTag().MatchesTagExact(InputTag) || !Spec.IsActive())
		{
			continue;
		}

		AbilitySpecInputReleased(Spec);
		if (Ability->GetActivationPolicy() == EEclipseAbilityActivationPolicy::WhileInputActive)
		{
			ToCancel.Add(Spec.Handle);
		}
	}

	for (const FGameplayAbilitySpecHandle& Handle : ToCancel)
	{
		CancelAbilityHandle(Handle);
	}
}
