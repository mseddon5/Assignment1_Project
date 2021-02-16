// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerGrenade.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShooterCharacter.generated.h"

class AGun;
class APawn;
class AAssignment1_ProjectGameModeBase;
class USceneCaptureComponent2D;

UCLASS()
class ASSIGNMENT1_PROJECT_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController*
		EventInstigator, AActor* DamageCauser) override;
	//UFUNCTION()
	//void MoveToWaypoints();

	UFUNCTION()
		void MoveForward(float AxisValue);

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION()
		void MoveRight(float AxisValue);

	UFUNCTION()
		void LookRight(float AxisValue);

	UFUNCTION()
		void LookUp(float AxisValue);

	UFUNCTION()
		void Shoot();

	UFUNCTION()
		void OnBeginFire();

	UFUNCTION()
		void OnEndFire();
private:
	UPROPERTY()
		AAssignment1_ProjectGameModeBase* gameModeRef;

	UPROPERTY(EditAnywhere)
		USoundBase* ShootSound;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ActorMesh;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
		UCameraComponent* myCamera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* mapArm;

	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* mapComponent;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 500.f;

	UPROPERTY(EditAnywhere)
		float TargetArmLengthVariable = 300.0f;

	UPROPERTY(EditAnywhere)
		float LagSpeedVariable = 1.0f;

	UPROPERTY(EditAnywhere)
		float CameraLagMaxDistanceVariable = 1.5f;

	UPROPERTY(EditAnywhere)
		FRotator SpringArmRelativeRotation = FRotator(-45.0f, 0.f, 0.f);

	UPROPERTY(EditAnywhere)
		FVector ProjectileSpawnPointRelativeLocation = FVector(36.0f, 38.0f, 64.0f);

	UPROPERTY(EditAnywhere)
		FRotator MapArmRelativeRotation = FRotator(-90.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
		float VolumeVariable = 1.0f;

	UPROPERTY(EditAnywhere)
		float PitchVariable = 1.0f;

	UPROPERTY(EditAnywhere)
		float StartTimeVariable = 0.0f;

	UPROPERTY(EditAnywhere)
		float RotationSpeed = 200.f;

	UPROPERTY(EditAnywhere)
		float RotationRate = 10.0f;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APlayerGrenade> GrenadeClass;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float Health = MaxHealth;

	UPROPERTY()
		AGun* Gun;

	UPROPERTY()
		APawn* DamagePawn;
};