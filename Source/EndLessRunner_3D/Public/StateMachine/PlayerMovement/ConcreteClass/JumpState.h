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
	/*Time To Stop Jumping, Avoid Spawning*/
	FTimerHandle StopJumpTime;

public:
	JumpState();
	virtual ~JumpState();

	/*Variable For Checking Wheather The Player Is Jumping*/
	bool bIsJumping;

	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;

	virtual void ExitState(ARunningPlayer* Player) override;

	/*Line Trace For Checking Player Is On Ground*/
	bool OnGround(ARunningPlayer* Player, UWorld* World);

};
