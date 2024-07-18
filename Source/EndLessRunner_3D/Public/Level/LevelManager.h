// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPool/ObjectPoolComp.h"
#include "Interface/GetLvlManagerMembers.h"
#include "LevelManager.generated.h"

class UObjectPoolComp;

UCLASS()
class ENDLESSRUNNER_3D_API ALevelManager : public AActor , public IGetLvlManagerMembers
{
	GENERATED_BODY()
	
public:
	  
	/*Interface Function For Retriving And Setting The LvlManager  Class*/
	virtual void  LvlManagerLaneValues(int& TotalLanes, float& WidthOfLane) override;
	virtual int  GetRandomInteger(int RandomNumber) override;
	virtual void GetSpawnTransform() override; 
	virtual void SetCanPlayerTurn(bool Value) override;
	virtual bool GetCanPlayerTurn() override;
	void SetActorNewDirection(FVector Direction) override;
	void SetQuickUseOnTurn() override; 

	ALevelManager();
	 
protected:

	/*ActorComponent That Hold The ObjectPool Logic*/
	UPROPERTY(VisibleDefaultsOnly)
	UObjectPoolComp* ObjectPoolComponent;

	//Array To Store RandomInteger From Obstacle(1) Arrays
	TArray<int>LatestRandomNumbers{3};

	/*Variable That Set TheRandomInteger Array Size*/
	const int ArraySize = 2;

	/*Varible That Give Permission For PlayerTurn , Storing From The ActorOverlapComponent*/
	UPROPERTY()
	bool PlayerTurn;

	/*Begin Play Function*/
	virtual void BeginPlay() override;

public:	
	
	/*Tick Function*/
	virtual void Tick(float DeltaTime) override;

	/*Variable That Limit The Tile Spawn Of  Normal Tile */
	UPROPERTY()
	int StraightTileSpawnCount;

	/*Varibales That Set The Lane Info*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	int NumberOfLane;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LaneWidth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LevelSpwaningSpeed;


};
