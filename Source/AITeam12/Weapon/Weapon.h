#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class USceneComponent;
class UBoxComponent;
class ABaseBullet;

UCLASS()
class AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	void Fire(FTransform FirePoint);
	void Reload();
	void Activate(bool Status);

	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;

	UPROPERTY(EditDefaultsOnly)
	FVector AimDistance = FVector(0,0,0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* GunPipe;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseBullet> BulletType;

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnReload();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnFire();

	void Drop();

	void PickUp();

protected:
	UPROPERTY(EditDefaultsOnly)
	float TimeSinceLastBullet = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ClipSize = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RemainingBullets = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTime = 2.f;

	UPROPERTY(EditDefaultsOnly)
	float RealoadTimer = 0.f;

	UPROPERTY(EditAnywhere)
	int BaseSpread = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString WeaponName;

	bool Reloading = false;
	bool Active = false;

	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
};
