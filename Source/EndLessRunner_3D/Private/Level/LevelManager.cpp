// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelManager.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumberOfLane = 3;
    LaneWidth = 100.0f;
    LevelSpwaningSpeed= 50.0f;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	

}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

