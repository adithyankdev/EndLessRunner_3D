// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"
#include "Components/TextBlock.h"
#include "Interface/GameInstanceInterface.h"

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
			FText TextToBind = FText::FromString(FString::FromInt(Interface->GetHightestScoreValue()));
			CurrentHighestScore->SetText(TextToBind);
		}
	}
}
