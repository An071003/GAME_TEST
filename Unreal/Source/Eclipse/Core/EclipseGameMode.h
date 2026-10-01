// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EclipseGameMode.generated.h"

/**
 * Core/ may only include engine headers (architecture section 3), so this class never names the Player classes.
 * Pawn / controller / HUD classes are set on BP_EclipseGameMode (Human step).
 */
UCLASS()
class ECLIPSE_API AEclipseGameMode : public AGameModeBase
{
	GENERATED_BODY()
};
