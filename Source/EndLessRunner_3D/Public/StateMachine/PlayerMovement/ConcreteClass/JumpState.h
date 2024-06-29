// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/PlayerMovement/PlayerMoveAbstract.h"


/**
 * 
 */
class ENDLESSRUNNER_3D_API JumpState : public PlayerMoveAbstract
{
public:
	JumpState();
	~JumpState();

	FTimerHandle ApplyGravityTimer;

	bool bIsJumping;

	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;


};
