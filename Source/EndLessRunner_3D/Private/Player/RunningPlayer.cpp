// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RunningPlayer.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"
#include "StateMachine/PlayerMovement/ConcreteClass/JumpState.h"
#include "Kismet/KismetSystemLibrary.h"

ARunningPlayer::ARunningPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	//RootComponent = BoxComp;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->SetupAttachment(RootComponent);

	PlayerSideMove = new SideMoveState();
	PlayerJump = new JumpState();
	CurrentState = nullptr;    // PlayerCurrently Doing Nothing  ...... Moving Forward (In Tick)


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

	//float Speed = (GetActorForwardVector().X * 100.0f)*DeltaTime;
	//AddActorLocalOffset(FVector(Speed, 0.0f, 0.0f));

}

void ARunningPlayer::SideMoveAction(const FInputActionValue& InputValue)
{
	CurrentMoveValue = InputValue.Get<float>();
	StateTransition(PlayerSideMove);
}

void ARunningPlayer::JumpAction(const FInputActionValue& InputValue)
{
	StateTransition(PlayerJump);
	
}

// Helper Function .... 
void ARunningPlayer::StateTransition(PlayerMoveAbstract* NextState)
{
	if (NextState != CurrentState)
	{
		PlayerMoveAbstract* PreviousState = CurrentState;
		CurrentState = NextState;
		NextState->EnterState(this, GetWorld());
	}
	
}




