// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/PoolActor.h"
#include "Interface/TurnTileInterface.h"
#include "LeftTurnTile.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_3D_API ALeftTurnTile : public APoolActor , public ITurnTileInterface
{
	GENERATED_BODY()

public :

	UPROPERTY()
	TMap<int, FVector>LaneLocations;

	TMap<int, FVector>GetTileLineLocations() override;

	//Deleting These Function , Casue They Don't Be Useful On Corner Tiles
	void SetComponentTransform() override;
	void SpawnObstacle() override; 
	int GetRandomTransform() override;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;

	
	
};
