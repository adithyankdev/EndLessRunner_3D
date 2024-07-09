// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTiles/LeftTurnTile.h"
#include "Kismet/KismetSystemLibrary.h"


void ALeftTurnTile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	
}
