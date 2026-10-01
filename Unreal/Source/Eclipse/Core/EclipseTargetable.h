// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EclipseTargetable.generated.h"

UINTERFACE(MinimalAPI)
class UEclipseTargetable : public UInterface
{
	GENERATED_BODY()
};

/** Implemented by anything the lock-on component may select. */
class IEclipseTargetable
{
	GENERATED_BODY()

public:
	virtual bool IsTargetable() const = 0;
	virtual FVector GetTargetLocation() const = 0;
};
