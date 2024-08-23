// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RunnerGameInstance.h"

void URunnerGameInstance::Init()
{

}

void URunnerGameInstance::SetCharacterMesh(USkeletalMesh* NewMesh)
{
	GameCharacterMesh = NewMesh; 
}

USkeletalMesh* URunnerGameInstance::GetCharacterMesh()
{
	return GameCharacterMesh;
}
