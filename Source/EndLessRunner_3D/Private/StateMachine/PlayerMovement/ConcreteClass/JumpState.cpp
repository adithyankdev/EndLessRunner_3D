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
		
		if (OnGround(Player, World))
		{
			bIsJumping = true;
			FVector LaunchVelocity = FVector(0, 0, 500);
			Player->LaunchCharacter(LaunchVelocity, false, false);
			World->GetTimerManager().SetTimer(StopJumpTime, [this]() { this->ResetJumping(); }, 1.0f, true);
			
		}
		
	}
}

void JumpState::ResetJumping()
{
	bIsJumping = false;
}
	 

bool JumpState::OnGround(ARunningPlayer* Player,UWorld* World)
{
	FHitResult Hit;
	FVector Start = Player->JumpArrow->GetComponentLocation();
	FVector End = Start - FVector(0.0f, 0.0f, 50.0f);
	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);
	bool IsHit = World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel);
	return IsHit;
}
