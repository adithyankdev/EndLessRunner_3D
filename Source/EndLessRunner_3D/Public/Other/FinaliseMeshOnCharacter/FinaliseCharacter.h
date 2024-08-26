// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Other/FinaliseMeshOnCharacter/SetMeshAbstract.h"

/**
 * 
 */
class ENDLESSRUNNER_3D_API FinaliseCharacter : public SetMeshAbstract
{
public:
	FinaliseCharacter();
	~FinaliseCharacter();

	void SetUpCharacterMesh(ACharacter* PlayerCharacter,USkeletalMesh* SkeletalMesh, int AnimationIndex) override;

private:

	UClass* DeerBPAnimInstance;
	UClass* PigBPAnimInstance;
	UClass* FoxBPAnimInstance;

};
