// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Interface/GetPlayerInfoInterface.h"
#include "Components/ArrowComponent.h"
#include "RunningPlayer.generated.h"

/*State Machines*/
class PlayerMoveAbstract;
class SideMoveState;
class JumpState;


UCLASS()
class ENDLESSRUNNER_3D_API ARunningPlayer : public ACharacter , public IGetPlayerInfoInterface
{
	GENERATED_BODY()

public:

	/*Object Initialisation Of State */
	PlayerMoveAbstract* CurrentState;
	SideMoveState* PlayerSideMove;
	JumpState* PlayerJump;

	void SetPlaneConstraints() override;
	void SetLocation(FVector NewLocation) override;

	ARunningPlayer();
   

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	bool ConstraintToogle;

public:	
	virtual void Tick(float DeltaTime) override;

	/*To Store Current Movement InputValue To DeterMine Which Key Pressed*/
	float CurrentMoveValue;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player Base")
	UBoxComponent* BoxComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Base")
	UArrowComponent* JumpArrow;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Player Base")
	UArrowComponent* MovementArrow;

	void SideMoveAction(const FInputActionValue& InputValue);
	void JumpAction(const FInputActionValue& InputValue);

	void StateTransition(PlayerMoveAbstract * NextState);

};
