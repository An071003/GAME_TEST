// Copyright Epic Games, Inc. All Rights Reserved.

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "AbilitySystemComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "GameplayEffect.h"
#include "Abilities/EclipseAbilitySystemComponent.h"
#include "Abilities/EclipseCombatAttributeSet.h"
#include "Core/EclipseGameplayTags.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEclipseAttributeSetTest, "Eclipse.Abilities.AttributeSet",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::ProductFilter)

namespace
{
	void AddModifier(UGameplayEffect* Effect, const FGameplayAttribute& Attribute, float Magnitude)
	{
		FGameplayModifierInfo& Info = Effect->Modifiers.AddDefaulted_GetRef();
		Info.Attribute = Attribute;
		Info.ModifierOp = EGameplayModOp::Additive;
		Info.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(Magnitude));
	}

	// Instant GE with PoiseDamage first, then Damage: the same order the damage execution must use.
	void ApplyHit(UAbilitySystemComponent* ASC, float PoiseDamage, float Damage)
	{
		UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage());
		Effect->DurationPolicy = EGameplayEffectDurationType::Instant;
		AddModifier(Effect, UEclipseCombatAttributeSet::GetIncomingPoiseDamageAttribute(), PoiseDamage);
		AddModifier(Effect, UEclipseCombatAttributeSet::GetIncomingDamageAttribute(), Damage);
		ASC->ApplyGameplayEffectToSelf(Effect, 1.f, ASC->MakeEffectContext());
	}
}

bool FEclipseAttributeSetTest::RunTest(const FString& Parameters)
{
	// GAS needs a registered component on a real actor, so spin up a minimal transient world.
	UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
	FWorldContext& Context = GEngine->CreateNewWorldContext(EWorldType::Game);
	Context.SetCurrentWorld(World);
	World->InitializeActorsForPlay(FURL());
	AActor* Owner = World->SpawnActor<AActor>();
	Owner->SetRootComponent(NewObject<USceneComponent>(Owner));
	Owner->GetRootComponent()->RegisterComponent();
	UEclipseAbilitySystemComponent* ASC = NewObject<UEclipseAbilitySystemComponent>(Owner);
	ASC->RegisterComponent();
	ASC->InitAbilityActorInfo(Owner, Owner);
	UEclipseCombatAttributeSet* Set = NewObject<UEclipseCombatAttributeSet>(Owner);
	ASC->AddAttributeSetSubobject(Set);

	// Max first: clamping uses it.
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetMaxHealthAttribute(), 400.f);
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetMaxStaminaAttribute(), 100.f);
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetMaxPoiseAttribute(), 30.f);
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetHealthAttribute(), 400.f);
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetStaminaAttribute(), 100.f);
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetPoiseAttribute(), 30.f);

	TArray<FGameplayTag> Events;
	auto Track = [&](const FGameplayTag& Tag)
	{
		ASC->GenericGameplayEventCallbacks.FindOrAdd(Tag).AddLambda([&Events, Tag](const FGameplayEventData*) { Events.Add(Tag); });
	};
	const FGameplayTag LightTag = EclipseTags::Event_HitReact_Light.GetTag();
	const FGameplayTag StaggerTag = EclipseTags::Event_HitReact_Stagger.GetTag();
	const FGameplayTag DeathTag = EclipseTags::Event_Death.GetTag();
	Track(LightTag);
	Track(StaggerTag);
	Track(DeathTag);

	TestEqual(TEXT("Initial Health"), Set->GetHealth(), 400.f);

	// Clamp: no overheal, no negative stamina.
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetHealthAttribute(), 9999.f);
	TestEqual(TEXT("Health clamped to Max"), Set->GetHealth(), 400.f);
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetStaminaAttribute(), -50.f);
	TestEqual(TEXT("Stamina floored at 0"), Set->GetStamina(), 0.f);
	ASC->SetNumericAttributeBase(UEclipseCombatAttributeSet::GetStaminaAttribute(), 100.f);

	// Light hit: damage taken, poise reduced but still > 0.
	ApplyHit(ASC, 10.f, 50.f);
	TestEqual(TEXT("Health after light hit"), Set->GetHealth(), 350.f);
	TestEqual(TEXT("Poise after light hit"), Set->GetPoise(), 20.f);
	TestEqual(TEXT("Meta damage reset"), Set->GetIncomingDamage(), 0.f);
	TestEqual(TEXT("Meta poise damage reset"), Set->GetIncomingPoiseDamage(), 0.f);
	TestEqual(TEXT("One event"), Events.Num(), 1);
	if (Events.Num() == 1) { TestEqual(TEXT("Light event"), Events[0], LightTag); }

	// Poise broken: stagger event.
	Events.Reset();
	ApplyHit(ASC, 25.f, 30.f);
	TestEqual(TEXT("Poise floored at 0"), Set->GetPoise(), 0.f);
	TestEqual(TEXT("Health after stagger hit"), Set->GetHealth(), 320.f);
	TestEqual(TEXT("One event"), Events.Num(), 1);
	if (Events.Num() == 1) { TestEqual(TEXT("Stagger event"), Events[0], StaggerTag); }

	// Lethal hit: death wins over stagger, health floored at 0.
	Events.Reset();
	ApplyHit(ASC, 5.f, 1000.f);
	TestEqual(TEXT("Health floored at 0"), Set->GetHealth(), 0.f);
	TestEqual(TEXT("One event"), Events.Num(), 1);
	if (Events.Num() == 1) { TestEqual(TEXT("Death event"), Events[0], DeathTag); }

	// Already dead: no further events.
	Events.Reset();
	ApplyHit(ASC, 5.f, 10.f);
	TestEqual(TEXT("No events after death"), Events.Num(), 0);

	GEngine->DestroyWorldContext(World);
	World->DestroyWorld(false);
	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
