// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetActorPoolMembers.generated.h"


class UArrowComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGetActorPoolMembers : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENDLESSRUNNER_3D_API IGetActorPoolMembers
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool CurrentActorUseState() = 0;
	virtual void SetActorInUse() = 0;
	virtual FTransform SpawnArrowTransform()=0;
	virtual void SetDirectionValue(FVector LocationValue) =  0;
	virtual UArrowComponent* GetDirectionalArrow() = 0;
	virtual FVector GetCurrentDirection() = 0;
};
