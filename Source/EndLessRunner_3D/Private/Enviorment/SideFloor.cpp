// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviorment/SideFloor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASideFloor::ASideFloor()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(DefaultComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetWorldLocation(FVector(0, 0, 55));

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstanceMeshComponent"));
	InstancedStaticMesh->SetupAttachment(BoxCollision);

}

void ASideFloor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Clear Any Existing Instances
	InstancedStaticMesh->ClearInstances();

	//Getting The Bounds Of The BoxCollision 
	FVector BoxExtent = BoxCollision->GetScaledBoxExtent();
	FVector Origin = BoxCollision->GetComponentLocation();

	//Loop For Adding Instances
	for (int32 i = 0; i < 25; ++i)
	{
		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);

		float RandomScale = FMath::FRandRange(2.0f, 5.0f);

		//Setting Up The Transform For Instance
		FTransform InstanceTransform(FRotator::ZeroRotator, RandomLocation, FVector(RandomScale));

		// Adding Instance To InstancedStaticMesh
		InstancedStaticMesh->AddInstance(InstanceTransform);
	}
}


void ASideFloor::BeginPlay()
{
	Super::BeginPlay();
}


