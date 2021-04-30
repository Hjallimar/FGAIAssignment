//Author Olof Wallentin
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#pragma once
#include "GameFramework/MovementComponent.h"
#include "Team12MovementComponent.generated.h"

struct FTeam12MovementStatics;

UCLASS()
class UTeam12MovementComponent : public UMovementComponent
{
	GENERATED_BODY()
public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FTeam12MovementStatics CreateFrameMovement() const;

	void Move(FTeam12MovementStatics& FrameMovement);

	FRotator GetFacingRotation() const { return FacingRotationCurrent; }
	FVector GetFacingDirection() const { return FacingRotationCurrent.Vector(); }

	void SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed = -1.0f);
	void SetFacingRotation(const FQuat& InFacingRotation, float InRotationSpeed = -1.0f);
	void SetFacingDirection(const FVector& InFacingDirection, float InRotationSpeed = -1.0f);

private:
	void Internal_SetFacingRotation(const FRotator& InFacingRotation, float InRotationSpeed);
	FVector GetMovementDelta(const FTeam12MovementStatics& FrameMovement) const;

	FRotator FacingRotationCurrent;
	FRotator FacingRotationTarget;
	float FacingRotationSpeed;
};