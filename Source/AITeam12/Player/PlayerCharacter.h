//Author Olof Wallentin
//This class was taken from one of his courses and additions to the original code will be documented
//Class, function and variables may have their names changed without documentation

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UTeam12MovementComponent;

UCLASS()
class APlayerCharacter : public APawn
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UTeam12MovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPSCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	virtual void Tick(float DeltaTime) override;

	UCameraComponent* GetFirstPersonCameraComponent() const { return FPSCamera; }
	UCapsuleComponent* GetCapsule() const { return Capsule; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Gravity;

	FVector InputVector = FVector::ZeroVector;
	FVector LookVector = FVector::ZeroVector;

	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
};