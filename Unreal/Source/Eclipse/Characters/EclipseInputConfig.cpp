// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/EclipseInputConfig.h"

FGameplayTag UEclipseInputConfig::FindInputTagForAction(const UInputAction* Action) const
{
	// T-013: return the InputTag of the first AbilityInputs entry whose Action == Action; otherwise FGameplayTag().
	return FGameplayTag();
}
