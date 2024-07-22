// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTiles/RightTurnTile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Level/LevelManager.h"
#include "Player/RunningPlayer.h"



TMap<int, FVector> ARightTurnTile::GetTileLineLocations()
{
	return LaneLocations;
}

void ARightTurnTile::BeginPlay()
{
	Super::BeginPlay();

}

void ARightTurnTile::SetComponentTransform()
{
	LaneLocations.Add(3, ObstacleArrowcomp_One->GetComponentLocation());
	LaneLocations.Add(2, ObstacleArrowcomp_Two->GetComponentLocation());
	LaneLocations.Add(1, ObstacleArrowcomp_Three->GetComponentLocation());
}

void ARightTurnTile::SpawnObstacle()
{

}

int ARightTurnTile::GetRandomTransform()
{
	return 0;
}

//Adding Addition Functionality To BeginOverlap...
void ARightTurnTile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor->IsA(ARunningPlayer::StaticClass()))
	{
		AActor* LvlActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass());
		if (LvlActor)
		{
			if (LvlActor->GetClass()->ImplementsInterface(UGetLvlManagerMembers::StaticClass()))
			{
				IGetLvlManagerMembers* Interface = Cast<IGetLvlManagerMembers>(LvlActor);         //Informing The Interface That The Player Is Overlaped...
				Interface->SetCanPlayerTurn(true);
				Interface->SetQuickUseOnTurn();

			}
		}
	}
	
}

