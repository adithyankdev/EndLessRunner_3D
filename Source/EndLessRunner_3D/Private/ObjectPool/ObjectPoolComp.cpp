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
	FTransform SpawnTransform;
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
			}
			else
			{
				SpawnTransform = FTransform::Identity;
			}


		}

	}
}

//Function That Set The Actor To Use And Set Its World Transform ...

AActor* UObjectPoolComp::UseFromPool(FTransform UseTransform)
{
	if (AActor* ActorToUse = GetNotInUseActor())
	{

	//	ActorToUse->SetActorLocation(UseLocation);
		ActorToUse->SetActorTransform(UseTransform);

		if (ActorToUse->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
		{
			Cast<IGetActorPoolMembers>(ActorToUse)->SetActorInUse();
			return ActorToUse;
			FString Debug = TEXT("Actor Is Good");
			UKismetSystemLibrary::PrintString(GetWorld(), Debug, true, true, FLinearColor::Yellow, 5);
		}
	}
	else
	{
		FString Debug = TEXT("UseFromPool Function Recived NUll Valid Pointer");
		UKismetSystemLibrary::PrintString(GetWorld(), Debug, true, true, FLinearColor::Red, 5);
	}
	return nullptr;
}


// Function Return The First Actor That Is Not Currently Using ...

AActor* UObjectPoolComp::GetNotInUseActor()
{
	for (AActor* Act :PoolActorArray)
	{
		if (Act->GetClass()->ImplementsInterface(UGetActorPoolMembers::StaticClass()))
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

