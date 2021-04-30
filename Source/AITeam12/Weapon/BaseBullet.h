#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseBullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UFUNCTION(BlueprintImplementableEvent)//Creates a blueprint event
	void OnHit(FHitResult Hit);

protected:
	virtual void BeginPlay() override;
	void BulletHit(FHitResult Hit);
	FVector Velocity;
public:	
	virtual void Tick(float DeltaTime) override;
};
