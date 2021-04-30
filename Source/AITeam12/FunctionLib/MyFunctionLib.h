#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyFunctionLib.generated.h"

class AActor;

UCLASS()
class UMyFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "NoiseEmitter", meta = (WorldContext = "WorldObj"))
	static void SpawnNoiseEmitter(const UObject* WorldObj,FVector Location, AActor* NoiseInstigator, float Radius = 300.0f, float LifeTime = 1.2f, bool bDrawDebug = false);
};