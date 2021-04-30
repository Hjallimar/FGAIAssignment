//Author Olof Wallentin
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#pragma once
#include "CoreMinimal.h"

class AActor;
class USceneComponent;

struct FTeam12MovementStatics
{
	FTeam12MovementStatics(const FVector& InStartLocation) :
		StartLocation(InStartLocation) {}

	FTeam12MovementStatics(AActor* InActor);
	FTeam12MovementStatics(USceneComponent* InSceneComponent);

	void AddDelta(const FVector& InDelta);
	void AddGravity(const float GravityToApply) { AccumulatedGravity -= GravityToApply; }

	bool ShouldApplyGravity() const { return !FMath::IsNearlyZero(AccumulatedGravity); }

	FVector GetMovementDelta() const { return MovementDelta; }

	FHitResult Hit;

	FVector FinalLocation = FVector::ZeroVector;

	FVector GetStartLocation() const { return StartLocation; }
	FVector GetGravity() const { return FVector(0.0f, 0.0f, AccumulatedGravity); }

private:
	FVector MovementDelta = FVector::ZeroVector;
	FVector StartLocation = FVector::ZeroVector;
	float AccumulatedGravity = 0.0f;
};
