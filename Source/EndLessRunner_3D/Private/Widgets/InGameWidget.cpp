// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InGameWidget.h"
#include "Components/TextBlock.h"

#include "GameInstance/RunnerGameInstance.h"
#include "Interface/GameInstanceInterface.h"

#include "Runtime/Engine/Public/TimerManager.h"


void UInGameWidget::NativeConstruct()
{
	ScoreValue = 0; 

	BindText();

	//Caching Interface
	if (GetGameInstance()->Implements<UGameInstanceInterface>())
	{
		if (IGameInstanceInterface* Interface = Cast<IGameInstanceInterface>(GetGameInstance()))
		{
			GM_Interface.SetInterface(Interface);
			GM_Interface.SetObject(GetGameInstance());
		}
	}
	StartScoreUpdating();
}

void UInGameWidget::BindText()
{
	FText TextToBind = FText::FromString(FString::FromInt(ScoreValue));
	HighestScoreValue->SetText(TextToBind);
}

void UInGameWidget::StartScoreUpdating()
{
	GetGameInstance()->GetWorld()->GetTimerManager().SetTimer(ScoreUpdateTimer, this, &UInGameWidget::UpdateScore, 0.5, true);
}

void UInGameWidget::UpdateScore()
{
	ScoreValue++;
	BindText();
	//Storing The Current Point To Instnace For Save Data
	GM_Interface->SetHighestScore(ScoreValue);
}
