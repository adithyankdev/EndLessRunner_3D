// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interface/GameInstanceInterface.h"
#include "RunnerGameInstance.generated.h"

class USkeletalMesh;
class URunnerSaveGame;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API URunnerGameInstance : public UGameInstance , public IGameInstanceInterface
{
	GENERATED_BODY()

public:

	URunnerGameInstance();
	
protected:

	void Init() override;

	//Interface Function
	int GetAnimationIndex() override;
	USkeletalMesh* GetCharacterMesh() override;
	void SetCharacterMesh(USkeletalMesh* NewMesh, int CurrentAnimationIndex) override;
	void SetHighestScore(int32 Value) override;
	int32 GetHightestScoreValue() override;
	void ClearUnnecessaryData() override;

private :

	UPROPERTY()
	USkeletalMesh* GameCharacterMesh;

	UPROPERTY()
	int AnimationIndex;

	UPROPERTY()
	FName RunningLevelName;

	UPROPERTY()
	FString SlotName;

	UPROPERTY()
	URunnerSaveGame* SaveGameObject;

	UPROPERTY()
	int32 HightScore;

};
