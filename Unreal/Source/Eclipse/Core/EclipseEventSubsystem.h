// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EclipseEventSubsystem.generated.h"

/** Native listener: (Channel, Payload). Payload may be an invalid FInstancedStruct. */
DECLARE_DELEGATE_TwoParams(FEclipseEventDelegate, FGameplayTag /*Channel*/, const FInstancedStruct& /*Payload*/);

/** Blueprint-facing: fires for every broadcast; the BP filters by channel. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEclipseEventDynamicDelegate, FGameplayTag, Channel, const FInstancedStruct&, Payload);

struct FEclipseEventHandle
{
	FGameplayTag Channel;
	uint32 Id = 0;

	bool IsValid() const { return Id != 0; }
};

/** Decoupled event bus (ADR-011). Listeners match the exact channel tag, parent tags are not matched. */
UCLASS()
class ECLIPSE_API UEclipseEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Broadcast(FGameplayTag Channel, const FInstancedStruct& Payload = FInstancedStruct());

	FEclipseEventHandle Listen(FGameplayTag Channel, FEclipseEventDelegate Delegate);
	void Unlisten(FEclipseEventHandle& Handle);

	UPROPERTY(BlueprintAssignable, Category = "Eclipse|Events")
	FEclipseEventDynamicDelegate OnEventBroadcast;

	virtual void Deinitialize() override;

private:
	struct FListener
	{
		uint32 Id = 0;
		FEclipseEventDelegate Delegate;
	};

	TMap<FGameplayTag, TArray<FListener>> Listeners;
	uint32 NextId = 1;
};
