#pragma once

#include "GameFramework/Actor.h"
#include "NoiseEmitterActor.generated.h"

//G�ra om s� att NoiseEmitter �r en component som l�ggs p� ett obj
//Detta g�r att objectet kan fixa s� att den g�r ljud ifr�n sig �ven om den r�r p� sig.
//Eventuellt skapa en ny Antingen Event eller liknande som �r oneshot f�r ljud.

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