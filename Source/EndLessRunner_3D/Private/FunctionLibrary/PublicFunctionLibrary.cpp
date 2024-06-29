// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/PublicFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


FLevelManagerInfo UPublicFunctionLibrary::GetLevelManagerInfo(UWorld* GetWorld)
{
	FLevelManagerInfo ValueStruct;
	return ValueStruct;
}

//This LineTrace Check Wheather The Player Is On Ground Or Not .....
bool UPublicFunctionLibrary::LineTraceCheck(UWorld* World, FVector Location)
{
	FHitResult Hit;
	FVector Start = Location; 
	FVector End = Start - FVector(0.0f, 0.0f, 50.0f);
	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams Params;
	//Params.AddIgnoredActor(Player);

	bool OnGround = World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel);
	DrawDebugLine(World, Start, End, FColor::Red, false, 1, 0, 1);
	return OnGround;
	
}


