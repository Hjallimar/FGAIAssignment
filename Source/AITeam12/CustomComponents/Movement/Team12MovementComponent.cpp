//Author Olof Wallentin
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#include "Team12MovementComponent.h"
#include "Team12MovementStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void UTeam12MovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FacingRotationCurrent = FQuat::Slerp(FacingRotationCurrent.Quaternion(), FacingRotationTarget.Quaternion(), FacingRotationSpeed * DeltaTime).Rotator();

	if (FacingRotationCurrent.Equals(FacingRotationTarget))
	{
		FacingRotationCurrent = FacingRotationTarget;
		SetComponentTickEnabled(false);
	}

	FacingRotationSpeed = 1.0f;
}

FTeam12MovementStatics UTeam12MovementComponent::CreateFrameMovement() const
{
	return FTeam12MovementStatics(UpdatedComponent);
}

void UTeam12MovementComponent::Move(FTeam12MovementStatics& FrameMovement)
{
	FHitResult Hit;

	// First perform movement with gravity
	if (FrameMovement.ShouldApplyGravity())
	{
		SafeMoveUpdatedComponent(FrameMovement.GetGravity(), UpdatedComponent->GetComponentQuat(), true, Hit);
		Hit.Reset();
	}

	FVector Delta = GetMovementDelta(FrameMovement);

	if (!Delta.IsNearlyZero())
	{
		SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);

		if (Hit.bBlockingHit)
		{
			Delta = GetMovementDelta(FrameMovement);
		}

		SlideAlongSurface(Delta, 1.0f - Hit.Time, Hit.Normal, Hit);
	}

	FrameMovement.Hit = Hit;
	FrameMovement.FinalLocation = UpdatedComponent->GetComponentLocation();
}

void UTeam12MovementComponent::SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed)
{
	Internal_SetFacingRotation(InFacingRotation, InRotationSpeed);
}

void UTeam12MovementComponent::SetFacingRotation(const FQuat& InFacingRotation, float InRotationSpeed)
{
	Internal_SetFacingRotation(InFacingRotation.Rotator(), InRotationSpeed);
}

void UTeam12MovementComponent::SetFacingDirection(const FVector& InFacingDirection, float InRotationSpeed)
{
	Internal_SetFacingRotation(InFacingDirection.Rotation(), InRotationSpeed);
}

void UTeam12MovementComponent::Internal_SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed)
{
	FRotator NewRotation = InFacingRotation;
	NewRotation.Roll = 0.0f;
	NewRotation.Pitch = 0.0f;
	FacingRotationTarget = NewRotation;

	if (InRotationSpeed < 0.0f)
	{
		FacingRotationCurrent = NewRotation;
		SetComponentTickEnabled(false);
	}
	else
	{
		SetComponentTickEnabled(true);
		FacingRotationSpeed = InRotationSpeed;
	}
}

FVector UTeam12MovementComponent::GetMovementDelta(const FTeam12MovementStatics& FrameMovement) const
{
	return FrameMovement.GetMovementDelta();
}