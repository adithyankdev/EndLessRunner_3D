// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"
#include "FunctionLibrary/PublicFunctionLibrary.h"
#include "Player/RunningPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "FunctionLibrary/ReorganisePlayer.h"


//Constructor
SideMoveState::SideMoveState()
{
	FirstCheck = false;
	CurrentLane = 0.0f;
	TotalNumberOfLane = 0;
	LaneWidth = 0.0f;
	TurnIndex = 0;

    ReChangePlayer = new ReorganisePlayer();

}
SideMoveState::~SideMoveState()
{
    ReChangePlayer = nullptr;
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

    if (LvlInterface->GetCanPlayerTurn())
    {
        FRotator RotationOffset;
        int PlayerTurnIndex = 0;
        if (Player->CurrentMoveValue > 0)
        {
            RotationOffset = { 0.0f, -90.0f, 0.0 };               //Setting The Player Location If It Collide With Corner Tile...
            PlayerTurnIndex = 1;
            LvlInterface->SetCanPlayerTurn(false);
        }                                                         
        else if (Player->CurrentMoveValue < 0)
        {
            RotationOffset = { 0.0f, 90.0f, 0.0f };
            PlayerTurnIndex = 0;
            LvlInterface->SetCanPlayerTurn(false);
        }
        Player->Controller->SetControlRotation(RotationOffset + DesiredRotation);
        DesiredRotation += RotationOffset;
        PlayerInterface->SetPlaneConstraints();
        LvlInterface->SetActorNewDirection(PlayerTurnIndex);
        ReChangePlayer->Begin(LvlInterface, Player->GetActorLocation(), Player->GetActorForwardVector(), this);
 
    }
    else
    {
        SetPlayerMoveIndex(Player);                              //Setting The Player Index Based On Current Direction Facing....
        DeterminePlayerMovement(TurnIndex, Player,World);
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
void SideMoveState::DeterminePlayerMovement(int Index, ARunningPlayer* Player, UWorld* World)
{
    switch (Index)
    {
    case 0:
        MovePlayer(Player, FVector(0, 1, 0), World); // Positive Y direction (Default)...
        break;
    case 1:
        MovePlayer(Player, FVector(0, -1, 0), World); // Negative Y direction...
        break;                                                                           //Player Current Facing Direction Is Passed...
    case 2:
        MovePlayer(Player, FVector(-1, 0, 0), World); // Negative X direction...
        break;
    case 3:
        MovePlayer(Player, FVector(1, 0, 0), World); // Postive X direction...
        break;
    }
}
//Function That MovePlayer(LaneWise) According To Direction Of Player Facing ....
void SideMoveState::MovePlayer(ARunningPlayer* Player, FVector Direction,  UWorld* World)
{
    if (Player->CurrentMoveValue > 0 && CurrentLane < TotalNumberOfLane)  //LeftButton...
    {
        FVector TargetPosition = Player->GetActorLocation() - (Direction * LaneWidth);
        Player->SetActorLocation(TargetPosition);
        CurrentLane++;
        FString D = FString::Printf(TEXT("%d"),CurrentLane);
        UKismetSystemLibrary::PrintString(World, D);

    }
    else if (Player->CurrentMoveValue < 0 && CurrentLane > 1)       //Right Button...
    {
        FVector TargetPosition = Player->GetActorLocation() + (Direction * LaneWidth);
        Player->SetActorLocation(TargetPosition);
        CurrentLane--;
        FString D = FString::Printf(TEXT("%d"), CurrentLane);
        UKismetSystemLibrary::PrintString(World, D);
    }
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

void SideMoveState::ChangeCurrentLane(int NewLane)
{
    CurrentLane = NewLane;
    UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentLane);

}
