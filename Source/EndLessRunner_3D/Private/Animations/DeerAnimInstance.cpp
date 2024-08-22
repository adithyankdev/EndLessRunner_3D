// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/DeerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDeerAnimInstance::NativeInitializeAnimation()
{
	if (TryGetPawnOwner())
	{
		OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	}
}

void UDeerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (OwnerCharacter)
	{
		IsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();

		ZVelocity = OwnerCharacter->GetVelocity().Z;
	}
}