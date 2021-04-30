#include "HearingSenseComponent.h"
#include "NoiseEmitterActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Team12GameModeBase.h"

UHearingSenseComponent::UHearingSenseComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UHearingSenseComponent::BeginPlay() 
{
	Super::BeginPlay();

	//Adds itself to a list of HearingSenseComponents
	auto* GameMode = Cast<ATeam12GameModeBase>(UGameplayStatics::GetGameMode(this));
	GameMode->HearingList.Add(this);
}

void UHearingSenseComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bDrawDebugLines) 
	{
		FVector OwnerLocation = GetOwner()->GetActorLocation();
		DrawDebugSphere(GetWorld(), OwnerLocation, HearingRange, 12, FColor::Red);
	}
}

void UHearingSenseComponent::OnComponentDestroyed(bool bDestroyedHierarchy)
{
	auto* GameMode = Cast<ATeam12GameModeBase>(UGameplayStatics::GetGameMode(this));
	//Removes itself from the list it added itself too in the BeginPlay
	if (GameMode != nullptr)
		GameMode->HearingList.Remove(this);

	Super::OnComponentDestroyed(bDestroyedHierarchy);
}

//Called when ever a noise emitter is created, then checks if it can be heared or not and reacts acordingly
void UHearingSenseComponent::RegisterNoise(ANoiseEmitterActor* NoiseEmitter)
{
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	float Radiussq = FMath::Square(HearingRange);
	float DistanceToNoisesq = FVector::DistSquared(NoiseEmitter->GetActorLocation(), OwnerLocation);
	float NoiseRangesq = FMath::Square(NoiseEmitter->StartRadius);
	if (DistanceToNoisesq < (NoiseRangesq + Radiussq))
	{
		FHearingInfo NewHearingInfo;
		NewHearingInfo.NoiseInstigator = NoiseEmitter->NoiseInstigator;
		FVector vect = NoiseEmitter->GetActorLocation();;
		NewHearingInfo.Location = NoiseEmitter->GetActorLocation();
		OnNoiseHeared.Broadcast(NewHearingInfo);
	}
}