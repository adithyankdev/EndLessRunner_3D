// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/PlayerMovement/PlayerMoveAbstract.h"


/**
 * 
 */
class ENDLESSRUNNER_3D_API JumpState : public PlayerMoveAbstract
{

protected:

	FTimerHandle StopJumpTime;

public:
	JumpState();
	virtual ~JumpState();

	FTimerHandle ApplyGravityTimer;

	bool bIsJumping;

	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;

	virtual void ExitState(ARunningPlayer* Player) override;

	bool OnGround(ARunningPlayer* Player, UWorld* World);

};
