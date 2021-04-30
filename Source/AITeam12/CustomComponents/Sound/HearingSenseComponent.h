#pragma once

#include "Components/ActorComponent.h"
#include "HearingSenseComponent.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FHearingInfo 
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	AActor* NoiseInstigator = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FVector Location = FVector::ZeroVector;
};

//event void HearingSenseDelegate(HearingInfo HearingInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHearingSenseDelegate, const FHearingInfo&, HearingInfo);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UHearingSenseComponent :public UActorComponent 
{
	GENERATED_BODY()
public:

	UHearingSenseComponent();

	UPROPERTY(BlueprintAssignable)
	FHearingSenseDelegate OnNoiseHeared;

	UFUNCTION()
	void RegisterNoise(ANoiseEmitterActor* NoiseEmitter);

	UPROPERTY(EditAnywhere)
	float HearingRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	bool bDrawDebugLines = false;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnComponentDestroyed(bool bDestroyedHierarchy) override;
	virtual void BeginPlay() override;
};