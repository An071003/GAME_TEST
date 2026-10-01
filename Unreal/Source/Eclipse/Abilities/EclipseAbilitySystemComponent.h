// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "EclipseAbilitySystemComponent.generated.h"

/** Lives on the Character (ADR-005, single-player: no replication/prediction setup). */
UCLASS()
class ECLIPSE_API UEclipseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/** Called by the controller (and later the input buffer) with the ability's InputTag instead of an InputID. */
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
};
