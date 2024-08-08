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

	/*For Retrive The PoolActor Current UseState(InUse Or NotInUse)*/
	virtual bool CurrentActorUseState() = 0;
	/*For Set The PoolActor UsesState To True*/
	virtual void SetActorInUse() = 0;
	/*For Retrive The Transform Of ArrowComponent(To Set Transform of  Next Tile)*/
	virtual FTransform SpawnArrowTransform()=0;

	virtual void IncreaseSpeed() = 0;
	
	
};
