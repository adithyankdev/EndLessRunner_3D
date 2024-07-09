// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetLvlManagerMembers.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGetLvlManagerMembers : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENDLESSRUNNER_3D_API IGetLvlManagerMembers
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void LvlManagerLaneValues(int& TotalLanes , float& WidthOfLane)=0;
	virtual int GetRandomInteger(int RandomNumber) = 0;
	virtual void GetSpawnTransform() = 0;
	virtual void SetCanPlayerTurn(bool Value) = 0; 
	virtual bool GetCanPlayerTurn() = 0;
};
