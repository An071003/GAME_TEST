// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EclipseInputConfig.generated.h"

class UInputAction;

/** One ability input: when Action fires, the controller forwards InputTag to the ASC. */
USTRUCT(BlueprintType)
struct FEclipseAbilityInputBinding
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> Action = nullptr;

	/** Must equal UEclipseGameplayAbility::InputTag of the ability it triggers (e.g. Ability.Attack.Light). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Ability"))
	FGameplayTag InputTag;
};

/** DA_InputConfig: maps Enhanced Input actions to gameplay (T-014 creates the IA_* assets). */
UCLASS(BlueprintType)
class ECLIPSE_API UEclipseInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Returns the tag bound to Action, or an empty tag if none. */
	FGameplayTag FindInputTagForAction(const UInputAction* Action) const;

	/** Bound directly by the controller (not abilities). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eclipse|Input|Native")
	TObjectPtr<const UInputAction> MoveAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eclipse|Input|Native")
	TObjectPtr<const UInputAction> LookAction = nullptr;

	/** Lock-on toggle: bound in T-017, unused until then. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eclipse|Input|Native")
	TObjectPtr<const UInputAction> LockOnAction = nullptr;

	/** Interact: bound in M3 (interaction component), unused until then. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eclipse|Input|Native")
	TObjectPtr<const UInputAction> InteractAction = nullptr;

	/** Light/Heavy attack, Block, Parry, Dodge, Sprint, UseItem. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eclipse|Input|Abilities")
	TArray<FEclipseAbilityInputBinding> AbilityInputs;
};
