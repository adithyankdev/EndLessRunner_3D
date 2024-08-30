// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/InitialTileActor.h"
#include "Interface/GameInstanceInterface.h"
#include "SaveGame/RunnerSaveGame.h"

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

}

// Called when the game starts or when spawned
void AInitialTileActor::BeginPlay()
{
	Super::BeginPlay();

	BindText();
}

void AInitialTileActor::BindText()
{
	if (GetGameInstance() && GetGameInstance()->Implements<UGameInstanceInterface>())
	{
		URunnerSaveGame* SaveGame =  Cast<IGameInstanceInterface>(GetGameInstance())->GetSaveGame();

		FText ScoreText = FText::FromString(FString::FromInt(SaveGame->HighestScore));
		HighestScoreText->SetText(ScoreText);
    }
}

// Called every frame
void AInitialTileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

