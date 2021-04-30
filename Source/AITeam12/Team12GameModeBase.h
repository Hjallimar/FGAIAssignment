#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Team12GameModeBase.generated.h"

class UHearingSenseComponent;
class ANoiseEmitterActor;
class UVisionTargetComponent;

UCLASS()
class ATeam12GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATeam12GameModeBase();
	void StartPlay() override;

	UFUNCTION()
	void RegisterNoise(ANoiseEmitterActor* Noise);

	void RegisterOneShot(FVector Location, float Radius = 300.0f);

	UPROPERTY()
	TArray<UVisionTargetComponent*> VisionTargetList;

	UPROPERTY()
	TArray<UHearingSenseComponent*> HearingList;
};