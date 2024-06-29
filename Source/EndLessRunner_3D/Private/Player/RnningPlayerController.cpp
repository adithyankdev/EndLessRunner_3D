// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RnningPlayerController.h"
#include "Player/PlayerInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void ARnningPlayerController::BeginPlay()
{
	if (UPlayerInputComponent* PlayerInputComp = Cast <UPlayerInputComponent>(this))
	{
		PlayerInputComp->RegisterComponent();
		PlayerInputComp->SetupInputBindings();
		PlayerInputComp->Activate();
		this->InputComponent = PlayerInputComp;
	}
	else
	{
		FString D = TEXT("Custom input componnet failed");
		UKismetSystemLibrary::PrintString(GetWorld(), D, true, true, FLinearColor::Red, 4);
	}

}
