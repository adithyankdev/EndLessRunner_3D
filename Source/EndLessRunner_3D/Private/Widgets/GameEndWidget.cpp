// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameEndWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameEndWidget::NativeConstruct()
{
	RestartGameButton->OnClicked.AddDynamic(this, &UGameEndWidget::RestartButtonFunction);
	QuitLevelButton->OnClicked.AddDynamic(this, &UGameEndWidget::QuitButtonFunction);
}

void UGameEndWidget::RestartButtonFunction()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetGameInstance()->GetWorld(), TEXT("RestartLevel"), GetGameInstance()->GetWorld()->GetFirstPlayerController());
}

void UGameEndWidget::QuitButtonFunction()
{
	//UGameplayStatics::OpenLevel(GetGameInstance()->GetWorld(),)
}
