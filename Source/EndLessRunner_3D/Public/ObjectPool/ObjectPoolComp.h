// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool/PoolActor.h"
#include "ObjectPoolComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER_3D_API UObjectPoolComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ObjectPool Base")
	TSubclassOf<AActor>PoolActorClass;

	UPROPERTY()
	TArray<AActor*>PoolActorArray;

	UPROPERTY()
	int PoolSize;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SingleTileSize;

	UPROPERTY()
	AActor* LatestRearFloor;

	UPROPERTY()
	int QuickSpwanCount;

	UObjectPoolComp();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void InitializePool();

	UFUNCTION(BlueprintCallable)
	AActor* UseFromPool(FTransform UseTransform);

	UFUNCTION()
	AActor* GetNotInUseActor();

	//HelperFunctions
	 
	 UFUNCTION()
	 FTransform QuickActorTransform(AActor* SpawnActor);
	
	//UFUNCTION()
	//void UpdateLatestRearFloor();

	

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
