// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/GetActorPoolMembers.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Interface/GetLvlManagerMembers.h"
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

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY()
	TScriptInterface<IGetLvlManagerMembers>LvlManagerInterface;

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


	UPROPERTY()
	bool CurrentlyUse;

	UFUNCTION()
	void SetInUse(bool InUse);

	UFUNCTION()
	void SetNotUse();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AActor>ObstacleClasses;

private:

	UChildActorComponent* ChildComponent;

	//Array Store ArrowComponent To Attach The Obstacles ....
	TArray<UArrowComponent*>ObstacleTras;


	UFUNCTION()
	 void SetComponentTransform();

	UFUNCTION()
	virtual int GetRandomTransform();

	UFUNCTION()
	void SpawnObstacle();


public:	

	FTimerHandle NotUseActorTimer;

	UFUNCTION()
	virtual void StopUsingTheActor();

	FVector CurrentDirection;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
