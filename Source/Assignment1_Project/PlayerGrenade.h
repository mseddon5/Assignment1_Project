// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerGrenade.generated.h"

UCLASS()
class ASSIGNMENT1_PROJECT_API APlayerGrenade : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* GrenadeMesh;

	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* GrenadeMovement;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
		float Damage = 10.0f;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};