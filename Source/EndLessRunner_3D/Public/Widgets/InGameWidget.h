// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	int32 ScoreValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HightestScoreValue;
	
};
