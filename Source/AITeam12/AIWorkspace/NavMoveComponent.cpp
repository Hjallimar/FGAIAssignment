#include "NavMoveComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UNavMoveComponent::UNavMoveComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UNavMoveComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bHasRequestedVelocity)
		return;

	//Nonphysical movement, only following a navmesh
	GetOwner()->AddActorWorldOffset(RequestedVelocity * DeltaTime);

	//Place the pawn on the floor of the navMesh
	FNavLocation NavFloorLocation;
	if(FindNavFloor(GetOwner()->GetActorLocation(), NavFloorLocation))
	{
		float FloorHeight = NavFloorLocation.Location.Z;
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		//Offsetting the location so that half the pawn isn't below ground
		CurrentLocation.Z = FloorHeight + GetPawnOwner()->GetDefaultHalfHeight();
		GetOwner()->SetActorLocation(CurrentLocation);	
	}

	FVector Target = GetActorLocation() + (RequestedVelocity.GetSafeNormal() * 100.0f);
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target);

	GetOwner()->SetActorRotation(FRotator(0, 0, Rot.Vector().Z));
}

void UNavMoveComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	RequestedVelocity = MoveVelocity.GetSafeNormal() * MovementSpeed;
	bHasRequestedVelocity = true;
}

void UNavMoveComponent::RequestPathMove(const FVector& MoveInput)
{
	
}

bool UNavMoveComponent::CanStartPathFollowing() const
{
	return true;
}

bool UNavMoveComponent::CanStopPathFollowing() const
{
	return true;
}

void UNavMoveComponent::StopActiveMovement()
{
	Super::StopActiveMovement();

	RequestedVelocity = FVector::ZeroVector;
	bHasRequestedVelocity = false;
}

float UNavMoveComponent::GetPathFollowingBrakingDistance(float MaxSpeed) const
{
	return 1.0f;
}

const INavigationDataInterface* UNavMoveComponent::GetNavData() const
{
	const UWorld* World = GetWorld();
	if (World == nullptr || World->GetNavigationSystem() == nullptr)
		return nullptr;

	const INavigationDataInterface* NavData = FNavigationSystem::GetNavDataForActor(*GetOwner());
	return NavData;
}

bool UNavMoveComponent::FindNavFloor(const FVector& TestLocation, FNavLocation& NavFloorLocation) const
{
	const INavigationDataInterface* NavData = GetNavData();
	if (NavData == nullptr)
		return false;

	const FNavAgentProperties& AgentProps = GetPawnOwner()->GetNavAgentPropertiesRef();
	const float SearchRadius = AgentProps.AgentRadius * 2.0f;
	const float SearchHeight = AgentProps.AgentHeight * AgentProps.NavWalkingSearchHeightScale;

	return NavData->ProjectPoint(TestLocation - FVector(0, 0, GetPawnOwner()->GetDefaultHalfHeight()), NavFloorLocation, FVector(SearchRadius, SearchRadius, SearchHeight));
}