// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/RunnableBlock.h"
#include "Kismet/KismetSystemLibrary.h"




void ARunnableBlock::ChangeRootScaleSize()
{
	DefaultRoot->SetRelativeScale3D(FVector(RootXScale, 1, 1));
	RootXScale -= 0.5f;

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%f"),RootXScale), true, true, FLinearColor::Green);
}

// Sets default values
ARunnableBlock::ARunnableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(DefaultRoot);

	


}

// Called when the game starts or when spawned
void ARunnableBlock::BeginPlay()
{
	Super::BeginPlay();

	RootXScale = 1.0f;
	
}

// Called every frame
void ARunnableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

