// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interface/GameInstanceInterface.h"
#include "RunnerGameInstance.generated.h"

class USkeletalMesh;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API URunnerGameInstance : public UGameInstance , public IGameInstanceInterface
{
	GENERATED_BODY()
	
protected:

	void Init() override;

	UPROPERTY()
	USkeletalMesh* GameCharacterMesh;

public:

	void SetCharacterMesh(USkeletalMesh* NewMesh) override;

	USkeletalMesh* GetCharacterMesh() override;



};
