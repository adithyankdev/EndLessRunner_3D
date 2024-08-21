// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/PoolActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Level/LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "Player/RunningPlayer.h"
#include "Kismet/KismetMathLibrary.h"


float APoolActor::Speed = 0.0f;
float APoolActor::ActorNotUseTime = 2.0f;

//Retrive The Current State Of Actor (On Use Or Not) ...
bool APoolActor::CurrentActorUseState()
{
	return CurrentlyUse;
   
}

//Setting The Actor True When it Used ...
void APoolActor::SetActorInUse()
{
	SetInUse(true);
	this->RerunConstructionScripts();
}

//Getting The ArrowComponent  For Spawning The Next Tile ...
FTransform APoolActor::SpawnArrowTransform()
{
	return Arrowcomponent->GetComponentTransform();
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

	InstancedMeshVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	InstancedMeshVolume->SetupAttachment(RootComponent);
	
	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstanceMeshComponent"));
	InstancedStaticMesh->SetupAttachment(InstancedMeshVolume);

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
void APoolActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	InstancedStaticMesh->ClearInstances();

	InstancedStaticMesh->SetWorldLocation(InstancedMeshVolume->GetRelativeLocation());

	//Getting The Bounds Of The BoxCollision 
	FVector BoxExtent = InstancedMeshVolume->GetScaledBoxExtent();
	FVector Origin = InstancedMeshVolume->GetComponentLocation();

	//Loop For Adding Instances
	for (int32 i = 0; i < 100; ++i)
	{
		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);

		//float RandomScaleXY = FMath::FRandRange(2.0f, 5.0f);
		float RandomScaleY = FMath::FRandRange(1.0f, 2.0f);
		float RandomScaleZ = FMath::FRandRange(1.0f, 2.0f);

		//Setting Up The Transform For Instance
		FTransform InstanceTransform(FRotator::ZeroRotator, RandomLocation, FVector(RandomScaleY, RandomScaleY, RandomScaleZ));

		// Adding Instance To InstancedStaticMesh
		InstancedStaticMesh->AddInstance(InstanceTransform);
	}
}
APoolActor::~APoolActor()
{

}


void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	Speed = 800.0f;
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

  
}

//Tick Function
void APoolActor::Tick(float DeltaTime)
{   
	AddActorLocalOffset(((CurrentDirection)*Speed)* DeltaTime);
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
		GetWorld()->GetTimerManager().SetTimer(NotUseActorTimer, this, &APoolActor::StopUsingTheActor,ActorNotUseTime, false);				
			
	}
	
}

//Function That Set The Actor Not To Use ...
void APoolActor::StopUsingTheActor()
{
	SetNotUse();
	RerunConstructionScripts();
}


