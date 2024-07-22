// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RunningPlayer.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"
#include "StateMachine/PlayerMovement/ConcreteClass/JumpState.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void ARunningPlayer::SetPlaneConstraints()
{
	ConstraintToogle = !ConstraintToogle;
	if (ConstraintToogle)
	{
		GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
	}
	else
	{
		GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	}
}

void ARunningPlayer::SetLocation(FVector NewLocation)
{
	SetActorLocation(NewLocation);
	FString De = NewLocation.ToString();
	UKismetSystemLibrary::PrintString(GetWorld(), De, true, true, FLinearColor::Green,10);
	FString D = TEXT("Player New Location Changed");
	UKismetSystemLibrary::PrintString(GetWorld(), D,true,true,FLinearColor::Red);

}

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

	PlayerSideMove = new SideMoveState();
	PlayerJump = new JumpState();
	CurrentState = nullptr;    // PlayerCurrently Doing Nothing  ...... Moving Forward (In Tick)
	SetPlaneConstraints();
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

}

void ARunningPlayer::SideMoveAction(const FInputActionValue& InputValue)
{
	CurrentMoveValue = InputValue.Get<float>();
	StateTransition(PlayerSideMove);
}

//Jump Function That Call The Jump State...
void ARunningPlayer::JumpAction(const FInputActionValue& InputValue)
{
	StateTransition(PlayerJump);	
}

// Helper Function .... 

//Function That Made Transition From One State To Another..
void ARunningPlayer::StateTransition(PlayerMoveAbstract* NextState)
{
	if (NextState != CurrentState)
	{
		PlayerMoveAbstract* PreviousState = CurrentState;
		CurrentState = NextState;
		NextState->EnterState(this, GetWorld());
	}
	
}




