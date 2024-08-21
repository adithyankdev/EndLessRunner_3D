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
	~SideMoveState();
	
protected:

	/*For Retreving The LvlManger Data Only Once*/
	bool FirstCheck;

	/*State Function Of Perfoming Action*/
	virtual void EnterState(ARunningPlayer* Player, UWorld* World) override;         


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

	/*Function For Retriving The LvlMangerInfo*/
	void CacheInterfaces(UWorld* World, ARunningPlayer* Player);

	//Declaring The Variables For Movement To Avoid Re-Declaration On Each Movement
	FVector PlayerLocation;
	float TargetYPosition;
};
