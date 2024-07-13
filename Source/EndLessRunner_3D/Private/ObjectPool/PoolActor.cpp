// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/PoolActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Level/LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "Player/RunningPlayer.h"




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
FTransform APoolActor::SpawnArrowTransform()
{
	return Arrowcomponent->GetComponentTransform();
}
 
void APoolActor::SetDirectionValue(FVector LocationValue)
{
	CurrentDirection = LocationValue; 
}

UArrowComponent* APoolActor::GetDirectionalArrow()
{
	return DirectionalArrow;
}

FVector APoolActor::GetCurrentDirection()
{
	return CurrentDirection;
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

	DirectionalArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	DirectionalArrow->SetupAttachment(RootComponent);


	 ChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ObstacleActor"));
	LvlManagerInterface = nullptr ;
	CurrentDirection = FVector::ZeroVector;
}


void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	SetInUse(false);
	CurrentDirection = FVector(-1,0,0);  //Setting Initial Movement Direction ...
	AActor* LevelManager = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass());
	if (LevelManager && LevelManager->GetClass()->ImplementsInterface(UGetLvlManagerMembers::StaticClass()))
	{
		LvlManagerInterface.SetObject(LevelManager);                                         //Caching The Interface For Resusing it ...
		LvlManagerInterface.SetInterface(Cast<IGetLvlManagerMembers>(LevelManager));
	}
	SetComponentTransform();                                                                //Setting Up Obstacle Transfrom...
	SpawnObstacle();                                                                        //Spawning Child ActorComponent...
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APoolActor::OnBeginOverlap);
}

//Tick Function
void APoolActor::Tick(float DeltaTime)
{   
	FVector Speed = ((CurrentDirection)*500.0f )*DeltaTime;
	
	AddActorLocalOffset(Speed);
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

//Function That Add Current To Array For (Spawnning Child)
void APoolActor::SetComponentTransform()
{
	ObstacleTras.Add(ObstacleArrowcomp_One);
	ObstacleTras.Add(ObstacleArrowcom_Two);
	ObstacleTras.Add(ObstacleArrowcomp_Three);
}

//Call The Interface On Lvl Manager --(Checking For Wheather The NumberIs Repeatative on Three Times)-- And Return Integer ...
int APoolActor::GetRandomTransform()
{
	int RandomInt = FMath::RandRange(0, ObstacleTras.Num() - 1);
	RandomInt = LvlManagerInterface->GetRandomInteger(RandomInt);
	
	return RandomInt;

}

//Function That Set The ChildActorClass and Attach To ArrowComponent ...
void APoolActor::SpawnObstacle()
{
	int Index = GetRandomTransform();

	if (ChildComponent )
	{
		ChildComponent->SetChildActorClass(ObstacleClasses);
		ChildComponent->RegisterComponent();
		ChildComponent->AttachToComponent(ObstacleTras[Index], FAttachmentTransformRules::KeepRelativeTransform);
		
	}
}


//BeginOverlap Functin For Using The Next Tile On The Front And Not Using the Last Tile ...
void APoolActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ARunningPlayer::StaticClass()))
	{
			LvlManagerInterface->GetSpawnTransform();
		if (GetWorld()->GetTimerManager().IsTimerActive(NotUseActorTimer))
		{
		   GetWorld()->GetTimerManager().ClearTimer(NotUseActorTimer);
		}
		GetWorld()->GetTimerManager().SetTimer(NotUseActorTimer, this, &APoolActor::StopUsingTheActor, 2.0f, false);				
			
		}
	
}

//Function That Set The Actor Not To Use ...
void APoolActor::StopUsingTheActor()
{
	SetNotUse();
}


