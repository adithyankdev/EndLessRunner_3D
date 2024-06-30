// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class ARunningPlayer;

/**
 * 
 */
class ENDLESSRUNNER_3D_API PlayerMoveAbstract
{
public:
	PlayerMoveAbstract();
	virtual ~PlayerMoveAbstract();

	virtual void EnterState(ARunningPlayer* Player, UWorld* World) = 0;
	virtual void ExitState(ARunningPlayer* Player) = 0 ;
};
