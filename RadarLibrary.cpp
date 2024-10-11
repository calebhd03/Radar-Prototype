// Fill out your copyright notice in the Description page of Project Settings.


#include "RadarLibrary.h"

void URadarLibrary::ShootRadars(const int& NumberOfRays, const float& TotalAngleRange, const int& MaxDistance, const FVector& ForwardVector, const AActor * Actor, const FVector& GridSize, TArray<FVector>& HitLocations, TArray<FVector>& RayDirections)
{

    FVector ActorLocation = Actor->GetActorLocation();

    float AngleStep = TotalAngleRange / (NumberOfRays - 1);
    float HalfAngleRange = TotalAngleRange / 2;

    FVector dir = FVector::CrossProduct(ActorLocation.UpVector, ForwardVector);

    for (int32 i = 0; i < NumberOfRays; ++i)
    {
        // Calculate the angle for this ray
        float CurrentAngle = -HalfAngleRange + (i * AngleStep);

        // Rotate forward vector around the Z-axis by CurrentAngle
        FVector RayDirection = ForwardVector.RotateAngleAxis(CurrentAngle, dir);
        RayDirections.Add(RayDirection);


        // Perform a line trace (raycast)
        FVector Start = ActorLocation;
        FVector End = Start + (RayDirection * MaxDistance);

        FHitResult HitResult;
        bool bHit = Actor->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

        if (bHit)
        {
            // Handle what happens when a ray hits something

            // Calculate the normalized distance from the radar origin to the hit location
            float DistanceFromRadar = FVector::Dist(ActorLocation, HitResult.Location);
            float NormalizedDistance = FMath::Clamp(DistanceFromRadar / MaxDistance, 0.0f, 1.0f);

            // Map the world space hit location to a 10x10 grid
            FVector MappedLocation3D = URadarLibrary::MapToGrid(HitResult.Location - ActorLocation, MaxDistance, GridSize);

            // Convert the 2D mapped location back into 3D space for the particle system (use Z=0 or any plane)
            //FVector MappedLocation3D = FVector(MappedLocation2D, 0.0f);
            
            HitLocations.Add(MappedLocation3D);
        }

        // Optional: Draw debug line for visualization
        // DrawDebugLine(Actor->GetWorld(), Start, End, FColor::Red, false, 1.0f, 1, 5.0f);
    }

    FHitResult hit;
    hit.Distance;
    hit.Normal;


}

FVector URadarLibrary::MapToGrid(FVector LocalHitLocation, float MaxDistance, FVector GridSize)
{
    // Normalize the hit location relative to the max distance
    float XNormalized = FMath::Clamp(LocalHitLocation.X / MaxDistance, -1.0f, 1.0f);
    float YNormalized = FMath::Clamp(LocalHitLocation.Y / MaxDistance, -1.0f, 1.0f);
    float ZNormalized = FMath::Clamp(LocalHitLocation.Z / MaxDistance, -1.0f, 1.0f);

    // Map the normalized value to the grid size
    float XMapped = XNormalized * (GridSize.X / 2);  // Half-size grid for positive and negative range
    float YMapped = YNormalized * (GridSize.Y / 2);
    float ZMapped = ZNormalized * (GridSize.Z / 2);

    return FVector(XMapped, YMapped, ZMapped);
}
