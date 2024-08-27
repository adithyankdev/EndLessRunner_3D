// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RunnerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API URunnerSaveGame : public USaveGame
{
	GENERATED_BODY()
	
private :

	int32 HighestScore;

};
