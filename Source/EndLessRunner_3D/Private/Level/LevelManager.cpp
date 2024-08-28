// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelManager.h"
#include "ObjectPool/ObjectPoolComp.h"
#include "Player/RunningPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


//Interface Function That Set LaneValues On Recived Parameters...
void ALevelManager::LvlManagerLaneValues(int& TotalLanes, float& WidthOfLane)
{
	TotalLanes = NumberOfLane;
	WidthOfLane = LaneWidth;
}

//Interface Function That Check Wheather Random Number Is Repetative For Spawning Obstcles On Floor Tile...
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

	// Add The New Random Number To The Array...
	LatestRandomNumbers.Add(RandomNumber);

	// Ensure The Array Does Not Exceed The Specified Size...
	if (LatestRandomNumbers.Num() > ArraySize)
	{
		LatestRandomNumbers.RemoveAt(0);
	}

	return RandomNumber;
}

//Checking The Count Of NormalTile  , For Spawning The CornerTile...
void ALevelManager::GetSpawnTransform()
{
   ObjectPoolComponent->UseFromPool(); 
}

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it...
	PrimaryActorTick.bCanEverTick = false;
	NumberOfLane = 3;
    LaneWidth = 200.0f;
    LevelSpwaningSpeed= 50.0f;
	StraightTileSpawnCount = 0; 
	ObjectPoolComponent = CreateDefaultSubobject<UObjectPoolComp>(TEXT("ActorComponent"));

}

// Called when the game starts or when spawned...
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	CacheInterface();

	GetWorld()->GetTimerManager().SetTimer(SpeedIncrementTimer, this, &ALevelManager::IncreseSpeed, 10, true);

}

// Called every frame...
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelManager::CacheInterface()
{
	AActor* Player = UGameplayStatics::GetActorOfClass(GetWorld(),ARunningPlayer::StaticClass());
	if (Player)
	{
		PlayerInterface.SetObject(Player);
		if (IGetPlayerInfoInterface* Interface = Cast <IGetPlayerInfoInterface>(Player))
		{
			PlayerInterface.SetInterface(Interface);
		}
	}
}

void ALevelManager::IncreseSpeed()
{
	ObjectPoolComponent->ChangeSpeed();
	
}

