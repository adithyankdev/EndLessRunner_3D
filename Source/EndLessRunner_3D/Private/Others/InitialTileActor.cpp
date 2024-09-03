// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/InitialTileActor.h"

#include "Interface/GameInstanceInterface.h"
#include "SaveGame/RunnerSaveGame.h"

#include "Level/LevelManager.h"
#include "Player/RunningPlayer.h"

#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AInitialTileActor::AInitialTileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
	SetRootComponent(BaseSceneComponent);

	HighestScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXT"));
	HighestScoreText->SetupAttachment(RootComponent);

	BoundaryCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoundaryCollision->SetupAttachment(RootComponent);

	EndGameCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisinBox"));
	EndGameCollision->SetupAttachment(RootComponent);

	Speed = 800.0f;

	MovementDirection = FVector::ZeroVector;
	//Actor Should Be Move Toware -X Axis --- Player Facing Towards X Axis
	MovementDirection.X = Speed*-1;

}

// Called when the game starts or when spawned
void AInitialTileActor::BeginPlay()
{
	Super::BeginPlay();

	BoundaryCollision->OnComponentBeginOverlap.AddDynamic(this, &AInitialTileActor::OnBeginOverlap);
	EndGameCollision->OnComponentBeginOverlap.AddDynamic(this, &AInitialTileActor::OnBeginOverlapCollision);

	BindText();
}


void AInitialTileActor::OnBeginOverlapCollision(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweap, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ARunningPlayer::StaticClass()))
	{
		if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass()))
		{
			if (IGetLvlManagerMembers* Interface = Cast <IGetLvlManagerMembers>(Actor))
			{
				StartStopingMovement();
				Interface->NotifyPlayerHit();
			}
		}
	}
}

void AInitialTileActor::BindText()
{
	if (GetGameInstance() && GetGameInstance()->Implements<UGameInstanceInterface>())
	{
		URunnerSaveGame* SaveGame =  Cast<IGameInstanceInterface>(GetGameInstance())->GetSaveGame();

		if (SaveGame->HighestScore == 0)HighestScoreText->SetVisibility(false);

		FText ScoreText = FText::FromString(FString::FromInt(SaveGame->HighestScore));
		HighestScoreText->SetText(ScoreText);

		                
    }
}


// Called every frame
void AInitialTileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(MovementDirection*DeltaTime);

}

void AInitialTileActor::StartStopingMovement()
{
	GetWorld()->GetTimerManager().SetTimer(StopActorMotionTimer, this, &AInitialTileActor::StopingMovement,0.5,true);
}

void AInitialTileActor::StopingMovement()
{
	if (Speed < 280)
	{
		Speed = 0;
		SetActorTickEnabled(false);
		GetWorld()->GetTimerManager().ClearTimer(StopActorMotionTimer);
	}
	Speed -= 280;
}

void AInitialTileActor::OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweap, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ARunningPlayer::StaticClass()))
	{
		FTimerHandle DestroyTimer;
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AInitialTileActor::DestroyActor, 5);
		
	}
}
void AInitialTileActor::DestroyActor()
{
	Destroy();
}



