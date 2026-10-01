// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/EclipseCharacterBase.h"
#include "EclipsePlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ECLIPSE_API AEclipsePlayerCharacter : public AEclipseCharacterBase
{
	GENERATED_BODY()

public:
	AEclipsePlayerCharacter();

	UFUNCTION(BlueprintPure, Category = "Eclipse|Camera")
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintPure, Category = "Eclipse|Camera")
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// UEclipseLockOnComponent is added in T-017; input buffer / interaction / inventory components come in M2-M3.

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eclipse|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eclipse|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
