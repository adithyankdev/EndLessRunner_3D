// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/LevelManager.h"
#include "StateMachine/PlayerMovement/PlayerMoveAbstract.h"


/**
 * 
 */
class ENDLESSRUNNER_3D_API SideMoveState : public PlayerMoveAbstract
{
public:
	SideMoveState();
	virtual ~SideMoveState();

	bool FirstCheck;

	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;

	virtual void ExitState(ARunningPlayer* Player) override;

	UPROPERTY()
	TScriptInterface<IGetLvlManagerMembers>LvlInterface;

	UPROPERTY();
	int CurrentLane;
	UPROPERTY()
	int TotalNumberOfLane;
	UPROPERTY()
	float LaneWidth;

	UPROPERTY()
	FRotator DesiredRotation;

	

	void GetLvlManagerInfo(UWorld* World);

};
