// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RadarLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RADARSIMULATION2_API URadarLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Shoot Radars"), Category = "Game Config")
		static void ShootRadars(const int& NumberOfRays, const float& TotalAngleRange, const int& MaxDistance, const FVector& ForwardVector, const AActor* Actor, const FVector& GridSize, TArray<FVector>& HitLocations, TArray<FVector>& RayDirections);
		static FVector MapToGrid(FVector LocalHitLocation, float MaxDistance, FVector GridSize);
};
