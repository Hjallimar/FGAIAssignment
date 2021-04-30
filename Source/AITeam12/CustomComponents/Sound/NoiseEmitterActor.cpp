#include "NoiseEmitterActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Team12GameModeBase.h"

ANoiseEmitterActor::ANoiseEmitterActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;
}

void ANoiseEmitterActor::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
	auto* GameMode = Cast<ATeam12GameModeBase>(UGameplayStatics::GetGameMode(this));
	GameMode->RegisterNoise(this);
}

void ANoiseEmitterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bDrawDebug)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), StartRadius, 12, FColor::Green);
	}
}