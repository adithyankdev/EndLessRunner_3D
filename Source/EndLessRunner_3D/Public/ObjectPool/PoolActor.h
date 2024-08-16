// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/GetActorPoolMembers.h"
#include "Components/InstancedStaticMeshComponent.h"
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
	virtual ~APoolActor();

	void OnConstruction(const FTransform& Transform)override;

	//Interface Function

	/*For Getting The Actor UseState*/
	virtual bool CurrentActorUseState()override;
	/*Setting Actor To InUse*/
	virtual void SetActorInUse()override;
	/*Retrving The SpawnArrowComponent Transform For Next Setting NxtTileTransform*/
	virtual FTransform SpawnArrowTransform() override;

	/*Varibale Responsible For The Floor Move Speed*/
	 static float Speed;
	 /*Varibale Responsible For SetActorNotToUse In Time*/
	 static float ActorNotUseTime;


	void IncreaseSpeed() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	/*Storing The Ref To LvlMangerInterface For Caching*/
	UPROPERTY()
	TScriptInterface<IGetLvlManagerMembers>LvlManagerInterface;

	/*Base Component Of The Actor*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadOnly , EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);             
	UArrowComponent* Arrowcomponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* ObstacleArrowcomp_One;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* ObstacleArrowcomp_Two;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* ObstacleArrowcomp_Three;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* DirectionalArrow;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* RightSideArrow;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly);
	UArrowComponent* LeftSideArrow;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* InstancedMeshVolume;

	UPROPERTY(EditDefaultsOnly)
	UInstancedStaticMeshComponent* InstancedStaticMesh;

	/*Retriving The Actor UseState*/
	UPROPERTY()
	bool CurrentlyUse;
	/*Setting The Actor To Use*/
	UFUNCTION()
	void SetInUse(bool InUse);
	/*Setting The Actor NotInUse*/
	UFUNCTION()
	void SetNotUse();
	/*For Storing The Obstacle Class Ref*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AActor>ObstacleClasses;

	UPROPERTY(BlueprintReadOnly , EditAnywhere)
	TSubclassOf<AActor>SideFloorClass;

private:

	/*Setting The Obstacle*/
	UChildActorComponent* ChildComponent;

	//UPROPERTY(EditDefaultsOnly)
	UChildActorComponent* RightSideFloorComp;
	//UPROPERTY(EditDefaultsOnly)
	UChildActorComponent* LeftSideFloorComp;

	//Array Store ArrowComponent To Attach The Obstacles ....
	TArray<UArrowComponent*>ObstacleTras;

	/*Storing The Obstacle Transform In An Array*/
	UFUNCTION()
	 void SetComponentTransform();
	/*Getting The Random Transform For Avoiding Repeatness*/
	UFUNCTION()
	 int GetRandomTransform();
	/*Creating The ChldComponent(Obstacle)*/
	UFUNCTION()
	 void SpawnObstacle();

	UFUNCTION()
	void SetupSideFloorChild();

public:	

	/*For Calling Function To Set Actor NotInUse After Overlape*/
	UPROPERTY()
	FTimerHandle NotUseActorTimer;

	/*Variable That Represesnt The Actor Direction*/
	UPROPERTY()
	FVector CurrentDirection;

	/*Function That Set Actor To NotInUse After A Delay*/
	UFUNCTION()
	virtual void StopUsingTheActor();


	/*For Spawning Nxt Tile And Setting Current Tile NotInUse*/
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};

