// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "InitialTileActor.generated.h"

UCLASS()
class ENDLESSRUNNER_3D_API AInitialTileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInitialTileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* BaseSceneComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UTextRenderComponent* HighestScoreText;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoundaryCollision;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* EndGameCollision;

	/*Variable Responsible For Movmeent Value OF The Actor*/
	float Speed;

	/*Actor Direction For Moving*/
	FVector MovementDirection;

	/*Timer To Stop The Movement Smoothly*/
	FTimerHandle StopActorMotionTimer;

	void StartStopingMovement();
	void StopingMovement();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweap, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBeginOverlapCollision(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweap, const FHitResult& SweepResult);

	/*Binding Text On HighScoreValue*/
	void BindText();

	void DestroyActor();

};
