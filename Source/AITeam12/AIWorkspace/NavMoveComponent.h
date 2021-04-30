#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "NavMoveComponent.generated.h"

class APawn;

UCLASS()
class UNavMoveComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	UNavMoveComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	virtual void RequestPathMove(const FVector& MoveInput) override;
	virtual bool CanStartPathFollowing() const override;
	virtual bool CanStopPathFollowing() const override;
	virtual void StopActiveMovement() override;
	virtual float GetPathFollowingBrakingDistance(float MaxSpeed) const override;
	const INavigationDataInterface* GetNavData() const;
	bool FindNavFloor(const FVector& TestLocation, FNavLocation& NavFloorLocation) const;

	UPROPERTY(BlueprintReadOnly)
	FVector RequestedVelocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float HalfHeight = 250.0f;

	bool bHasRequestedVelocity = false;

};