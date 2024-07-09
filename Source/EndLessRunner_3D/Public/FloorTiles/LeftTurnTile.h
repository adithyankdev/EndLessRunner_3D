// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/PoolActor.h"
#include "LeftTurnTile.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API ALeftTurnTile : public APoolActor
{
	GENERATED_BODY()

public :
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;
	
};
