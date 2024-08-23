// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RunningPlayer.h"
#include "Interface/GameInstanceInterface.h"
#include "StateMachine/PlayerMovement/ConcreteClass/SideMoveState.h"
#include "StateMachine/PlayerMovement/ConcreteClass/JumpState.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void ARunningPlayer::TriggerMovementTimeline(float TargetYPosition)
{
	SetActorNewLocation(TargetYPosition);
}

ARunningPlayer::ARunningPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	//RootComponent = BoxComp;

	NonMovableScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	NonMovableScene->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(NonMovableScene);

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

void ARunningPlayer::SetupTheCharacterMesh()
{
	if (GetGameInstance() && GetGameInstance()->Implements<UGameInstanceInterface>())
	{
		GetMesh()->SetSkeletalMesh(Cast<IGameInstanceInterface>(GetGameInstance())->GetCharacterMesh());
	}
}

// Called every frame
void ARunningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunningPlayer::SideMoveAction(const FInputActionValue& InputValue)
{
	if (!DisableMovementInput)
	{
		DisableMovementInput = true;
		CurrentMoveValue = InputValue.Get<float>();
		StateLibrary[EnumState::GroundMove]->EnterState(this, GetWorld());
	}
	
}

//Jump Function That Call The Jump State...
void ARunningPlayer::JumpAction(const FInputActionValue& InputValue)
{
	
	StateLibrary[EnumState::Jump]->EnterState(this,GetWorld());
}







