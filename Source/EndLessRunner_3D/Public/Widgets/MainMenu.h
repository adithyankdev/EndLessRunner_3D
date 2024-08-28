// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentHighestScore;

	void BindText();
	
};
