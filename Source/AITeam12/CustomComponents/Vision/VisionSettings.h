#pragma once

#include "Engine/DataAsset.h"
#include "VisionSettings.generated.h"

UCLASS()
class UVisionSettings : public UDataAsset 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float Angle = 180.0f;

	UPROPERTY(EditAnywhere)
	float MinimumDistance = 8000.0f;
};