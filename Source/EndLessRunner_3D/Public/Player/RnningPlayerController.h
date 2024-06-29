// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RnningPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API ARnningPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
