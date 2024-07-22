// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTiles/LeftTurnTile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/RunningPlayer.h"
#include "Level/LevelManager.h"
#include "Kismet/GameplayStatics.h"

TMap<int, FVector> ALeftTurnTile::GetTileLineLocations()
{
	return LaneLocations;
}

void ALeftTurnTile::SetComponentTransform()
{
	LaneLocations.Add(1, ObstacleArrowcomp_One->GetComponentLocation());
	LaneLocations.Add(2, ObstacleArrowcomp_Two->GetComponentLocation());
	LaneLocations.Add(3, ObstacleArrowcomp_Three->GetComponentLocation());
}

void ALeftTurnTile::SpawnObstacle()
{

}

int ALeftTurnTile::GetRandomTransform()
{
	return 0;
}
 
void ALeftTurnTile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
