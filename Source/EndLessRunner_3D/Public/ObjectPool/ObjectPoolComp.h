// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool/PoolActor.h"
#include "ObjectPoolComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER_3D_API UObjectPoolComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ObjectPool Base")
	TSubclassOf<AActor>PoolActorClass;

	UPROPERTY()
	TArray<AActor*>PoolActorArray;

	UPROPERTY()
	int PoolSize;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SingleTileSize;

	UPROPERTY()
	AActor* LatestRearFloor;

	UPROPERTY()
	int QuickSpwanCount;

	UObjectPoolComp();

	FTransform SpawnTransform;

	UFUNCTION()
	AActor* UseFromPool();

protected:
	
	virtual void BeginPlay() override;

	FTimerHandle SpawnBatchingTimer;

	UFUNCTION()
	void InitializePool();

	UFUNCTION()
	AActor* GetNotInUseActor();

	//HelperFunctions
	 
	 UFUNCTION()
	 FTransform QuickActorTransform(AActor* SpawnActor);

	 UFUNCTION()
	 void BatchingSpawn(int inde);

	 //Turn Tile Spawning Methods And Variables

	 UPROPERTY(BlueprintReadWrite , EditDefaultsOnly , Category = "ObjectPool Base")
	 TArray<TSubclassOf<AActor>>TurnTileClass;
	 UPROPERTY()
	 TArray<AActor*>TurnTileArray;

	 UFUNCTION()
	 void SpawnTurnTile();

public:
	UFUNCTION()
	void UseTurnTileFromPool();
	

};
