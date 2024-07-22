// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/GetLvlManagerMembers.h"


class SideMoveState;

/**
 * 
 */
class ENDLESSRUNNER_3D_API ReorganisePlayer
{
protected:

	TMap<int, FVector>LaneLocations;

public:
	ReorganisePlayer();
	~ReorganisePlayer();

	void Begin(const TScriptInterface<IGetLvlManagerMembers>& LvlInterface,FVector PlayerLocation ,FVector PlayerForwardVector, SideMoveState* StateMachine);

	void GetTurnLaneLocatins(TScriptInterface<IGetLvlManagerMembers> LvlInterface);
	void RearrangePlayerLocation(TScriptInterface<IGetLvlManagerMembers> LvlInterface,FVector PlayerLocation, FVector PlayerForwardVector, SideMoveState* StateMachine);

};
