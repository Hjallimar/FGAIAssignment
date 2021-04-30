#include "Team12GameModeBase.h"
#include "CustomComponents/Vision/VisionTargetComponent.h"
#include "CustomComponents/Sound/HearingSenseComponent.h"
#include "CustomComponents/Sound/NoiseEmitterActor.h"
#include "Player/PlayerCharacter.h"

ATeam12GameModeBase::ATeam12GameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void ATeam12GameModeBase::StartPlay()
{
	Super::StartPlay();
}

void ATeam12GameModeBase::RegisterNoise(ANoiseEmitterActor* noise)
{
	for (UHearingSenseComponent* Hearing : HearingList)
	{
		Hearing->RegisterNoise(noise);
	}
}