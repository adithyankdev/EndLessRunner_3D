// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/ObjectPoolComp.h"
#include "Kismet/KismetSystemLibrary.h"


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
}

//Function That Set The Actor To Use And Set Its World Transform ...

AActor* UObjectPoolComp::UseFromPool()
{

	if(AActor* ActorToUse = GetNotInUseActor())
	{
	  //SpawnTransform = QuickActorTransform(ActorToUse);		//

		if (IGetActorPoolMembers* ActorInterface = Cast<IGetActorPoolMembers>(LatestRearFloor))
		{
			FTransform GetTransform = ActorInterface->ArrowTransform();
			ActorToUse->SetActorTransform(GetTransform);
			//ActorInterface->SetActorInUse();
		}
		if (ActorToUse->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
		{
			IGetActorPoolMembers* Interface = Cast<IGetActorPoolMembers>(ActorToUse);
			Interface->SetActorInUse();
		//	SpawnTransform = QuickActorTransform(ActorToUse);
			LatestRearFloor = ActorToUse;
			if (Turnhappend)Interface->SetDirectionValue(ActorToUse->GetActorForwardVector());
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
			FTransform GetTransform = ActorInterface->ArrowTransform();
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
		//PoolActorArray.AddUnique(SpawnTileActor);
		TurnTileArray.AddUnique(SpawnTileActor);		
	}
}

//Function  That Use Trun Tile From Pool
void UObjectPoolComp::UseTurnTileFromPool()
{
	int RandomInt = FMath::RandRange(0, 1);


	AActor* ActorToUse = TurnTileArray[RandomInt];
		{
			if (IGetActorPoolMembers* ActorInterface = Cast<IGetActorPoolMembers>(LatestRearFloor))
			{
				FTransform GetTransform = ActorInterface->ArrowTransform();
				ActorToUse->SetActorTransform(GetTransform);
			}
			if (ActorToUse->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
			{
				Cast<IGetActorPoolMembers>(ActorToUse)->SetActorInUse();
			}
			LatestRearFloor = ActorToUse;
			Turnhappend = true;
	}
}
