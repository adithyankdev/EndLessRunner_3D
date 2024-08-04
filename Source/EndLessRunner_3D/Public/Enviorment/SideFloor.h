// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "SideFloor.generated.h"

UCLASS()
class ENDLESSRUNNER_3D_API ASideFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASideFloor();

	 void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly)
	UInstancedStaticMeshComponent* InstancedStaticMesh;

    void BeginPlay() override;

};
