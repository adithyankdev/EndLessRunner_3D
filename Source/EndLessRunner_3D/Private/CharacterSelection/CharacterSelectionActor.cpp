// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelection/CharacterSelectionActor.h"
#include "Widgets/CharacterSelctionWidget.h"
#include "Interface/GameInstanceInterface.h"

#include "Kismet/KismetSystemLibrary.h"



// Sets default values
ACharacterSelectionActor::ACharacterSelectionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalActor"));
	CurrentIndex = 0; 

}

// Called when the game starts or when spawned
void ACharacterSelectionActor::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->SetSkeletalMesh(GameCharactersMesh[0]);

	if (SelectionWidgetClass)
	{
		SelectionWidget = CreateWidget<UCharacterSelctionWidget>(GetWorld(), SelectionWidgetClass);
		if (SelectionWidget)
		{
			SelectionWidget->ChangeCharcter.BindUObject(this, &ACharacterSelectionActor::ChangeBaseMesh);
			SelectionWidget->CharacterSelected.BindUObject(this, &ACharacterSelectionActor::FinaliseCharacterMesh);

			SelectionWidget->AddToViewport();
			UE_LOG(LogTemp,Warning,TEXT("SelectionWdiget Is Good To Go ---"))
		}
		
	}

}

// Called every frame
void ACharacterSelectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterSelectionActor::ChangeBaseMesh()
{
	if (CurrentIndex < GameCharactersMesh.Num()-1)
	{
		CurrentIndex++;
	}
	else
	{
		CurrentIndex = 0;
	}

	BaseMesh->SetSkeletalMesh(GameCharactersMesh[CurrentIndex]);
	BaseMesh->PlayAnimation(GameCharactersAnimation[CurrentIndex],true);

	//Custom Scale For Avoid Larger Size Difference
	switch (CurrentIndex)
	{
	case 0 : BaseMesh->SetRelativeScale3D(FVector(0.7, 0.7, 0.7));
		break;
	case 1 : BaseMesh->SetRelativeScale3D(FVector(0.8, 0.8, 0.8));
		break;
	case 2: BaseMesh->SetRelativeScale3D(FVector(1.7, 1.7, 1.7));
	}
}

void ACharacterSelectionActor::FinaliseCharacterMesh()
{
	if ( GetGameInstance() &&  GetGameInstance()->Implements<UGameInstanceInterface>())
	{
		Cast<IGameInstanceInterface>(GetGameInstance())->SetCharacterMesh(GameCharactersMesh[CurrentIndex],CurrentIndex);
	}
}

