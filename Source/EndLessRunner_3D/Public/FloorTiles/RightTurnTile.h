// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPool/PoolActor.h"
#include "RightTurnTile.generated.h"

UCLASS()
class ENDLESSRUNNER_3D_API ARightTurnTile : public APoolActor
{
	GENERATED_BODY()
	
public:

	ARightTurnTile();

	void BeginPlay() override;

	//Deleting These Function , Casue They Don't Be Useful On Corner Tiles
	void SetComponentTransform() = delete;
	void SpawnObstacle() = delete;

 /*Overriding The BeginOverlap For Adding Additional Functionality*/
   void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	   const FHitResult& SweepResult) override;

};
