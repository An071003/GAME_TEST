// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Core/EclipseDamageable.h"
#include "Core/EclipseTargetable.h"
#include "EclipseCharacterBase.generated.h"

class UEclipseAbilitySystemComponent;
class UEclipseCombatAttributeSet;
class UEclipseGameplayAbility;
class UGameplayEffect;

/** Base of every character (architecture section 4). ASC lives here (ADR-002/005). */
UCLASS(Abstract)
class ECLIPSE_API AEclipseCharacterBase : public ACharacter, public IAbilitySystemInterface, public IEclipseDamageable, public IEclipseTargetable
{
	GENERATED_BODY()

public:
	AEclipseCharacterBase();

	//~ IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//~ IEclipseDamageable
	virtual bool CanBeDamaged(const FEclipseDamageContext& Context) const override;

	//~ IEclipseTargetable
	virtual bool IsTargetable() const override;
	virtual FVector GetTargetLocation() const override;

	UFUNCTION(BlueprintPure, Category = "Eclipse|Character")
	UEclipseAbilitySystemComponent* GetEclipseASC() const { return AbilitySystemComponent; }

	UFUNCTION(BlueprintPure, Category = "Eclipse|Character")
	const UEclipseCombatAttributeSet* GetCombatAttributes() const { return CombatAttributes; }

	/** True when the ASC owns the State.Dead tag. */
	UFUNCTION(BlueprintPure, Category = "Eclipse|Character")
	bool IsDead() const;

protected:
	virtual void PossessedBy(AController* NewController) override;

	/**
	 * Runs once (guard with bAbilitiesInitialized): InitAbilityActorInfo(this, this), then grants StartupAbilities
	 * (level 1, no input id), then applies StartupEffects to self (level 1).
	 */
	virtual void InitializeAbilities();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eclipse|Abilities")
	TObjectPtr<UEclipseAbilitySystemComponent> AbilitySystemComponent;

	/** Subobject registered with the ASC (outer is this actor, as UAttributeSet requires). */
	UPROPERTY()
	TObjectPtr<UEclipseCombatAttributeSet> CombatAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Eclipse|Abilities")
	TArray<TSubclassOf<UEclipseGameplayAbility>> StartupAbilities;

	/** E.g. GE_Init_Player (starting Health/Stamina/Poise). */
	UPROPERTY(EditDefaultsOnly, Category = "Eclipse|Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	bool bAbilitiesInitialized = false;
};
