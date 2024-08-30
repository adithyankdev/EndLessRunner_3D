// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameEndWidget.h"
#include "Components/Button.h"

#include "Interface/GameInstanceInterface.h"
#include "SaveGame/RunnerSaveGame.h"

#include "Player/RnningPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameEndWidget::NativeConstruct()
{
	RestartGameButton->OnClicked.AddDynamic(this, &UGameEndWidget::RestartButtonFunction);
	QuitLevelButton->OnClicked.AddDynamic(this, &UGameEndWidget::QuitButtonFunction);

	UKismetSystemLibrary::PrintString(GetGameInstance()->GetWorld(), TEXT("Game Over Widget NativeConstruct"));
}

void UGameEndWidget::RestartButtonFunction()
{
	UKismetSystemLibrary::PrintString(GetGameInstance()->GetWorld(), TEXT("RESTART"));
	//UKismetSystemLibrary::ExecuteConsoleCommand(GetGameInstance()->GetWorld(), TEXT("RestartLevel"), GetGameInstance()->GetWorld()->GetFirstPlayerController());
}

void UGameEndWidget::QuitButtonFunction()
{
	UKismetSystemLibrary::PrintString(GetGameInstance()->GetWorld(), TEXT("QUIT GAME"));
	//UGameplayStatics::OpenLevel(GetGameInstance()->GetWorld(),)
}
