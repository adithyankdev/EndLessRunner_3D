// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/ArrowComponent.h"
#include "RunningPlayer.generated.h"


UCLASS()
class ENDLESSRUNNER_3D_API ARunningPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ARunningPlayer();

protected:

	

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player Base")
	UBoxComponent* BoxComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	UArrowComponent* DirectionArrow;

	void SideMoveAction(const FInputActionValue& InputValue);

};
