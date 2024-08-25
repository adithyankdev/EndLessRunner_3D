// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RunnerGameInstance.h"
#include "Kismet/GameplayStatics.h"

void URunnerGameInstance::Init()
{
	RunningLevelName = FName("Level");
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
