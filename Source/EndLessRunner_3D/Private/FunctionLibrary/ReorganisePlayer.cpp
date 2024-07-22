// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/ReorganisePlayer.h"
#include "Player/RunningPlayer.h"
#include "Interface/TurnTileInterface.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"



ReorganisePlayer::ReorganisePlayer()
{
	//SideStateMachine = new SideMoveState();
}

ReorganisePlayer::~ReorganisePlayer()
{
	//SideStateMachine = nullptr;
	
}

void ReorganisePlayer::Begin(const TScriptInterface<IGetLvlManagerMembers>& LvlInterface, FVector PlayerLocation,FVector PlayerForwardVector,SideMoveState* StateMachine)
{
	GetTurnLaneLocatins(LvlInterface);
	RearrangePlayerLocation(LvlInterface,PlayerLocation,PlayerForwardVector,StateMachine);
}

void ReorganisePlayer::GetTurnLaneLocatins(TScriptInterface<IGetLvlManagerMembers>LvlInterface)
{
	AActor* TurnActor = LvlInterface->GetLatestTurnTile();
	if (ITurnTileInterface* TurnInterface = Cast <ITurnTileInterface>(TurnActor))
	{
		LaneLocations =  TurnInterface->GetTileLineLocations();
	}
}

void ReorganisePlayer::RearrangePlayerLocation(TScriptInterface<IGetLvlManagerMembers> LvlInterface,FVector PlayerLocation, FVector PlayerForwardVector, SideMoveState* StateMachine)
{
	
	if (PlayerForwardVector.X > PlayerForwardVector.Y && PlayerForwardVector.X > 0)
	{
		float YLocation = PlayerLocation.Y;

		if (LaneLocations.Num() > 0)  // Check if LaneLocations is not empty
		{
			float ClosestDifference = TNumericLimits<float>::Max();
			int ClosestLane = -1;

			for (const auto& Lane : LaneLocations)
			{
				float Difference = FMath::Abs(YLocation - Lane.Value.Y);
				if (Difference < ClosestDifference)
				{
					ClosestDifference = Difference;
					ClosestLane = Lane.Key;
				}
			}

			if (ClosestLane != -1)
			{
				StateMachine->ChangeCurrentLane(ClosestLane);
				PlayerLocation.Y = LaneLocations[ClosestLane].Y;
				LvlInterface->SetPlayerLocationOnTurn(PlayerLocation);
			}
		}
	}
	else if(PlayerForwardVector.X < PlayerForwardVector.Y && PlayerForwardVector.Y > 0)
	{
		float XLocation = PlayerLocation.X;

		if (LaneLocations.Num() > 0)  // Check if LaneLocations is not empty
		{
			float ClosestDifference = TNumericLimits<float>::Max();
			int ClosestLane = -1;

			for (const auto& Lane : LaneLocations)
			{
				float Difference = FMath::Abs(XLocation - Lane.Value.X);
				if (Difference < ClosestDifference)
				{
					ClosestDifference = Difference;
					ClosestLane = Lane.Key;
				}
			}

			if (ClosestLane != -1)
			{
				StateMachine->ChangeCurrentLane(ClosestLane);
				PlayerLocation.X = LaneLocations[ClosestLane].X;
				LvlInterface->SetPlayerLocationOnTurn(PlayerLocation);
			}
		}
	}
	else if (PlayerForwardVector.X < PlayerForwardVector.Y && PlayerForwardVector.X < 0)
	{
		float XLocation = PlayerLocation.Y;

		if (LaneLocations.Num() > 0)  // Check if LaneLocations is not empty
		{
			float ClosestDifference = TNumericLimits<float>::Max();
			int ClosestLane = -1;

			for (const auto& Lane : LaneLocations)
			{
				float Difference = FMath::Abs(XLocation - Lane.Value.Y);
				if (Difference < ClosestDifference)
				{
					ClosestDifference = Difference;
					ClosestLane = Lane.Key;
				}
			}

			if (ClosestLane != -1)
			{
				StateMachine->ChangeCurrentLane(ClosestLane);
				PlayerLocation.Y = LaneLocations[ClosestLane].Y;
				LvlInterface->SetPlayerLocationOnTurn(PlayerLocation);
			}
		}
	}
	else
	{
		float XLocation = PlayerLocation.X;
		if (auto Itr = LaneLocations.CreateIterator())
		{
			float Difference = FMath::Abs(XLocation - Itr->Value.X);
			int  CurrentLane = Itr->Key;
			++Itr;
			for (; Itr; ++Itr)
			{
				float Value = FMath::Abs(XLocation - Itr->Value.X);
				if (Value < Difference)
				{
					CurrentLane = Itr->Key;
					Difference = Value;
				}
			}
			StateMachine->ChangeCurrentLane(CurrentLane);
			PlayerLocation.X = LaneLocations[CurrentLane].X;
			LvlInterface->SetPlayerLocationOnTurn(PlayerLocation);
		}
	}
}



