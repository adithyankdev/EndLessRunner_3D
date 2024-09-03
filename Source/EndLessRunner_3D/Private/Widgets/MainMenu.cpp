// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Interface/GameInstanceInterface.h"
#include "SaveGame/RunnerSaveGame.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMainMenu::NativeConstruct()
{
	CharacterSelectMapName = FName("CharacterSelectionMap");
	RunningLevelName = FName("Level");

	StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartButtonFunction);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonFunction);

	BindText();
}

void UMainMenu::BindText()
{
	if (GetGameInstance() && GetGameInstance()->Implements<UGameInstanceInterface>())
	{
		if(IGameInstanceInterface* Interface = Cast <IGameInstanceInterface>(GetGameInstance()))
		{
		    URunnerSaveGame* SaveGame =  Interface->GetSaveGame();
			if (SaveGame->HighestScore > 0)
			{
				FText TextToBind = FText::FromString(FString::FromInt(SaveGame->HighestScore));
				CurrentHighestScore->SetText(TextToBind);
			}
			else
			{
				CurrentHighestScore->SetVisibility(ESlateVisibility::Hidden);
				HighScoreText->SetVisibility(ESlateVisibility::Hidden);
			}
			
		}
	}
}

void UMainMenu::StartButtonFunction()
{
	UGameplayStatics::OpenLevel(GetWorld(),CharacterSelectMapName);
}


void UMainMenu::QuitButtonFunction()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("quit"), GetGameInstance()->GetWorld()->GetFirstPlayerController());
}
