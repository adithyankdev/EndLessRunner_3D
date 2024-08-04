// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"
#include "FunctionLibrary/PublicFunctionLibrary.h"
#include "Player/RunningPlayer.h"
#include "Kismet/GameplayStatics.h"


//Constructor
SideMoveState::SideMoveState()
{
	FirstCheck = false;
	CurrentLane = 0.0f;
	TotalNumberOfLane = 0;
	LaneWidth = 0.0f;

}
SideMoveState::~SideMoveState()
{
    LvlInterface = nullptr;
    PlayerInterface = nullptr;
}
//Function That Trigger First
void SideMoveState::EnterState(ARunningPlayer* Player, UWorld* World)
{
    if (!FirstCheck)
    {
       CacheInterfaces(World,Player);                 //Getting The Lane Information And The LvlManager Interface ...
        FirstCheck = true;
    }
    if (Player->CurrentMoveValue > 0 && CurrentLane < TotalNumberOfLane)  //LeftButton...
    {
        PlayerLocation = Player->GetActorLocation();
        TargetPosition = FVector(0,PlayerLocation.Y -  LaneWidth,PlayerLocation.Z);
        Player->SetActorLocation(TargetPosition);
        CurrentLane++;
    }
    else if (Player->CurrentMoveValue < 0 && CurrentLane > 1)       //Right Button...
    {
        PlayerLocation = Player->GetActorLocation();
        TargetPosition = FVector(0,PlayerLocation.Y + LaneWidth,PlayerLocation.Z);
        Player->SetActorLocation(TargetPosition);
        CurrentLane--;
    }  
   ;
}


//Function That Retrive The LaneInfo From LvlManager ...
void SideMoveState::CacheInterfaces(UWorld* World, ARunningPlayer* Player)
{
    AActor* LvlActor = UGameplayStatics::GetActorOfClass(World, ALevelManager::StaticClass());
    if (LvlActor)
    {
        LvlInterface.SetObject(LvlActor);
        if (LvlActor->GetClass()->ImplementsInterface(UGetLvlManagerMembers::StaticClass()))
        {
            IGetLvlManagerMembers* Interface = Cast<IGetLvlManagerMembers>(LvlActor);
            LvlInterface.SetInterface(Interface);                           //Using The ScriptInterface For Caching The LvlManagerInterface...
            LvlInterface->LvlManagerLaneValues(TotalNumberOfLane, LaneWidth);
            CurrentLane = (TotalNumberOfLane / 2) + 1;
        }
    }
    PlayerInterface.SetObject(Player);
    PlayerInterface.SetInterface(Cast<IGetPlayerInfoInterface>(Player));

}
