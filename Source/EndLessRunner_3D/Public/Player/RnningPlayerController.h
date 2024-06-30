// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/PlayerInputComponent.h"
#include "RnningPlayerController.generated.h"


class ARunningPlayer;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API ARnningPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	ARnningPlayerController();

	UPlayerInputComponent* PlayerInputComp;

	ARunningPlayer* GetOwnerPlayer();

	virtual void BeginPlay() override;
};
