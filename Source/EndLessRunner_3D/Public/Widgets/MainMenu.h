// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

	/*Level Character Selection Map Name*/
	UPROPERTY()
	FName CharacterSelectMapName;
	UPROPERTY()
	FName RunningLevelName;

	/*Texts*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentHighestScore;
    UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScoreText;

	/*Buttons*/
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	void BindText();

	UFUNCTION()
	void StartButtonFunction();
	UFUNCTION()
	void QuitButtonFunction();
	
};
