
#include "NoiseEmitterComponent.h"

UNoiseEmitterComponent::UNoiseEmitterComponent() 
{
}

void UNoiseEmitterComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNoiseEmitterComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
