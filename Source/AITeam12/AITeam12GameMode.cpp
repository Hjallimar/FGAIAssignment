// Copyright Epic Games, Inc. All Rights Reserved.

#include "AITeam12GameMode.h"
#include "AITeam12HUD.h"
#include "AITeam12Character.h"
#include "UObject/ConstructorHelpers.h"


AAITeam12GameMode::AAITeam12GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAITeam12HUD::StaticClass();
}


