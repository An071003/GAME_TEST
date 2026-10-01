// Copyright Epic Games, Inc. All Rights Reserved.

#include "Abilities/EclipseGameplayAbility.h"
#include "AbilitySystemComponent.h"

UEclipseGameplayAbility::UEclipseGameplayAbility()
{
	// Per-actor instances let abilities keep state (combo index, cached montage) without extra plumbing.
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UEclipseGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivationPolicy == EEclipseAbilityActivationPolicy::OnSpawn && ActorInfo && ActorInfo->AbilitySystemComponent.IsValid() && !Spec.IsActive())
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}
