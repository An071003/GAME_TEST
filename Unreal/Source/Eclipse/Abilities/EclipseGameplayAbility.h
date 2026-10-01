// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "EclipseGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EEclipseAbilityActivationPolicy : uint8
{
	/** Activates once when the bound input is pressed. */
	OnInputTriggered,
	/** Activates on press and is cancelled when the input is released (block, sprint). */
	WhileInputActive,
	/** Activates automatically when the avatar is set (passives). */
	OnSpawn
};

/** Base class of every GA_*. Tag-based blocking/cancel rules are set per ability asset, not hardcoded here. */
UCLASS(Abstract, Blueprintable)
class ECLIPSE_API UEclipseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UEclipseGameplayAbility();

	EEclipseAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
	const FGameplayTag& GetInputTag() const { return InputTag; }

protected:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eclipse|Ability")
	EEclipseAbilityActivationPolicy ActivationPolicy = EEclipseAbilityActivationPolicy::OnInputTriggered;

	/** Input slot this ability listens to (e.g. Ability.Attack.Light). Empty = not bound to input. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eclipse|Ability")
	FGameplayTag InputTag;
};
