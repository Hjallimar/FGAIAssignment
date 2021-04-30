#pragma once

#include "GameFramework/Actor.h"
#include "NoiseEmitterActor.generated.h"

//Göra om så att NoiseEmitter är en component som läggs på ett obj
//Detta gör att objectet kan fixa så att den gör ljud ifrån sig även om den rör på sig.
//Eventuellt skapa en ny Antingen Event eller liknande som är oneshot för ljud.

UCLASS()
class ANoiseEmitterActor : public AActor 
{
	GENERATED_BODY()
public:
	ANoiseEmitterActor();

	USceneComponent* RootComp;

	float StartRadius = 300.0f;
	float LifeTime = 1.2f;

	UPROPERTY(BlueprintReadOnly)
	AActor* NoiseInstigator;

	bool bDrawDebug = false;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Tick(float DeltaTime) override;
};