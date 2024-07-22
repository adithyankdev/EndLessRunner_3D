// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetPlayerInfoInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGetPlayerInfoInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENDLESSRUNNER_3D_API IGetPlayerInfoInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetPlaneConstraints() = 0;
	virtual void SetLocation(FVector NewLocation) = 0;
};
