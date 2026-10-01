// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EclipseInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UEclipseInteractable : public UInterface
{
	GENERATED_BODY()
};

/** Rest points, doors, pickups, fog gates. */
class IEclipseInteractable
{
	GENERATED_BODY()

public:
	virtual FText GetPrompt() const = 0;
	virtual void Interact(AActor* Instigator) = 0;
};
