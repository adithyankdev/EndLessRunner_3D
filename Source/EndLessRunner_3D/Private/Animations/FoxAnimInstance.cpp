// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/FoxAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFoxAnimInstance::NativeInitializeAnimation()
{
	if (TryGetPawnOwner())
	{
		OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	}
	 
}

void UFoxAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (OwnerCharacter)
	{
		IsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();

		ZVelocity = OwnerCharacter->GetVelocity().Z;
	}
	
}
