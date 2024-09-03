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
	//Checking Wheather SaveGame Exist 
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		//If Exist , Then Loading The Data
		SaveGameObject = Cast<URunnerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		
	}
	else
	{
		//If Doesn't Exist , The Creating A Slot And Saving It 
		SaveGameObject = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName, 0);

		
	}
}

void URunnerGameInstance::SetCharacterMesh(USkeletalMesh* NewMesh,int CurrentAnimationIndex)
{
	//Storing Values For Passing It On Next Lvl
	GameCharacterMesh = NewMesh; 
	AnimationIndex = CurrentAnimationIndex;

	//Openening Next Lvl After Player Selecting The Mesh
	UGameplayStatics::OpenLevel(GetWorld(), RunningLevelName);
}

void URunnerGameInstance::SaveData(int32 ScoreValue)
{
	SaveGameObject->HighestScore = ScoreValue;
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName,0);

}

URunnerSaveGame* URunnerGameInstance::GetSaveGame()
{
	return SaveGameObject;
}

USkeletalMesh* URunnerGameInstance::GetCharacterMesh()
{
	return GameCharacterMesh;
}

int URunnerGameInstance::GetAnimationIndex()
{
	return AnimationIndex;
}
