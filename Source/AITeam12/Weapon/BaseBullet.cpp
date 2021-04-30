#include "BaseBullet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ActorComponent.h"
#include "CustomComponents/Health/HealthComponent.h"

ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = Sphere;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(Sphere);
	BulletMesh->SetCollisionProfileName("NoCollision");

}

void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	Velocity = GetActorForwardVector() * ProjectileSpeed;
}

void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Velocity.Z -= 982.f * DeltaTime;
	FHitResult Hit;
	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);
	if (Hit.bBlockingHit)
	{
		BulletHit(Hit);
	}
	FRotator Rot = UKismetMathLibrary::MakeRotFromX(Velocity);
	SetActorRotation(Rot);
}

void ABaseBullet::BulletHit(FHitResult Hit)
{
	OnHit(Hit);
	UHealthComponent* HealthComp = Hit.Actor->FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		HealthComp->OnTakeDamage.Broadcast(Damage);
	}
	Destroy();
	return;
}

