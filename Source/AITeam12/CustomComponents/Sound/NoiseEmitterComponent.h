#pragma once

#include "Components/ActorComponent.h"
#include "NoiseEmitterComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UNoiseEmitterComponent :public UActorComponent
{
	GENERATED_BODY()
public:

	UNoiseEmitterComponent();

	UPROPERTY(EditAnywhere)
	float SoundRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	bool bDrawDebugLines = false;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
};