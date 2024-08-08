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
	TotalSpawnCount = 0;
	
}


void UObjectPoolComp::BeginPlay()
{
	Super::BeginPlay();
	SpawnTransform.SetLocation(FVector(2500.0f,0.0f,0.0f));
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

	if (AActor* ActorToUse = GetNotInUseActor())
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
	
		if ( Act->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
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
	
}

//Caching The Interface....
void UObjectPoolComp::SetInterfaces()
{
	//AActor* LvlActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass());
	LvlInterface.SetObject(GetOwner());
	LvlInterface.SetInterface(Cast <IGetLvlManagerMembers>(GetOwner()));	
}



