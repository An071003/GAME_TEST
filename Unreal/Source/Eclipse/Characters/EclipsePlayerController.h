// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "EclipsePlayerController.generated.h"

class UInputMappingContext;
class UEclipseInputConfig;
class UEclipseAbilitySystemComponent;
struct FInputActionValue;

UCLASS()
class ECLIPSE_API AEclipsePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** IMC_Gameplay from T-014; assigned on the Blueprint subclass. */
	UPROPERTY(EditDefaultsOnly, Category = "Eclipse|Input")
	TObjectPtr<UInputMappingContext> GameplayMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Eclipse|Input")
	TObjectPtr<const UEclipseInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Eclipse|Input")
	int32 MappingContextPriority = 0;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);

	UEclipseAbilitySystemComponent* GetPawnASC() const;
};
