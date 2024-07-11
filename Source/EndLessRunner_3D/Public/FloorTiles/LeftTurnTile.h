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

	virtual void SetDirectionValue(FVector LocationValue) override;

	//Deleting These Function , Casue They Don't Be Useful On Corner Tiles
	void SetComponentTransform() = delete;
	void SpawnObstacle() = delete;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;
	
};
