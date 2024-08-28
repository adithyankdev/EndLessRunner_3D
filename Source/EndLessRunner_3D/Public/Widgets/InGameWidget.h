// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/GameInstanceInterface.h"
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

	void NativeConstruct() override;

	/*Score Value*/
	UPROPERTY()
	int32 ScoreValue;

	/*Text Block For Representing The ScoreValue*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighestScoreValue;

	/*Caching GameInstnace Interface*/
	UPROPERTY()
	TScriptInterface<IGameInstanceInterface>GM_Interface;
	
	/*Function For Binding The TextBlock And Int Variable*/
	void BindText();
	
	/*Function Calling UpdateFunction Using Timer*/
	void StartScoreUpdating();

	/*Timer For Calling Update Function*/
	FTimerHandle ScoreUpdateTimer;

	/*For Updating The Score Over Time*/
	void UpdateScore();
	
};
