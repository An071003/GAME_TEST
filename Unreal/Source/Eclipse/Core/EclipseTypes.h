// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EclipseTypes.generated.h"

UENUM(BlueprintType)
enum class EEclipseHitReactStrength : uint8
{
	Light,
	Heavy
};

/** Describes an incoming hit. Used only to ask "can this be damaged"; real damage always goes through GAS. */
USTRUCT(BlueprintType)
struct FEclipseDamageContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Eclipse")
	TObjectPtr<AActor> Instigator = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Eclipse")
	TObjectPtr<AActor> DamageCauser = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Eclipse")
	FVector HitLocation = FVector::ZeroVector;

	/** World-space direction from attacker toward the target. */
	UPROPERTY(BlueprintReadWrite, Category = "Eclipse")
	FVector HitDirection = FVector::ForwardVector;

	/** One of Data.Damage.* (Physical/Fire/Magic). */
	UPROPERTY(BlueprintReadWrite, Category = "Eclipse")
	FGameplayTag DamageType;

	UPROPERTY(BlueprintReadWrite, Category = "Eclipse")
	EEclipseHitReactStrength HitReactStrength = EEclipseHitReactStrength::Light;
};
