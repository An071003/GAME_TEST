// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Core/EclipseTypes.h"
#include "EclipseDamageable.generated.h"

UINTERFACE(MinimalAPI)
class UEclipseDamageable : public UInterface
{
	GENERATED_BODY()
};

/** Lets non-GAS actors (e.g. a wooden crate) answer damage queries. Characters with an ASC take damage via GameplayEffects. */
class IEclipseDamageable
{
	GENERATED_BODY()

public:
	virtual bool CanBeDamaged(const FEclipseDamageContext& Context) const = 0;
};
