// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool/PoolActor.h"
#include "Interface/GetPlayerInfoInterface.h"
#include "ObjectPoolComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER_3D_API UObjectPoolComp : public UActorComponent
{
	GENERATED_BODY()

public:	

	UObjectPoolComp();

	/*Storing The Class Of Actor To Pool*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ObjectPool Base")
	TSubclassOf<AActor>PoolActorClass;

	/*Total Number Of The Pool Actor To Create*/
	UPROPERTY()
	TArray<AActor*>PoolActorArray;
	/*Size Of The Pool*/
	UPROPERTY()
	int PoolSize;
	
	/*Referance On The Latest Used Straing Tile*/
	UPROPERTY()
	AActor* LatestRearFloor;

	/*Total Count Of Qucik Spawn On First Game Begin*/
	UPROPERTY()
	int QuickSpwanCount;

	/*Store The Transform Of Latest Used Tile Arrowcomponent For Setting The Location Of Upcoming Tile*/
	FTransform SpawnTransform;

	/*Function That Resuse Actors From Available Pool*/
	UFUNCTION()
	AActor* UseFromPool();

protected:
	
	virtual void BeginPlay() override;

	//*Value Responsibe For Calling The CacheInterface Only At Once*/
	bool CanCache;

	///*Function That Assgin Value In TScriptInterface*/
	//void CacheInterface

	/*Timer For Calling The Batch Function For Spawwning Tiles*/
	FTimerHandle SpawnBatchingTimer;

	/*Function That Create Tiles*/
	UFUNCTION()
	void InitializePool();
	/*Function That Retrive The First NotInUse Actor For Using It*/
	UFUNCTION()
	AActor* GetNotInUseActor();

	//HelperFunctions.....
	 
	/*Retriving The Transform The Latest Used Tile*/
	 UFUNCTION()
	 FTransform QuickActorTransform(AActor* SpawnActor);

	 /*Function That Create Remaining Tiles*/
	 UFUNCTION()
	 void BatchingSpawn(int inde);

public:

	/*Storing Interfaces For Caching*/
	UPROPERTY()
	TScriptInterface<IGetLvlManagerMembers>LvlInterface;

	/*For Caching The Actor Interface*/
	TScriptInterface<IGetActorPoolMembers>PoolActorInterface;

    /*Function For Storing Interface Referance*/
	void SetInterfaces(AActor* PoolActor);

	/*Timer For Switching The TurnTile Direction Back To Normal*/
	FTimerHandle timer;
	
	UPROPERTY()
	bool QuickUse;
	UPROPERTY()
	int TotalSpawnCount;

	float ActorXScaleSize;

	void ChangeActorSpeed();

};
