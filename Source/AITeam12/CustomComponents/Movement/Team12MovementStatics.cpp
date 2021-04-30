//Author Olof Wallentin
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#include "Team12MovementStatics.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

FTeam12MovementStatics::FTeam12MovementStatics(AActor* InActor)
{
	StartLocation = InActor->GetActorLocation();
}

FTeam12MovementStatics::FTeam12MovementStatics(USceneComponent* InSceneComponent)
{
	StartLocation = InSceneComponent->GetComponentLocation();
}

void FTeam12MovementStatics::AddDelta(const FVector& InDelta)
{
	MovementDelta += InDelta;
}
