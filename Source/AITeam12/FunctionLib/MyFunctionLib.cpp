#include "MyFunctionLib.h"
#include "GameFramework/Actor.h"
#include "CustomComponents/Sound/NoiseEmitterActor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


void UMyFunctionLib::SpawnNoiseEmitter(const UObject* WorldObj, FVector Location, AActor* NoiseInstigator, float Radius, float LifeTime, bool bDrawDebug)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldObj, EGetWorldErrorMode::LogAndReturnNull);
	auto Noise = World->SpawnActor<ANoiseEmitterActor>(Location, FRotator::ZeroRotator);
	Noise->NoiseInstigator = NoiseInstigator;
	Noise->StartRadius = Radius;
	Noise->LifeTime = LifeTime;
	Noise->bDrawDebug = bDrawDebug;
}