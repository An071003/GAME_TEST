// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EclipseSaveable.generated.h"

UINTERFACE(MinimalAPI)
class UEclipseSaveable : public UInterface
{
	GENERATED_BODY()
};

/** WriteSave/ReadSave are added at M4 together with FEclipseActorSaveData, to avoid defining save types early. */
class IEclipseSaveable
{
	GENERATED_BODY()

public:
	virtual FGuid GetSaveId() const = 0;
};
