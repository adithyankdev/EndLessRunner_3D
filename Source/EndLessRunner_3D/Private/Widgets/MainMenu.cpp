// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"
#include "Components/TextBlock.h"
#include "Interface/GameInstanceInterface.h"
#include "SaveGame/RunnerSaveGame.h"


void UMainMenu::NativeConstruct()
{
	BindText();
}

void UMainMenu::BindText()
{
	if (GetGameInstance() && GetGameInstance()->Implements<UGameInstanceInterface>())
	{
		if(IGameInstanceInterface* Interface = Cast <IGameInstanceInterface>(GetGameInstance()))
		{
		    URunnerSaveGame* SaveGame =  Interface->GetSaveGame();
			FText TextToBind = FText::FromString(FString::FromInt(SaveGame->HighestScore));
			CurrentHighestScore->SetText(TextToBind);
		}
	}
}
