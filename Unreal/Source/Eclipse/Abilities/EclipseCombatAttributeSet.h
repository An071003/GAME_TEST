// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "EclipseCombatAttributeSet.generated.h"

#define ECLIPSE_ATTRIBUTE_ACCESSORS(PropertyName) ATTRIBUTE_ACCESSORS_BASIC(UEclipseCombatAttributeSet, PropertyName)

/**
 * Health / Stamina / Poise (combat spec section 5). Not replicated (ADR-005).
 * Starting values come from an init GameplayEffect, never from this class.
 *
 * Damage contract with UEclipseDamageExecution: output the IncomingPoiseDamage modifier BEFORE
 * IncomingDamage, because the hit-reaction event is chosen when IncomingDamage is processed.
 */
UCLASS()
class ECLIPSE_API UEclipseCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes")
	FGameplayAttributeData Health;
	ECLIPSE_ATTRIBUTE_ACCESSORS(Health)

	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes")
	FGameplayAttributeData MaxHealth;
	ECLIPSE_ATTRIBUTE_ACCESSORS(MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes")
	FGameplayAttributeData Stamina;
	ECLIPSE_ATTRIBUTE_ACCESSORS(Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes")
	FGameplayAttributeData MaxStamina;
	ECLIPSE_ATTRIBUTE_ACCESSORS(MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes")
	FGameplayAttributeData Poise;
	ECLIPSE_ATTRIBUTE_ACCESSORS(Poise)

	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes")
	FGameplayAttributeData MaxPoise;
	ECLIPSE_ATTRIBUTE_ACCESSORS(MaxPoise)

	/** Meta attribute: consumed in PostGameplayEffectExecute, always reset to 0. */
	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes|Meta")
	FGameplayAttributeData IncomingDamage;
	ECLIPSE_ATTRIBUTE_ACCESSORS(IncomingDamage)

	/** Meta attribute: consumed in PostGameplayEffectExecute, always reset to 0. */
	UPROPERTY(BlueprintReadOnly, Category = "Eclipse|Attributes|Meta")
	FGameplayAttributeData IncomingPoiseDamage;
	ECLIPSE_ATTRIBUTE_ACCESSORS(IncomingPoiseDamage)

private:
	void SendHitEvent(const FGameplayTag& EventTag, const FGameplayEffectModCallbackData& Data, float Magnitude) const;
};
