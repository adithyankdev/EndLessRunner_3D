// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/GetActorPoolMembers.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "PoolActor.generated.h"

class UObjectPoolComp;

UCLASS()
class ENDLESSRUNNER_3D_API APoolActor : public AActor , public IGetActorPoolMembers
{
	GENERATED_BODY()
	
public:	
	APoolActor();

	//Interface Function

	virtual bool CurrentActorUseState()override;

	virtual void SetActorInUse()override;

	virtual FTransform ArrowTransform() override;

	void SetDirectionValue(FVector LocationValue) override;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadOnly , EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* Arrowcomponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* ObstacleArrowcomp_One;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* ObstacleArrowcom_Two;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* ObstacleArrowcomp_Three;

	UChildActorComponent* ChildComponent;
	
	UPROPERTY()
	AActor* LevelManager;

	UPROPERTY()
	bool CurrentlyUse;

	UFUNCTION()
	void SetInUse(bool InUse);

	UFUNCTION()
	void SetNotUse();


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//Array Store ArrowComponent To Attach The Obstacles ....
	TArray<UArrowComponent*>ObstacleTras;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TSubclassOf<AActor>ObstacleClasses;

	UFUNCTION()
	 virtual void SetComponentTransform();

	UFUNCTION()
	virtual int GetRandomTransform();

	UFUNCTION()
	virtual void SpawnObstacle();

	FTimerHandle NotUseActorTimer;

	UFUNCTION()
	virtual void StopUsingTheActor();

	FVector CurrentDirection;

public:	

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
