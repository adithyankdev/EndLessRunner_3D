// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/JumpState.h"
#include "Player/RunningPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"

JumpState::JumpState()
{
	bIsJumping = false;
}

JumpState::~JumpState()
{
}

void JumpState::EnterState(ARunningPlayer* Player, UWorld* World)
{
	if (bIsJumping == false)
	{
		FString Debug = TEXT("Jump Triggered");
		UKismetSystemLibrary::PrintString(World, Debug, true, true, FLinearColor::Black, 5);
		if (OnGround(Player, World))
		{
			bIsJumping = true;
			FVector LaunchVelocity = FVector(0, 0, 500);
			Player->LaunchCharacter(LaunchVelocity, false, false);
			World->GetTimerManager().SetTimer(StopJumpTime, [this, Player]() { this->ExitState(Player); }, 1.0f, true);
		}
		else
		{
			ExitState(Player);
		}
	}
}
	 

void JumpState::ExitState(ARunningPlayer* Player)
{
	bIsJumping = false;
	Player->CurrentState = nullptr; 

}

bool JumpState::OnGround(ARunningPlayer* Player,UWorld* World)
{
	FHitResult Hit;
	FVector Start = Player->DirectionArrow->GetComponentLocation();
	FVector End = Start - FVector(0.0f, 0.0f, 50.0f);
	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);

	bool OnGround = World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, Params);
	DrawDebugLine(World, Start, End, FColor::Red, true, 1, 0, 1);
	return OnGround;
}
