// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "PlayerInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API UPlayerInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	UPlayerInputComponent();

	virtual void SetupInputBindings();


	UPROPERTY()
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY()
	class UInputAction* MoveInput;

	UPROPERTY()
	class UInputAction* JumpInput;
};
