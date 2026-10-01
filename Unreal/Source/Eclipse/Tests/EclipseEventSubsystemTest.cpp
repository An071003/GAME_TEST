// Copyright Epic Games, Inc. All Rights Reserved.

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "Engine/GameInstance.h"
#include "Core/EclipseEventSubsystem.h"
#include "Core/EclipseGameplayTags.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEclipseEventSubsystemTest, "Eclipse.Core.EventSubsystem",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::ProductFilter)

bool FEclipseEventSubsystemTest::RunTest(const FString& Parameters)
{
	// Subsystems have ClassWithin=GameInstance, so a bare GameInstance is the outer; Initialize is not needed.
	UEclipseEventSubsystem* Bus = NewObject<UEclipseEventSubsystem>(NewObject<UGameInstance>(GetTransientPackage()));
	TestNotNull(TEXT("Subsystem created"), Bus);

	int32 CallCount = 0;
	FVector LastPayload = FVector::ZeroVector;
	const FGameplayTag Channel = EclipseTags::Event_Boss_Defeated.GetTag();

	FEclipseEventHandle Handle = Bus->Listen(Channel, FEclipseEventDelegate::CreateLambda(
		[&](FGameplayTag InChannel, const FInstancedStruct& Payload)
		{
			++CallCount;
			if (const FVector* V = Payload.GetPtr<FVector>())
			{
				LastPayload = *V;
			}
		}));
	TestTrue(TEXT("Handle valid"), Handle.IsValid());

	Bus->Broadcast(Channel, FInstancedStruct::Make(FVector(1.0, 2.0, 3.0)));
	TestEqual(TEXT("Listener called once"), CallCount, 1);
	TestEqual(TEXT("Payload delivered"), LastPayload, FVector(1.0, 2.0, 3.0));

	Bus->Broadcast(EclipseTags::Event_Player_Died.GetTag());
	TestEqual(TEXT("Other channel not delivered"), CallCount, 1);

	Bus->Unlisten(Handle);
	TestFalse(TEXT("Handle cleared"), Handle.IsValid());
	Bus->Broadcast(Channel, FInstancedStruct::Make(FVector::OneVector));
	TestEqual(TEXT("Not called after Unlisten"), CallCount, 1);

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
