#pragma once
#include "Components/ActorComponent.h"
#include "VisionSenseComponent.generated.h"

class AActor;
class UVisionSettings;
class UVisionTargetComponent;

USTRUCT(BlueprintType)
struct FVisionResult
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		AActor* SeenActor = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVisisionResultDelegate, const FVisionResult&, Results);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UVisionSenseComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UVisionSenseComponent();

	TArray<UVisionTargetComponent*> SeenTargets;

	UPROPERTY(EditAnywhere, Category = "Settings")
	UVisionSettings* VisionSetting = nullptr;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDrawVisionDebug = false;

	bool IsPointVisible(const FVector& TestPoint, const FVector& Origin, const FVector& Direction, float MinDistance) const;

	float GetVisionInRadians() const;

	void CheckLineOfSight();

	void DrawDebug();

	bool LineOfSight(AActor* Target);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)
	FVisisionResultDelegate OnTargetSeen;
	UPROPERTY(BlueprintAssignable)
	FVisisionResultDelegate OnTargetLost;

	FCollisionQueryParams CollisionParams;
};