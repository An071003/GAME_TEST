// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/EclipseCharacterBase.h"
#include "Abilities/EclipseAbilitySystemComponent.h"
#include "Abilities/EclipseCombatAttributeSet.h"
#include "Abilities/EclipseGameplayAbility.h"
#include "Core/EclipseGameplayTags.h"
#include "GameplayEffect.h"

AEclipseCharacterBase::AEclipseCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UEclipseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	CombatAttributes = CreateDefaultSubobject<UEclipseCombatAttributeSet>(TEXT("CombatAttributes"));
}

UAbilitySystemComponent* AEclipseCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool AEclipseCharacterBase::CanBeDamaged(const FEclipseDamageContext& Context) const
{
	// T-013: return false if IsDead() or the ASC has State.Invulnerable; otherwise true.
	return false;
}

bool AEclipseCharacterBase::IsTargetable() const
{
	// T-013: return !IsDead().
	return false;
}

FVector AEclipseCharacterBase::GetTargetLocation() const
{
	// T-013: world location of the "spine_03" socket/bone if the mesh has it, else GetActorLocation().
	return FVector::ZeroVector;
}

bool AEclipseCharacterBase::IsDead() const
{
	// T-013: return AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(EclipseTags::State_Dead.GetTag()).
	return false;
}

void AEclipseCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeAbilities();
}

void AEclipseCharacterBase::InitializeAbilities()
{
	// T-013: see the comment in the header. Order matters: ActorInfo -> abilities -> effects.
	// Skip null entries in both arrays and log a Warning (LogEclipse) for each.
}
