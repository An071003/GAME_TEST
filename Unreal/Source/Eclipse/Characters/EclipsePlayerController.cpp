// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/EclipsePlayerController.h"
#include "Characters/EclipseInputConfig.h"
#include "Abilities/EclipseAbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

void AEclipsePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// T-013: get UEnhancedInputLocalPlayerSubsystem from GetLocalPlayer(); if both it and GameplayMappingContext are valid,
	// AddMappingContext(GameplayMappingContext, MappingContextPriority). Log a Warning (LogEclipse) if the context is null.
}

void AEclipsePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// T-013: Cast InputComponent to UEnhancedInputComponent (return if cast fails or InputConfig is null), then:
	//  - BindAction(InputConfig->MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move) and the same for LookAction (skip null actions).
	//  - For every entry in InputConfig->AbilityInputs (skip null Action or invalid InputTag):
	//      BindAction(Entry.Action, ETriggerEvent::Started,   this, &ThisClass::AbilityInputPressed,  Entry.InputTag);
	//      BindAction(Entry.Action, ETriggerEvent::Completed, this, &ThisClass::AbilityInputReleased, Entry.InputTag);
	//  - LockOnAction and InteractAction are NOT bound here (T-017 / M3).
}

void AEclipsePlayerController::Move(const FInputActionValue& Value)
{
	// T-013: FVector2D Axis = Value.Get<FVector2D>(); build a yaw-only rotation from GetControlRotation();
	// APawn* P = GetPawn(); if valid: P->AddMovementInput(Forward, Axis.Y); P->AddMovementInput(Right, Axis.X).
}

void AEclipsePlayerController::Look(const FInputActionValue& Value)
{
	// T-013: FVector2D Axis = Value.Get<FVector2D>(); AddYawInput(Axis.X); AddPitchInput(Axis.Y).
}

void AEclipsePlayerController::AbilityInputPressed(FGameplayTag InputTag)
{
	// T-013: if (UEclipseAbilitySystemComponent* ASC = GetPawnASC()) ASC->AbilityInputTagPressed(InputTag);
}

void AEclipsePlayerController::AbilityInputReleased(FGameplayTag InputTag)
{
	// T-013: if (UEclipseAbilitySystemComponent* ASC = GetPawnASC()) ASC->AbilityInputTagReleased(InputTag);
}

UEclipseAbilitySystemComponent* AEclipsePlayerController::GetPawnASC() const
{
	// T-013: return Cast<UEclipseAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn()));
	// (include "AbilitySystemGlobals.h"). Return nullptr when there is no pawn.
	return nullptr;
}
