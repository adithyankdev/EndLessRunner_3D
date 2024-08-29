// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPool/ObjectPoolComp.h"
#include "Interface/GetLvlManagerMembers.h"
#include "Interface/GetPlayerInfoInterface.h"
#include "LevelManager.generated.h"

class UObjectPoolComp;
class APoolActor;

UCLASS()
class ENDLESSRUNNER_3D_API ALevelManager : public AActor , public IGetLvlManagerMembers
{
	GENERATED_BODY()
	
public:
	  
	/*Interface Function For Retriving And Setting The LvlManager  Class*/
	 void  LvlManagerLaneValues(int& TotalLanes, float& WidthOfLane) override;
	 int  GetRandomInteger(int RandomNumber) override;
	 void GetSpawnTransform() override; 
	 void CallDeadWidget() override;

	ALevelManager();
	 
protected:

	/*ActorComponent That Hold The ObjectPool Logic*/
	UPROPERTY(VisibleDefaultsOnly)
	UObjectPoolComp* ObjectPoolComponent;

	//Array To Store RandomInteger From Obstacle(1) Arrays
	TArray<int>LatestRandomNumbers{3};

	/*Variable That Set TheRandomInteger Array Size*/
	const int ArraySize = 2;

	/*Begin Play Function*/
	virtual void BeginPlay() override;

public:	
	
	/*Varible That Give Permission For PlayerTurn , Storing From The ActorOverlapComponent*/
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	bool PlayerTurn;

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


	/*Timer For Calling Speed Function*/
	FTimerHandle SpeedIncrementTimer;

	/*For Increasing The Speed Of Pooled Actor Over Time*/
	void IncreseSpeed();

	UPROPERTY(EditDefaultsOnly , Category = "LevelValues")
	TSubclassOf<class UGameEndWidget> EndGameWidgetClass;


};
