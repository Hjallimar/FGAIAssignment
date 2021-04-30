#pragma once
#include "GameFramework/Pawn.h"
#include "AIEnemy.generated.h"

class UHearingSenseComponent;
class UHealthComponent;
class UVisionSenseComponent;
class AActor;
class UStaticMeshComponent;
class UNavMoveComponent;
class UCapsuleComponent;
class USplineComponent;


UCLASS()
class AAIEnemy : public APawn
{
	GENERATED_BODY()
public:
	AAIEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor;

	UFUNCTION()
	void ReciveDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void DamagePlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

	UFUNCTION(BlueprintCallable)
	void UpdateTarget(AActor* Newtarget);

	UFUNCTION(BlueprintCallable)
	FVector GetFollowSplinePoint();

	virtual float GetDefaultHalfHeight() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pathing)
	AActor* SplineActor; 

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UHearingSenseComponent* HearingComponent;

	UPROPERTY(EditAnywhere)
	UVisionSenseComponent* VisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNavMoveComponent* NavigationComponent;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComp;

protected:
	USplineComponent* FollowSpline;
};