// Copyright Epic Games, Inc. All Rights Reserved.

#include "Abilities/EclipseCombatAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Core/EclipseGameplayTags.h"

namespace
{
	// Max <= 0 means "not initialised yet" (init GE applies Health before MaxHealth), so only the floor applies.
	float ClampToRange(float Value, float Max)
	{
		return Max > 0.f ? FMath::Clamp(Value, 0.f, Max) : FMath::Max(Value, 0.f);
	}
}

void UEclipseCombatAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = ClampToRange(NewValue, GetMaxHealth());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		// Floor is 0 (spec section 3 allows "slightly negative or 0"); an ability may start while Stamina > 0.
		NewValue = ClampToRange(NewValue, GetMaxStamina());
	}
	else if (Attribute == GetPoiseAttribute())
	{
		NewValue = ClampToRange(NewValue, GetMaxPoise());
	}
}

void UEclipseCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;

	if (Attribute == GetIncomingPoiseDamageAttribute())
	{
		const float PoiseDamage = GetIncomingPoiseDamage();
		SetIncomingPoiseDamage(0.f);
		if (PoiseDamage > 0.f)
		{
			SetPoise(ClampToRange(GetPoise() - PoiseDamage, GetMaxPoise()));
		}
	}
	else if (Attribute == GetIncomingDamageAttribute())
	{
		const float Damage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (Damage <= 0.f || GetHealth() <= 0.f)
		{
			return;
		}

		SetHealth(ClampToRange(GetHealth() - Damage, GetMaxHealth()));

		// Death > Stagger > Light. Poise was already reduced by the preceding IncomingPoiseDamage modifier.
		// Whoever handles Event.HitReact.Stagger is responsible for restoring Poise (M2), otherwise the next hit staggers again.
		if (GetHealth() <= 0.f)
		{
			SendHitEvent(EclipseTags::Event_Death.GetTag(), Data, Damage);
		}
		else if (GetPoise() <= 0.f)
		{
			SendHitEvent(EclipseTags::Event_HitReact_Stagger.GetTag(), Data, Damage);
		}
		else
		{
			SendHitEvent(EclipseTags::Event_HitReact_Light.GetTag(), Data, Damage);
		}
	}
	else if (Attribute == GetHealthAttribute())
	{
		SetHealth(ClampToRange(GetHealth(), GetMaxHealth()));
	}
	else if (Attribute == GetStaminaAttribute())
	{
		SetStamina(ClampToRange(GetStamina(), GetMaxStamina()));
	}
	else if (Attribute == GetPoiseAttribute())
	{
		SetPoise(ClampToRange(GetPoise(), GetMaxPoise()));
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		SetHealth(ClampToRange(GetHealth(), GetMaxHealth()));
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		SetStamina(ClampToRange(GetStamina(), GetMaxStamina()));
	}
	else if (Attribute == GetMaxPoiseAttribute())
	{
		SetPoise(ClampToRange(GetPoise(), GetMaxPoise()));
	}
}

void UEclipseCombatAttributeSet::SendHitEvent(const FGameplayTag& EventTag, const FGameplayEffectModCallbackData& Data, float Magnitude) const
{
	UAbilitySystemComponent* TargetASC = GetOwningAbilitySystemComponent();
	if (!TargetASC)
	{
		return;
	}

	const FGameplayEffectContextHandle& Context = Data.EffectSpec.GetContext();

	FGameplayEventData Payload;
	Payload.EventTag = EventTag;
	Payload.Instigator = Context.GetOriginalInstigator();
	Payload.Target = TargetASC->GetAvatarActor();
	Payload.ContextHandle = Context;
	Payload.EventMagnitude = Magnitude;
	TargetASC->HandleGameplayEvent(EventTag, &Payload);
}
