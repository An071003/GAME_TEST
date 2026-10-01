// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EclipseGameInstance.generated.h"

/** Empty on purpose: the event bus is a subsystem (ADR-011); save/profile hooks arrive in M4. */
UCLASS()
class ECLIPSE_API UEclipseGameInstance : public UGameInstance
{
	GENERATED_BODY()
};
