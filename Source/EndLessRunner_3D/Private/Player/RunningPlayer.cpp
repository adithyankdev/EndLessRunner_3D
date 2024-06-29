// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RunningPlayer.h"

// Sets default values
ARunningPlayer::ARunningPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARunningPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARunningPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

