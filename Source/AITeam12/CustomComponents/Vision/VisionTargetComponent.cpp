#include "VisionTargetComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Team12GameModeBase.h"

void UVisionTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* GameMode = Cast<ATeam12GameModeBase>(UGameplayStatics::GetGameMode(this));
	GameMode->VisionTargetList.Add(this);
}

void UVisionTargetComponent::OnComponentDestroyed(bool bDestroyedHierarchy) 
{
	auto* GameMode = Cast<ATeam12GameModeBase>(UGameplayStatics::GetGameMode(this));
	if(GameMode != nullptr)
		GameMode->VisionTargetList.Remove(this);
	
	Super::OnComponentDestroyed(bDestroyedHierarchy);
}

FVector UVisionTargetComponent::GetTargetOrigin() const
{
	return GetOwner()->GetActorLocation();
}