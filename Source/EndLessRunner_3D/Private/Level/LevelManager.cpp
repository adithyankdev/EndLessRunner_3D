// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ObjectPool/ObjectPoolComp.h"

void ALevelManager::LvlManagerLaneValues(int& TotalLanes, float& WidthOfLane)
{
	TotalLanes = NumberOfLane;
	WidthOfLane = LaneWidth;
}

//Interface Function That Check Wheather Random Number Is Repetative For Spawning Obstcles On Floor Tile ; 
int ALevelManager::GetRandomInteger(int RandomNumber)
{
	if (LatestRandomNumbers.Num() >= ArraySize)
	{
		while (LatestRandomNumbers[LatestRandomNumbers.Num() - 1] == LatestRandomNumbers[LatestRandomNumbers.Num() - 2] &&
			LatestRandomNumbers[LatestRandomNumbers.Num() - 1] == RandomNumber)
		{
			RandomNumber = FMath::RandRange(0, ArraySize - 1);
		}
	}

	// Add the new random number to the array
	LatestRandomNumbers.Add(RandomNumber);

	// Ensure the array does not exceed the specified size
	if (LatestRandomNumbers.Num() > ArraySize)
	{
		LatestRandomNumbers.RemoveAt(0);
	}

	return RandomNumber;
}

void ALevelManager::GetSpawnTransform()
{
	if (StraightTileSpawnCount <= 10)
	{
		ObjectPoolComponent->UseFromPool(); 
		StraightTileSpawnCount++;
	}
	else
	{
		ObjectPoolComponent->UseTurnTileFromPool();
		StraightTileSpawnCount = 0;
	} 
}

//Interface Function That Set Wheather The Player Have Turn Or Not ...
void ALevelManager::SetCanPlayerTurn(bool Value)
{
	PlayerTurn = Value;
}

//Interface Get Function On PlayerMove ...
bool ALevelManager::GetCanPlayerTurn()
{
	return PlayerTurn;
}

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumberOfLane = 3;
    LaneWidth = 200.0f;
    LevelSpwaningSpeed= 50.0f;
	StraightTileSpawnCount = 0; 
	ObjectPoolComponent = CreateDefaultSubobject<UObjectPoolComp>(TEXT("ActorComponent"));

}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

