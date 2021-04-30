#include "PacManPlayer.h"
#include "CustomComponents/Vision/VisionTargetComponent.h"
#include "Weapon/BaseBullet.h"
#include "CustomComponents/Health/HealthComponent.h"
#include "Camera/CameraComponent.h"

APacManPlayer::APacManPlayer()
{
	//Super::APlayerCharacter();

	VisionTarget = CreateDefaultSubobject<UVisionTargetComponent>(TEXT("Vision Target"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	HealthComponent->OnTakeDamage.AddDynamic(this, &APacManPlayer::OnDamageTaken);
}

void APacManPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APacManPlayer::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
}

void APacManPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APacManPlayer::OnFire);
}
void APacManPlayer::OnFire()
{
	if (CurrentAmmo > 0)
	{
		CurrentAmmo--;
		FTransform FireTrans;
		FireTrans.SetLocation(FPSCamera->GetComponentLocation() + FPSCamera->GetForwardVector() * 50.f);
		FireTrans.SetRotation(FPSCamera->GetComponentQuat());

		GetWorld()->SpawnActor<ABaseBullet>(BulletType, FireTrans);
		PlayerFire();
	}
}
void APacManPlayer::OnDamageTaken(float Damage) 
{
	HealthComponent->Health -= Damage;
	if (HealthComponent->Health <= 0)
	{
		PlayerGameOver();
	}
}

void APacManPlayer::IncreaseAmmo()
{
	CurrentAmmo++;
	CurrentScore++;
	AmmoIncrease();
	if (CurrentScore >= MaxScore)
		PlayerWin();
}