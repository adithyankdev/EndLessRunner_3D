// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/PoolActor.h"
#include "Kismet/KismetSystemLibrary.h"


//Retrive The Current State Of Actor (On Use Or Not) ...
bool APoolActor::CurrentActorUseState()
{
	return CurrentlyUse;
   
}

//Setting The Actor True When it Used ...
void APoolActor::SetActorInUse()
{
	SetInUse(true);
}

//Getting The ArrowComponent  For Spawning The Next Tile ...
FTransform APoolActor::ArrowTransform()
{
	return Arrowcomponent->GetComponentTransform();
}

// Sets default values
APoolActor::APoolActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Scene"));
	SetRootComponent(SceneComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnTileBox"));
	BoxCollision->SetupAttachment(RootComponent);

	Arrowcomponent = CreateDefaultSubobject<UArrowComponent>(TEXT("TileSpawnPoint"));
	Arrowcomponent->SetupAttachment(RootComponent);
    
	ObstacleArrowcomp_One = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePointOne"));
	ObstacleArrowcomp_One->SetupAttachment(RootComponent);

	ObstacleArrowcom_Two = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePointTwo"));
	ObstacleArrowcom_Two->SetupAttachment(RootComponent);

	ObstacleArrowcomp_Three = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePointThree"));
	ObstacleArrowcomp_Three->SetupAttachment(RootComponent);
}


void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	SetInUse(false);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APoolActor::OnPlayerBeginOverlap);
}

//Function That Set Property When The Actor Is On Use ..
void APoolActor::SetInUse(bool InUse)
{
	CurrentlyUse = InUse;
	SetActorTickEnabled(InUse);
	SetActorEnableCollision(InUse);
	SetActorHiddenInGame(!InUse);
	
}
//Function That Always Make The Actor Not Use  ...
void APoolActor::SetNotUse()
{
	SetInUse(false);
}

void APoolActor::SetComponentTransform()
{
	//ObstacleTransform.Add(ObstacleArrowcomp_One->GetComponentTransform());
	//ObstacleTransform.Add(ObstacleArrowcom_Two->GetComponentTransform());
	//ObstacleTransform.Add(ObstacleArrowcomp_Three->GetComponentTransform());
	ObstacleTras.Add(ObstacleArrowcomp_One);
	ObstacleTras.Add(ObstacleArrowcom_Two);
	ObstacleTras.Add(ObstacleArrowcomp_Three);
}

//Need To Be On The Level Manager Class ...
int APoolActor::GetRandomTransform()
{
	int RandomInt = FMath::RandRange(0, ObstacleTransform.Num() - 1);
	if (LatestRandomNumbers.Num()==3)
	{
		if (LatestRandomNumbers[0] == LatestRandomNumbers[1] && LatestRandomNumbers[1] == LatestRandomNumbers[2])
		{
			if (LatestRandomNumbers[0] == RandomInt)
			{
				while (RandomInt == LatestRandomNumbers[0])
				{
					RandomInt = FMath::RandRange(0, ObstacleTransform.Num() - 1);
				}
			}	
		}
			LatestRandomNumbers.Empty();
			LatestRandomNumbers.Add(RandomInt);
	}
	else
	{
		LatestRandomNumbers.Add(RandomInt);
	}
	
	return RandomInt;
}

void APoolActor::SpawnObstacle()
{
	int value = GetRandomTransform();

	if(UChildActorComponent* ChildComponent = NewObject<UChildActorComponent>(this))
	{
		ChildComponent->SetChildActorClass(ObstacleClasses);
		ChildComponent->RegisterComponent();
		ChildComponent->AttachToComponent(ObstacleTras[value], FAttachmentTransformRules::KeepRelativeTransform);
	}
}

// Called every frame
void APoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Begin Player For Making The Tile NotUse

void APoolActor::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

