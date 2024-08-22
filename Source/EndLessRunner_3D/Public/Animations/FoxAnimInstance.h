// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FoxAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API UFoxAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly)
	float ZVelocity;
	
};
