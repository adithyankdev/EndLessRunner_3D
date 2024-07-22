// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/LevelManager.h"
#include "StateMachine/PlayerMovement/PlayerMoveAbstract.h"

class ReorganisePlayer;

/**
 * 
 */
class ENDLESSRUNNER_3D_API SideMoveState : public PlayerMoveAbstract
{
public:

	SideMoveState();
	~SideMoveState();
	
protected:

	ReorganisePlayer* ReChangePlayer;

	/*For Retreving The LvlManger Data Only Once*/
	bool FirstCheck;       

	/*State Function Of Perfoming Action*/
	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;         
	virtual void ExitState(ARunningPlayer* Player) override;

	/*For Storing The Referance Of LvlMangerInterface*/
	UPROPERTY() 
	TScriptInterface<IGetLvlManagerMembers>LvlInterface;   

	UPROPERTY()
	TScriptInterface<IGetPlayerInfoInterface>PlayerInterface;

	/*Variables That Store The LaneInfo From The LvlManager*/
	UPROPERTY();
	int CurrentLane;
	UPROPERTY()
	int TotalNumberOfLane;                     
	UPROPERTY()
	float LaneWidth;

	/*For Storing The Rotation Of The Player , Which Is Use When On Perfoming Another Rotation*/
	UPROPERTY()
	FRotator DesiredRotation; 

	/*Variable That Store The Different Values According To The Player Rotation , For Its Lane Movement*/
	UPROPERTY()
	int TurnIndex;

	/*Function That Call The Movement Function Based On The Index*/
	void DeterminePlayerMovement(int Index,ARunningPlayer* Player,UWorld* World);

	/*Function That Set The Index Of Player Based On The Rotation */
	void SetPlayerMoveIndex(ARunningPlayer* Player);

	/*Function That Move Player According To Direction Input*/
	void MovePlayer(ARunningPlayer* Player,FVector Direction, UWorld* World);

	/*Function For Retriving The LvlMangerInfo*/
	void CacheInterfaces(UWorld* World, ARunningPlayer* Player);

public:

	void ChangeCurrentLane(int NewLane);

	

};
