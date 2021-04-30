#include "VisionSenseComponent.h"
#include "GameFramework/Actor.h"
#include "VisionSettings.h"
#include "VisionTargetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Team12GameModeBase.h"

UVisionSenseComponent::UVisionSenseComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
	CollisionParams.AddIgnoredActor(GetOwner());
}

void UVisionSenseComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (VisionSetting == nullptr)
		return;

	FVector Direction = GetOwner()->GetActorForwardVector();
	FVector Origin = GetOwner()->GetActorLocation();

	DrawDebug();

	for (int32 Index = SeenTargets.Num() - 1; Index >= 0; --Index) 
	{
		UVisionTargetComponent* CurrentTarget = SeenTargets[Index];

		if(CurrentTarget == nullptr || (CurrentTarget != nullptr && CurrentTarget->IsBeingDestroyed()))
		{
			SeenTargets.RemoveAt(Index);
			continue;
		}

		if(!IsPointVisible(CurrentTarget->GetTargetOrigin(), Origin, Direction, VisionSetting->MinimumDistance))
		{
			FVisionResult Result;
			Result.SeenActor = CurrentTarget->GetOwner();
			OnTargetLost.Broadcast(Result);
			SeenTargets.RemoveAt(Index);
		}
		else 
		{
			if (!LineOfSight(CurrentTarget->GetOwner()))
			{
				FVisionResult Result;
				Result.SeenActor = CurrentTarget->GetOwner();
				OnTargetLost.Broadcast(Result);
				SeenTargets.RemoveAt(Index);
			}
		}
	}

	TArray<UVisionTargetComponent*> ListOfTargets;
	float MinDistanceSquare = FMath::Square(VisionSetting->MinimumDistance);
	auto* GameMode = Cast<ATeam12GameModeBase>(UGameplayStatics::GetGameMode(this));

	for (UVisionTargetComponent* Target : GameMode->VisionTargetList)
	{
		if (Target == nullptr)
			return;

		float DistanceSquare = FVector::DistSquared(Target->GetOwner()->GetActorLocation(), Origin);
		if (DistanceSquare < MinDistanceSquare)
		{
			ListOfTargets.Add(Target);
		}
	}

	for (UVisionTargetComponent* Target :ListOfTargets)
	{
		if(!SeenTargets.Contains(Target) && IsPointVisible(Target->GetTargetOrigin(), Origin, Direction, VisionSetting->MinimumDistance))
		{
			if (LineOfSight(Target->GetOwner()))
			{
				SeenTargets.Add(Target);
				FVisionResult Result;
				Result.SeenActor = Target->GetOwner();
				OnTargetSeen.Broadcast(Result);
			}
		}
	}
}

bool UVisionSenseComponent::IsPointVisible(const FVector& TestPoint, const FVector& Origin, const FVector& Direction, float MinDistance) const
{
	if (VisionSetting == nullptr)
		return false;

	float DistanceMinsq = FMath::Square(MinDistance);

	if (FVector::DistSquared(Origin, TestPoint) > DistanceMinsq)
		return false;

	FVector TargetDirection = (TestPoint - Origin).GetSafeNormal();

	float AsHalfRad = FMath::Cos(FMath::DegreesToRadians(VisionSetting->Angle));
	float Dot = FVector::DotProduct(Direction, TargetDirection);

	return Dot > AsHalfRad;
}

float UVisionSenseComponent::GetVisionInRadians() const
{
	if (VisionSetting == nullptr)
		return 0.0f;

	return FMath::Cos(FMath::DegreesToRadians(VisionSetting->Angle));
}

void UVisionSenseComponent::CheckLineOfSight()
{
	if (SeenTargets.Num() <= 0)
		return;

	for (int i = SeenTargets.Num(); i > 0; i--)
	{
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = SeenTargets[i - 1]->GetTargetOrigin();
	}
}

bool UVisionSenseComponent::LineOfSight(AActor* Target) 
{
	FHitResult Hit;
	FVector Start = GetOwner()->GetActorLocation();
	GetWorld()->LineTraceSingleByChannel(Hit, Start, Target->GetActorLocation(), ECC_Visibility, CollisionParams);
	if(Hit.bBlockingHit)
	{
		if (Hit.GetActor() != Target)
			return false;
	}
	return true;
}

void UVisionSenseComponent::DrawDebug() 
{
	if (!bDrawVisionDebug)
		return;

		FVector Direction = GetOwner()->GetActorForwardVector();
		FVector Origin = GetOwner()->GetActorLocation();
		FVector Right = Direction.RotateAngleAxis(VisionSetting->Angle, FVector::UpVector);
		FVector Left = Direction.RotateAngleAxis(-VisionSetting->Angle, FVector::UpVector);

		FLinearColor tempColor;
		if (SeenTargets.Num() > 0)
			tempColor = FLinearColor::Green;
		else
			tempColor = FLinearColor::Red;

		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, Origin + Right * VisionSetting->MinimumDistance, tempColor);
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, Origin + Left * VisionSetting->MinimumDistance, tempColor);
}