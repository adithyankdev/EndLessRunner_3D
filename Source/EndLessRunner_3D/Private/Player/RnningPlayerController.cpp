// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RnningPlayerController.h"
#include "Player/PlayerInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/RunningPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

ARnningPlayerController::ARnningPlayerController()
{
	PlayerInputComp = CreateDefaultSubobject<UPlayerInputComponent>(TEXT("CustomPlayerInputComponent"));
	
	this->InputComponent = PlayerInputComp;
}


void ARnningPlayerController::BeginPlay()
{	
	
	ARunningPlayer* MainPlayer = GetOwnerPlayer();
	Possess(MainPlayer);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(PlayerInputComp->PlayerMappingContext, 0);
	}

	// Binding Inpuut and Its Functionality
	PlayerInputComp->BindAction(PlayerInputComp->MoveInput, ETriggerEvent::Started, MainPlayer, &ARunningPlayer::SideMoveAction);
	PlayerInputComp->BindAction(PlayerInputComp->JumpInput, ETriggerEvent::Triggered, MainPlayer, &ARunningPlayer::JumpAction);

}

void ARnningPlayerController::SetupInputComponent()
{
	PlayerInputComp->SetupInputBindings();
	PlayerInputComp->RegisterComponent();
	PlayerInputComp->Activate();
	
}



//Helper Functions ... 
ARunningPlayer* ARnningPlayerController::GetOwnerPlayer()
{
	TArray<AActor*>PlayerClasses;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARunningPlayer::StaticClass(), PlayerClasses);

	if (PlayerClasses.Num() > 0)
	{
		if (ARunningPlayer* GetPlayer = Cast <ARunningPlayer>(PlayerClasses[0]))
		{
			return GetPlayer;
		}
	}

	return nullptr;
}