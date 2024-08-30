// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitLevelButton;

	UFUNCTION()
	void RestartButtonFunction();

	UFUNCTION()
	void QuitButtonFunction();

};
