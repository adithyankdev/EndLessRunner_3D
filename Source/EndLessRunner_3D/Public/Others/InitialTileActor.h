// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
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

	void BindText();

};
