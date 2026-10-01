// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/EclipseEventSubsystem.h"

void UEclipseEventSubsystem::Broadcast(FGameplayTag Channel, const FInstancedStruct& Payload)
{
	if (!Channel.IsValid())
	{
		return;
	}

	// Copy: a listener may call Listen/Unlisten while being notified.
	if (const TArray<FListener>* Found = Listeners.Find(Channel))
	{
		const TArray<FListener> Snapshot = *Found;
		for (const FListener& Listener : Snapshot)
		{
			Listener.Delegate.ExecuteIfBound(Channel, Payload);
		}
	}

	OnEventBroadcast.Broadcast(Channel, Payload);
}

FEclipseEventHandle UEclipseEventSubsystem::Listen(FGameplayTag Channel, FEclipseEventDelegate Delegate)
{
	FEclipseEventHandle Handle;
	if (!Channel.IsValid() || !Delegate.IsBound())
	{
		return Handle;
	}

	Handle.Channel = Channel;
	Handle.Id = NextId++;
	FListener& NewListener = Listeners.FindOrAdd(Channel).AddDefaulted_GetRef();
	NewListener.Id = Handle.Id;
	NewListener.Delegate = MoveTemp(Delegate);
	return Handle;
}

void UEclipseEventSubsystem::Unlisten(FEclipseEventHandle& Handle)
{
	if (Handle.IsValid())
	{
		if (TArray<FListener>* Found = Listeners.Find(Handle.Channel))
		{
			const uint32 IdToRemove = Handle.Id;
			Found->RemoveAll([IdToRemove](const FListener& L) { return L.Id == IdToRemove; });
			if (Found->IsEmpty())
			{
				Listeners.Remove(Handle.Channel);
			}
		}
	}
	Handle = FEclipseEventHandle();
}

void UEclipseEventSubsystem::Deinitialize()
{
	Listeners.Empty();
	Super::Deinitialize();
}
