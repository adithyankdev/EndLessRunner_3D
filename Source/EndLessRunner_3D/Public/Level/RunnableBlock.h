// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/RunnableBlockInterface.h"
#include "RunnableBlock.generated.h"

UCLASS()
class ENDLESSRUNNER_3D_API ARunnableBlock : public AActor , public IRunnableBlockInterface
{
	GENERATED_BODY()
	
public:	

	void ChangeRootScaleSize() override;

	// Sets default values for this actor's properties
	ARunnableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultRoot;

	float RootXScale;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
