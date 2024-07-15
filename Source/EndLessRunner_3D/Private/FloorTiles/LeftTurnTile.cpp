// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTiles/LeftTurnTile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/RunningPlayer.h"
#include "Level/LevelManager.h"
#include "Kismet/GameplayStatics.h"


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


			}
		}
	}
}
