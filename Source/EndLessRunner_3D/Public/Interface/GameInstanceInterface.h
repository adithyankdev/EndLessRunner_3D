// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameInstanceInterface.generated.h"

class USkeletalMesh;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENDLESSRUNNER_3D_API IGameInstanceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetCharacterMesh(USkeletalMesh* NewMesh,int CurrentAnimationIndex) = 0;
	virtual USkeletalMesh* GetCharacterMesh() = 0; 
	virtual int GetAnimationIndex() = 0; 
};
