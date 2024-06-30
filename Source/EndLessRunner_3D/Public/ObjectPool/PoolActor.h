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

	
	virtual bool CurrentActorUseState()override;

	virtual void SetActorInUse()override;

	virtual FTransform ArrowTransform() override;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadOnly , EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* Arrowcomponent;

	//UPROPERTY(VisibleDefaultsOnly)
	//UObjectPoolComp* ObjectPoolComponent;


protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	bool CurrentlyUse;

	UFUNCTION()
	void SetInUse(bool InUse);

	UFUNCTION()
	void SetNotUse();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
