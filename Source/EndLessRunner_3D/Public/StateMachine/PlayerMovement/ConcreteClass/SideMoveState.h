// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/PlayerMovement/PlayerMoveAbstract.h"


/**
 * 
 */
class ENDLESSRUNNER_3D_API SideMoveState : public PlayerMoveAbstract
{
public:
	SideMoveState();
	~SideMoveState();

	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	int CurrentLane;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	int TotalNumberOfLane;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	float LaneWidth;

};
