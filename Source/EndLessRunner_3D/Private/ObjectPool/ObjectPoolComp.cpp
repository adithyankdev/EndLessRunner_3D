// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/ObjectPoolComp.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/RunningPlayer.h"



// Sets default values for this component's properties
UObjectPoolComp::UObjectPoolComp()
{
	PrimaryComponentTick.bCanEverTick = false;
	QuickSpwanCount = 10;
	PoolSize = 20;
	       
}


void UObjectPoolComp::BeginPlay()
{
	Super::BeginPlay();
	InitializePool();

}

//Function For Spawnning All the Actors To the World and Arrange Some Object For The Game Start (Long Road) ... 

void UObjectPoolComp::InitializePool()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	int SpawnedCount = 0;
	
	for (int itr = 0; itr < PoolSize; itr++)
	{
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(PoolActorClass,SpawnTransform , SpawnParams);

		if (SpawnActor)
		{
			PoolActorArray.AddUnique(SpawnActor);
			SpawnedCount++;
			if (SpawnedCount <= QuickSpwanCount)
			{
				SpawnTransform = QuickActorTransform(SpawnActor);
				LatestRearFloor = SpawnActor;
			
			}
			else
			{
				FTimerHandle NextBatchTimer;
				GetWorld()->GetTimerManager().SetTimer(NextBatchTimer, [this, itr](){BatchingSpawn(itr);}, 2.0f, false);
				break;
			}

		}

	}
	SetInterfaces();
}

//Function That Set The Actor To Use And Set Its World Transform ...

AActor* UObjectPoolComp::UseFromPool()
{
	if(AActor* ActorToUse = GetNotInUseActor())
	{
		if (IGetActorPoolMembers* ActorInterface = Cast<IGetActorPoolMembers>(LatestRearFloor))
		{
			FTransform GetTransform = ActorInterface->SpawnArrowTransform();
			ActorToUse->SetActorTransform(GetTransform);
		}
		if (ActorToUse->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
		{
			IGetActorPoolMembers* Interface = Cast<IGetActorPoolMembers>(ActorToUse);
			Interface->SetActorInUse();
			LatestRearFloor = ActorToUse;
		
			//Only happen when the turnhappen 
			if (Turnhappend)
			{
				if (TurnIndex == 0)
				{
					Interface->SetDirectionValue(FVector(0, 1, 0));
				}
				else
				{
					Interface->SetDirectionValue(FVector(0, -1, 0));
				}
			}
			return ActorToUse;
		}
	}
	return nullptr;
}




// Function Return The First Actor That Is Not Currently Using ...

AActor* UObjectPoolComp::GetNotInUseActor()
{
	for (AActor* Act :PoolActorArray)
	{	
	
		if (!Act->IsA(TurnTileClass[0]->StaticClass()) && Act->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
		{
			if (!Cast<IGetActorPoolMembers>(Act)->CurrentActorUseState())
			{
				return Act;
			}
		}
		
	}
	return nullptr;
}

//Function Return The World Transform For the Tile To Spawn 

FTransform UObjectPoolComp::QuickActorTransform(AActor* SpawnActor)
{
	if (SpawnActor->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
	{
		if (IGetActorPoolMembers* ActorInterface = Cast<IGetActorPoolMembers>(SpawnActor))
		{
			ActorInterface->SetActorInUse();
			FTransform GetTransform = ActorInterface->SpawnArrowTransform();
			return GetTransform;
		}
	}
	return FTransform::Identity;
}


//Function That Just Spawn The Pool Actors To The World (Batching Method) ...
void UObjectPoolComp::BatchingSpawn(int index)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int itr = index+1; itr < PoolSize; itr++)
	{
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(PoolActorClass,FTransform::Identity, SpawnParams);
		PoolActorArray.AddUnique(SpawnActor);
	}
	SpawnTurnTile();
}

//Function That Spawn Tile Actor Into The World And Adding It Into The Array ...
void UObjectPoolComp::SpawnTurnTile()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int itr = 0; itr <=1; itr++)
	{
		AActor* SpawnTileActor = GetWorld()->SpawnActor<AActor>(TurnTileClass[itr], FTransform::Identity, SpawnParams);
		TurnTileArray.AddUnique(SpawnTileActor);		
	}
}

//Function  That Use Trun Tile From Pool
void UObjectPoolComp::UseTurnTileFromPool()
{
	int RandomInt = FMath::RandRange(0, 1);
	TurnIndex = RandomInt;

	AActor* ActorToUse = TurnTileArray[RandomInt];
		{
			if (IGetActorPoolMembers* ActorInterface = Cast<IGetActorPoolMembers>(LatestRearFloor))
			{
				FTransform GetTransform = ActorInterface->SpawnArrowTransform();
				ActorToUse->SetActorTransform(GetTransform);
				ActorInterface->SetDirectionValue(FVector(-1, 0, 0));
			}
			if (ActorToUse->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
			{
				Cast<IGetActorPoolMembers>(ActorToUse)->SetActorInUse();  
			}
			LatestRearFloor = ActorToUse;
			LatestTurnFloor = ActorToUse;
			Turnhappend = true;
	}
}//Setting Direction Of Tiles After Turning
void UObjectPoolComp::SetActorDirection(FVector Direction)
{
	if (IGetActorPoolMembers* TurnInterface = Cast <IGetActorPoolMembers>(LatestTurnFloor))
	{
		if (LatestTurnFloor == TurnTileArray[0])
		{
			//Constant Direction...
			TurnInterface->SetDirectionValue(FVector(0, -1, 0));
		}
		else
		{
			//Constant Direction...
			TurnInterface->SetDirectionValue(FVector(0, 1, 0));	
		}
		GetWorld()->GetTimerManager().SetTimer(timer, this, &UObjectPoolComp::SetTurnDefaultDirection, 2);
		
	}
	for (AActor* PActor : PoolActorArray)
	{
		if (IGetActorPoolMembers* Interface = Cast<IGetActorPoolMembers>(PActor))
		{
			Interface->SetDirectionValue(Direction);
		}
	}
	
}

//Caching The Interface....
void UObjectPoolComp::SetInterfaces()
{
	//AActor* LvlActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass());
	LvlInterface.SetObject(GetOwner());
	LvlInterface.SetInterface(Cast <IGetLvlManagerMembers>(GetOwner()));	
}

//Setting The Movement Value To Default (-x) of The Turn Tile ....
void UObjectPoolComp::SetTurnDefaultDirection()
{
	if (IGetActorPoolMembers* TurnInterface = Cast <IGetActorPoolMembers>(LatestTurnFloor))
	{
				TurnInterface->SetDirectionValue(FVector(-1,0,0));
	}
}


