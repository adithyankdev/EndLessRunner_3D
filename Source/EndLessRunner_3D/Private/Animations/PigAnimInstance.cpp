// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PigAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPigAnimInstance::NativeInitializeAnimation()
{
	if (TryGetPawnOwner())
	{
		OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	}
}

void UPigAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (OwnerCharacter)
	{
		IsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();

		ZVelocity = OwnerCharacter->GetVelocity().Z;
	}
}
