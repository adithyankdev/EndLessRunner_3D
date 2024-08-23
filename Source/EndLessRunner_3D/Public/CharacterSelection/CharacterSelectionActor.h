// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterSelectionActor.generated.h"


UCLASS()
class ENDLESSRUNNER_3D_API ACharacterSelectionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterSelectionActor();

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category = "Select Character")
	USkeletalMeshComponent* BaseMesh; 

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category = "Select Character")
	TArray<USkeletalMesh*>GameCharactersMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Select Character");
	TArray<UAnimSequence*>GameCharactersAnimation;

	int CurrentIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Variable Storing The Widget Ref*/
	UPROPERTY()
	class UCharacterSelctionWidget* SelectionWidget;

	/*Varible For Storing The Class Ref For Creating It*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Select Character")
	TSubclassOf<class UCharacterSelctionWidget> SelectionWidgetClass;

	void ChangeBaseMesh();
	void FinaliseCharacterMesh();

};
