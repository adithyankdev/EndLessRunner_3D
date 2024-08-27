// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RunnerGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "SaveGame/RunnerSaveGame.h"
#include "Kismet/KismetSystemLibrary.h"

URunnerGameInstance::URunnerGameInstance()
{
	SlotName = FString("EndlessRunnerSaveSlot_1");
	RunningLevelName = FName("Level");
}

void URunnerGameInstance::Init()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Event Init -- GameInstance "), true, true, FLinearColor::Blue);
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveGameObject = Cast<URunnerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SaveGameObject Loaded"), true, true, FLinearColor::Green);
	}
	else
	{
		SaveGameObject = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));

		UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName, 0);

		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SaveGameObject Created "), true, true, FLinearColor::Red);
	}
	
}

void URunnerGameInstance::SetCharacterMesh(USkeletalMesh* NewMesh,int CurrentAnimationIndex)
{
	GameCharacterMesh = NewMesh; 
	AnimationIndex = CurrentAnimationIndex;

	UGameplayStatics::OpenLevel(GetWorld(), RunningLevelName);

	UE_LOG(LogTemp, Warning, TEXT("Game Instnace Function Triggered"));
}

USkeletalMesh* URunnerGameInstance::GetCharacterMesh()
{
	return GameCharacterMesh;
}

int URunnerGameInstance::GetAnimationIndex()
{
	return AnimationIndex;
}
