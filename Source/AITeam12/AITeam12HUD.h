// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AITeam12HUD.generated.h"

UCLASS()
class AAITeam12HUD : public AHUD
{
	GENERATED_BODY()

public:
	AAITeam12HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

