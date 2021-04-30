#include "AIEnemy.h"
#include "CustomComponents/Health/HealthComponent.h"
#include "CustomComponents/Sound/HearingSenseComponent.h"
#include "CustomComponents/Vision/VisionSenseComponent.h"
#include "NavMoveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"

AAIEnemy::AAIEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComp->SetCollisionProfileName("BlockAllDynamics");
	RootComponent = CapsuleComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetupAttachment(CapsuleComp);

	VisionComponent = CreateDefaultSubobject<UVisionSenseComponent>(TEXT("VisionComponent"));
	HearingComponent = CreateDefaultSubobject<UHearingSenseComponent>(TEXT("HearingComponent"));
	NavigationComponent = CreateDefaultSubobject<UNavMoveComponent>(TEXT("NavmeshComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnTakeDamage.AddDynamic(this, &AAIEnemy::ReciveDamage);
}

void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	if(SplineActor != nullptr)
		FollowSpline = SplineActor->FindComponentByClass<USplineComponent>();
}

void AAIEnemy::ReciveDamage(float Damage) 
{
	HealthComponent->Health -= Damage;
	if (HealthComponent->Health <= 0) 
	{
		OnDeath();
	}
}

void AAIEnemy::DamagePlayer()
{
	UHealthComponent* PlayerHealth = TargetActor->FindComponentByClass<UHealthComponent>();
	if (PlayerHealth)
		PlayerHealth->OnTakeDamage.Broadcast(1.0f);
}

void AAIEnemy::UpdateTarget(AActor* Newtarget)
{
	TargetActor = Newtarget;
}

FVector AAIEnemy::GetFollowSplinePoint()
{
	if (FollowSpline != nullptr) 
	{
		float Input = FollowSpline->FindInputKeyClosestToWorldLocation(GetActorLocation());
		float Distance = FollowSpline->GetDistanceAlongSplineAtSplineInputKey(Input) + 200.0f;
		if (Distance > FollowSpline->GetSplineLength())
			Distance -= FollowSpline->GetSplineLength();
		FVector TargetLocation = FollowSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		return TargetLocation;
	}
	return GetActorLocation();
}

float AAIEnemy::GetDefaultHalfHeight() const
{
	return CapsuleComp->GetUnscaledCapsuleHalfHeight();
}