#pragma once

#include "PlayerCharacter.h"
#include "PacManPlayer.generated.h"

class ABaseBullet;
class UVisionTargetComponent;
class UHealthComponent;

UCLASS()
class APacManPlayer : public APlayerCharacter
{
	GENERATED_BODY()

public:

	APacManPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseBullet> BulletType;
 
	UPROPERTY(VisibleAnywhere, Category = Vision)
	UVisionTargetComponent* VisionTarget;

	UPROPERTY(VisibleAnywhere, Category = Health)
	UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable)
	void IncreaseAmmo();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentAmmo = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxScore = 200;

	void OnFire();

	UFUNCTION()
	void OnDamageTaken(float Damage);

	UPROPERTY(BlueprintReadOnly)
	FVector StartPosition;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayerFire();
	UFUNCTION(BlueprintImplementableEvent)
	void AmmoIncrease();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayerWin();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayerGameOver();
	UPROPERTY(BlueprintReadOnly)
	int CurrentScore = 0;
};