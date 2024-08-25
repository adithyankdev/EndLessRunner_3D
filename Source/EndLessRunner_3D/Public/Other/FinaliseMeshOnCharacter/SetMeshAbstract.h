// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class USkeletalMesh;
class ACharacter;

/**
 * 
 */
class ENDLESSRUNNER_3D_API SetMeshAbstract
{
public:
	SetMeshAbstract();
	virtual ~SetMeshAbstract();

	virtual void SetUpCharacterMesh(ACharacter* PlayerCharacter,USkeletalMesh* SkeletalMesh, int AnimationIndex) = 0;

};
