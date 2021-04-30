#include "Weapon.h"
#include "BaseBullet.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseTrans"));
	Box->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Box;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(Box);

	GunPipe = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	GunPipe->SetupAttachment(WeaponMesh);
	TimeSinceLastBullet = 1 / FireRate;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Reloading)
	{
		RealoadTimer += DeltaTime;
		if (RealoadTimer >= ReloadTime)
		{
			Reloading = false;
			RemainingBullets = ClipSize;
			TimeSinceLastBullet = FireRate;
			UE_LOG(LogTemp, Log, TEXT("Reload Done"));
		}
	}
	else
	{
		TimeSinceLastBullet += DeltaTime;
	}
}

void AWeapon::Fire(FTransform FirePoint)
{
	if (TimeSinceLastBullet > 1 /FireRate)
	{
		TimeSinceLastBullet = 0.f;
		RemainingBullets--;
		GetWorld()->SpawnActor<ABaseBullet>(BulletType, FirePoint);
		OnFire();
		if (RemainingBullets <= 0.f)
		{
			Reload();
		}
	}
}

void AWeapon::Reload()
{
	OnReload();
	UE_LOG(LogTemp, Log, TEXT("Starting Reload"));
	RealoadTimer = 0.f;
	Reloading = true;
}

void AWeapon::Activate(bool Status)
{
	SetActorHiddenInGame(!Status);
	SetActorEnableCollision(Status);
	SetActorTickEnabled(Status);
}

void AWeapon::Drop()
{
	Active = false;
	Box->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Box->SetSimulatePhysics(true);
	Box->UpdateCollisionProfile();
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AWeapon::PickUp()
{
	Active = true;
	Box->SetSimulatePhysics(false);
	Box->SetCollisionProfileName(TEXT("NoCollision"));
}