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
	 
	virtual void  LvlManagerLaneValues(int& TotalLanes, float& WidthOfLane) override;
	virtual int  GetRandomInteger(int RandomNumber) override;
	virtual void GetSpawnTransform() override; 
	virtual void SetCanPlayerTurn(bool Value) override;
	virtual bool GetCanPlayerTurn() override;

	ALevelManager();

	

protected:

	UPROPERTY(VisibleDefaultsOnly)
	UObjectPoolComp* ObjectPoolComponent;

	//Array To Store RandomInteger From Obstacle(1) Arrays
	TArray<int>LatestRandomNumbers{3};
	const int ArraySize = 2;

	virtual void BeginPlay() override;

	UPROPERTY()
	bool PlayerTurn;

public:	
	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	int StraightTileSpawnCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	int NumberOfLane;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LaneWidth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LevelSpwaningSpeed;


};
