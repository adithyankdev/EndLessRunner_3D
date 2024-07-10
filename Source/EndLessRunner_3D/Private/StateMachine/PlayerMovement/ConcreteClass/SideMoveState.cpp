// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"
#include "FunctionLibrary/PublicFunctionLibrary.h"
#include "Player/RunningPlayer.h"
#include "Kismet/GameplayStatics.h"


SideMoveState::SideMoveState()
{
	FirstCheck = false;
	CurrentLane = 0.0f;
	TotalNumberOfLane = 0;
	LaneWidth = 0.0f;

}

SideMoveState::~SideMoveState()
{
	
}

void SideMoveState::EnterState(ARunningPlayer* Player, UWorld* World)
{	
	if (!FirstCheck)GetLvlManagerInfo(World); FirstCheck = true;
	
	if (Player->CurrentMoveValue > 0 and CurrentLane < TotalNumberOfLane)
	{
		if (LvlInterface->GetCanPlayerTurn())
	   	{
			FRotator RotationOffset(0.0f, -90.0f, 0.0f);
			Player->Controller->SetControlRotation(RotationOffset + DesiredRotation);
			DesiredRotation += RotationOffset;
			
	  	}
		else
		{
			float TargetPosition = Player->GetActorLocation().Y - LaneWidth;
			FVector NewLocation = { Player->GetActorLocation().X , TargetPosition ,Player->GetActorLocation().Z };
			Player->SetActorLocation(NewLocation);
			CurrentLane++;
		}		
		
	}
	else if (Player->CurrentMoveValue < 0 and CurrentLane > 1)
	{
		if (LvlInterface->GetCanPlayerTurn())
		{
			FRotator RotationOffset(0.0f, 90.0f,0.0f);
			Player->Controller->SetControlRotation(RotationOffset + DesiredRotation);
			DesiredRotation += RotationOffset;
		}
		else
		{
			float TargetPosition = Player->GetActorLocation().Y + LaneWidth;
			FVector NewLocation = { Player->GetActorLocation().X , TargetPosition ,Player->GetActorLocation().Z };
			Player->SetActorLocation(NewLocation);
			CurrentLane--;
		}
		
	}
	ExitState(Player);
	
}

void SideMoveState::ExitState(ARunningPlayer* Player)
{
	Player->CurrentState = nullptr;
}


// Helper Function ... 

void SideMoveState::GetLvlManagerInfo(UWorld*World)
{
	AActor* LvlActor =  UGameplayStatics::GetActorOfClass(World, ALevelManager::StaticClass());
	if (LvlActor)
	{
		LvlInterface.SetObject(LvlActor);
		if (LvlActor->GetClass()->ImplementsInterface(UGetLvlManagerMembers::StaticClass()))
		{
			IGetLvlManagerMembers* Interface = Cast<IGetLvlManagerMembers>(LvlActor);
			LvlInterface.SetInterface(Interface);
			LvlInterface->LvlManagerLaneValues(TotalNumberOfLane, LaneWidth);
			CurrentLane = (TotalNumberOfLane / 2) + 1;
	    }
	}
	
}