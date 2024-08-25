// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/FinaliseMeshOnCharacter/FinaliseCharacter.h"
#include "GameFramework/Character.h"

#include "Animations/DeerAnimInstance.h"

FinaliseCharacter::FinaliseCharacter()
{
	DeerBPAnimInstance = StaticLoadClass(UDeerAnimInstance::StaticClass(), nullptr, TEXT("/Game/Player/Deer/ABP_DeerAnimInstance.ABP_DeerAnimInstance"));
	
	if (DeerBPAnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello World"));
	}
	else
	{
		UE_LOG(LogTemp, Error , TEXT("Hello World"));
	}

	/*PigMeshAnimation = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Player/Pig/ABP_PigAnimInstance.ABP_PigAnimInstance"));
	FoxMeshAnimation = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Player/Fox/ABP_FoxAnimInstance.ABP_FoxAnimInstance"));*/

}

FinaliseCharacter::~FinaliseCharacter()
{

}

void FinaliseCharacter::SetUpCharacterMesh(ACharacter* PlayerCharacter,USkeletalMesh* SkeletalMesh, int AnimationIndex)
{
	PlayerCharacter->GetMesh()->SetSkeletalMesh(SkeletalMesh);

	switch (AnimationIndex)
	{
	case 0: PlayerCharacter->GetMesh()->SetAnimInstanceClass(DeerBPAnimInstance);
		    PlayerCharacter->GetMesh()->SetRelativeScale3D(FVector(0.7, 0.7, 0.7));
		break;
	//case 1:PlayerCharacter->GetMesh()->PlayAnimation(PigMeshAnimation, true);
	//	PlayerCharacter->GetMesh()->SetRelativeScale3D(FVector(0.8, 0.8, 0.8));
	//	break;
	//case 2:PlayerCharacter->GetMesh()->PlayAnimation(FoxMeshAnimation, true);
	//	PlayerCharacter->GetMesh()->SetRelativeScale3D(FVector(1.7, 1.7, 1.7));
	}

	UE_LOG(LogTemp, Warning,TEXT("Animation Index For The Mesh  : : :  %d"), AnimationIndex);
}
