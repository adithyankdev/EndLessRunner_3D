// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RunningPlayer.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"
#include "StateMachine/PlayerMovement/ConcreteClass/JumpState.h"
#include "GameFramework\CharacterMovementComponent.h"
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

	JumpArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	JumpArrow->SetupAttachment(RootComponent);

	MovementArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MoveDirectionArrow"));
	MovementArrow->SetupAttachment(RootComponent);

	PlayerMoveAbstract* temp = new SideMoveState();
	StateLibrary.Add(EnumState::GroundMove, temp);
	temp = new JumpState();
	StateLibrary.Add(EnumState::Jump, temp);
	
}

ARunningPlayer::~ARunningPlayer()
{
	StateLibrary.Empty();
}

// Called when the game starts or when spawned
void ARunningPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
}

// Called every frame
void ARunningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunningPlayer::SideMoveAction(const FInputActionValue& InputValue)
{
	CurrentMoveValue = InputValue.Get<float>();
	StateLibrary[EnumState::GroundMove]->EnterState(this,GetWorld());
}

//Jump Function That Call The Jump State...
void ARunningPlayer::JumpAction(const FInputActionValue& InputValue)
{
	StateLibrary[EnumState::Jump]->EnterState(this,GetWorld());
}







