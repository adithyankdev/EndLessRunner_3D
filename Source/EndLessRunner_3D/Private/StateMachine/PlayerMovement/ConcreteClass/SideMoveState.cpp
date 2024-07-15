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
	TurnIndex = 0;

}
//Function That Trigger First
void SideMoveState::EnterState(ARunningPlayer* Player, UWorld* World)
{
    if (!FirstCheck)
    {
        GetLvlManagerInfo(World);                 //Getting The Lane Information And The LvlManager Interface ...
        FirstCheck = true;
    }

    if (LvlInterface->GetCanPlayerTurn())
    {
        FRotator RotationOffset;
        if (Player->CurrentMoveValue > 0)
        {
            RotationOffset = { 0.0f, -90.0f, 0.0 };               //Setting The Player Location If It Collide With Corner Tile...
        }                                                         
        else if (Player->CurrentMoveValue < 0)
        {
            RotationOffset = { 0.0f, 90.0f, 0.0f };
        }
        Player->Controller->SetControlRotation(RotationOffset + DesiredRotation);
        DesiredRotation += RotationOffset;
        LvlInterface->SetCanPlayerTurn(false);               //Falsing The Value For Avoid More Than Two Rotation  At The Same Time...
        LvlInterface->SetActorNewDirection(FVector(-1,0,0));
      
    }
    else
    {
        SetPlayerMoveIndex(Player);                              //Setting The Player Index Based On Current Direction Facing....
        DeterminePlayerMovement(TurnIndex, Player);         
    }

    ExitState(Player);
}

void SideMoveState::ExitState(ARunningPlayer* Player)
{   
    Player->CurrentState = nullptr;
}

/** Helper Function **/

//Function That Check The Player Forward Direction And Set The Index For Movement ...
void SideMoveState::SetPlayerMoveIndex(ARunningPlayer* Player)
{
    FVector Direction = Player->MovementArrow->GetForwardVector();

    if (FMath::Abs(Direction.X) > FMath::Abs(Direction.Y))
    {
        TurnIndex = (Direction.X > 0) ? 0 : 1;
    }
    else
    {
        TurnIndex = (Direction.Y > 0) ? 2 : 3;
    }
}

//Calling The Movement Function According To The PlayerTurnIndexl....
void SideMoveState::DeterminePlayerMovement(int Index, ARunningPlayer* Player)
{
    switch (Index)
    {
    case 0:
        MovePlayer(Player, FVector(0, 1, 0)); // Positive Y direction (Default)...
        break;
    case 1:
        MovePlayer(Player, FVector(0, -1, 0)); // Negative Y direction...
        break;                                                                           //Player Current Facing Direction Is Passed...
    case 2:
        MovePlayer(Player, FVector(-1, 0, 0)); // Negative X direction...
        break;
    case 3:
        MovePlayer(Player, FVector(1, 0, 0)); // Postive X direction...
        break;
    }
}
//Function That MovePlayer(LaneWise) According To Direction Of Player Facing ....
void SideMoveState::MovePlayer(ARunningPlayer* Player, FVector Direction)
{
    if (Player->CurrentMoveValue > 0 && CurrentLane < TotalNumberOfLane)  //LeftButton...
    {
        FVector TargetPosition = Player->GetActorLocation() - (Direction * LaneWidth);
        Player->SetActorLocation(TargetPosition);
        CurrentLane++;
    }
    else if (Player->CurrentMoveValue < 0 && CurrentLane > 1)       //Right Button...
    {
        FVector TargetPosition = Player->GetActorLocation() + (Direction * LaneWidth);
        Player->SetActorLocation(TargetPosition);
        CurrentLane--;
    }
}

//Function That Retrive The LaneInfo From LvlManager ...
void SideMoveState::GetLvlManagerInfo(UWorld* World)
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

}