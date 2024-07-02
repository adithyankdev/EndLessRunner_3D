// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/GetLvlManagerMembers.h"
#include "LevelManager.generated.h"

class UObjectPoolComp;

UCLASS()
class ENDLESSRUNNER_3D_API ALevelManager : public AActor , IGetLvlManagerMembers
{
	GENERATED_BODY()
	
public:
	 
	virtual int  GetRandomInteger() override;

	ALevelManager();

	UPROPERTY(VisibleDefaultsOnly)
	UObjectPoolComp* ObjectPoolComponent;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	int NumberOfLane;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LaneWidth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LevelValues")
	float LevelSpwaningSpeed;

};
