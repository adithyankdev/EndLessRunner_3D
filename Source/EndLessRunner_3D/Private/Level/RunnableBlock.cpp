// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/RunnableBlock.h"

// Sets default values
ARunnableBlock::ARunnableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(BaseScene);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	BoxCollision->SetupAttachment(StaticMeshComp);

	MinScaleValue = 10.0f;

}

void ARunnableBlock::OnConstruction(const FTransform& Transform)
{
	float MaxScaleValue = 10.0f;
	float YValue = 1.5f;
	float ZValue = 2.0f;
	float XValue = FMath::FRandRange(MinScaleValue,MaxScaleValue);
	StaticMeshComp->SetWorldScale3D(FVector(XValue,YValue,ZValue));
}

// Called when the game starts or when spawned
void ARunnableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunnableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

