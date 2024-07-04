// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ObjectPool/ObjectPoolComp.h"


//Interface Function That Check Wheather Random Number Is Repetative For Spawning Obstcles On Floor Tile ; 
int ALevelManager::GetRandomInteger(int RandomNumber)
{
	if (LatestRandomNumbers.Num() == Arraysize)
	{
		if (LatestRandomNumbers[0] == LatestRandomNumbers[1] && LatestRandomNumbers[1] == LatestRandomNumbers[2])
		{
			if (LatestRandomNumbers[0] == RandomNumber)
			{
				while (RandomNumber == LatestRandomNumbers[0])
				{
					 RandomNumber = FMath::RandRange(0,LatestRandomNumbers.Num() - 1);
				}
			}
		}
		LatestRandomNumbers.Empty();
		LatestRandomNumbers.Add(RandomNumber);
	}
	else
	{
		LatestRandomNumbers.Add(RandomNumber);
	}
	return RandomNumber ;
}

void ALevelManager::GetSpawnTransform()
{
	ObjectPoolComponent->UseFromPool();
}

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumberOfLane = 3;
    LaneWidth = 100.0f;
    LevelSpwaningSpeed= 50.0f;

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

