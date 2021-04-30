#pragma once

#include "Components/ActorComponent.h"
#include "VisionTargetComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UVisionTargetComponent:public UActorComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyedHierarchy) override;
	FVector GetTargetOrigin() const;
};