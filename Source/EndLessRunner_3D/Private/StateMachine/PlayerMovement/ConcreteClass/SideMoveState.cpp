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

	FString Debug = FString::Printf(TEXT("%d"), LaneWidth);
	UKismetSystemLibrary::PrintString(World, Debug,true,true,FLinearColor::Red,5);
	
	if (Player->CurrentMoveValue > 0 and CurrentLane < TotalNumberOfLane)
	{
		FString D = TEXT("Go Right");
		UKismetSystemLibrary::PrintString(World, D);
		float TargetPosition = Player->GetActorLocation().Y - LaneWidth;
		FVector NewLocation = { Player->GetActorLocation().X , TargetPosition ,Player->GetActorLocation().Z };
		Player->SetActorLocation(NewLocation);
		CurrentLane++;
		
	}
	else if (Player->CurrentMoveValue < 0 and CurrentLane > 1)
	{
		FString D = TEXT("Go Left");
		UKismetSystemLibrary::PrintString(World, D);
		float TargetPosition = Player->GetActorLocation().Y + LaneWidth;
		FVector NewLocation = { Player->GetActorLocation().X , TargetPosition ,Player->GetActorLocation().Z };
		Player->SetActorLocation(NewLocation);
	    
       CurrentLane--;
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
	TArray<AActor*>LevelClasses;
	UGameplayStatics::GetAllActorsOfClass(World, ALevelManager::StaticClass(), LevelClasses);
	if (LevelClasses.Num() > 0)
	{
	ALevelManager* lvlManger = Cast <ALevelManager>(LevelClasses[0]);

	 TotalNumberOfLane = lvlManger->NumberOfLane;
	 CurrentLane = (lvlManger->NumberOfLane / 2) + 1;
	 LaneWidth = lvlManger->LaneWidth;
	}
	
}