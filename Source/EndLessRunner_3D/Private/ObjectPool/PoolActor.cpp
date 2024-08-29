// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/PoolActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Level/LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "Player/RunningPlayer.h"
#include "Kismet/KismetMathLibrary.h"


float APoolActor::Speed = 0.0f;
float APoolActor::ActorNotUseTime = 3.0f;
bool APoolActor::CanActorTick = true;

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

void APoolActor::StopMoving()
{
	GetWorld()->GetTimerManager().SetTimer(ReduceSpeedTimer, this, &APoolActor::ReduceSpeed, 0.5,true);
	
}

void APoolActor::ReduceSpeed()
{
	if (Speed > 50)
	{
		Speed = 0;
		CanActorTick = false;
		GetWorld()->GetTimerManager().ClearTimer(ReduceSpeedTimer);
	}
	Speed -= 50;
}


void APoolActor::IncreaseSpeed()
{
	Speed += 100.0f;
	if (ActorNotUseTime > 0.5)ActorNotUseTime -= 0.1;
}


// Sets default values
APoolActor::APoolActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Scene"));
	SetRootComponent(SceneComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnTileBox"));
	BoxCollision->SetupAttachment(RootComponent);

	GameOverCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EndGame"));
	GameOverCollision->SetupAttachment(RootComponent);

	Arrowcomponent = CreateDefaultSubobject<UArrowComponent>(TEXT("TileSpawnPoint"));
	Arrowcomponent->SetupAttachment(RootComponent);

	ObstacleArrowcomp_One = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePointOne"));
	ObstacleArrowcomp_One->SetupAttachment(RootComponent);

	ObstacleArrowcomp_Two = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePointTwo"));
	ObstacleArrowcomp_Two->SetupAttachment(RootComponent);

	ObstacleArrowcomp_Three = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePointThree"));
	ObstacleArrowcomp_Three->SetupAttachment(RootComponent);

	DirectionalArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	DirectionalArrow->SetupAttachment(RootComponent);


	RightSideArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RightArrow"));
	RightSideArrow->SetupAttachment(RootComponent);
	LeftSideArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrow"));
    LeftSideArrow->SetupAttachment(RootComponent);

    ChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ObstacleActor"));

	RightSideFloorComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("RightSideFloor"));
	LeftSideFloorComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("LeftSideFloor"));

	LvlManagerInterface = nullptr ;
	CurrentDirection = FVector::ZeroVector;

}

APoolActor::~APoolActor()
{

}


void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	Speed = 800.0f;
	CanActorTick = true;
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
	SetupSideFloorChild();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APoolActor::OnBeginOverlap);

	GameOverCollision->OnComponentBeginOverlap.AddDynamic(this, &APoolActor::OnEndGameOverlap);
}

//Tick Function
void APoolActor::Tick(float DeltaTime)
{   
	AddActorLocalOffset(((CurrentDirection)*Speed)* DeltaTime);
	if (CanActorTick == false)SetActorTickEnabled(CanActorTick);
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

//Adding All Spawnable Points  Transform To Array For (Spawnning Child)
void APoolActor::SetComponentTransform()
{
	ObstacleTras.Add(ObstacleArrowcomp_One);
	ObstacleTras.Add(ObstacleArrowcomp_Two);
	ObstacleTras.Add(ObstacleArrowcomp_Three);
}

//Call The Interface On Lvl Manager --(Checking For Wheather The NumberIs Repeatative on Three Times)-- And Return Integer ...
int APoolActor::GetRandomTransform()
{
	int RandomInt = FMath::RandRange(0, ObstacleTras.Num() - 1);
	RandomInt = LvlManagerInterface->GetRandomInteger(RandomInt);        //LvlManger Check Wheather This Random Number Is Repetative For 2 Times..
	
	return RandomInt;

}

//Function That Set The ChildActorClass and Attach To ArrowComponent ...
void APoolActor::SpawnObstacle()
{
	int Index = GetRandomTransform();

	//Setting The ChildComponent And Its Transform...
	if (ChildComponent )
	{
		ChildComponent->SetChildActorClass(ObstacleClasses);
		ChildComponent->RegisterComponent();
		ChildComponent->AttachToComponent(ObstacleTras[Index], FAttachmentTransformRules::KeepRelativeTransform);

	}
}

void APoolActor::SetupSideFloorChild()
{
	if (LeftSideFloorComp)
	{
		LeftSideFloorComp->SetChildActorClass(SideFloorClass);
		LeftSideFloorComp->RegisterComponent();
		LeftSideFloorComp->AttachToComponent(LeftSideArrow, FAttachmentTransformRules::KeepRelativeTransform);
	}
	if (RightSideFloorComp)
	{
		RightSideFloorComp->SetChildActorClass(SideFloorClass);
		RightSideFloorComp->RegisterComponent();
		RightSideFloorComp->AttachToComponent(RightSideArrow, FAttachmentTransformRules::KeepRelativeTransform);
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
	    GetWorld()->GetTimerManager().SetTimer(NotUseActorTimer, this, &APoolActor::StopUsingTheActor, ActorNotUseTime, false);
	}
	
}

void APoolActor::OnEndGameOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (GameEnded.IsBound())
		{
			GameEnded.Broadcast();
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT(" BOUND"), true, true, FLinearColor::Yellow);
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("N0t BOUND"), true, true, FLinearColor::Blue);
		}
	}
	
}

//Function That Set The Actor Not To Use ...
void APoolActor::StopUsingTheActor()
{
	SetNotUse();
}


