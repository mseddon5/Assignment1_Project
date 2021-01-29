// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Gun.generated.h"
class AAssignment1_ProjectGameModeBase;
UCLASS()
class ASSIGNMENT1_PROJECT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger(/*AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& HitResult*/);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		AAssignment1_ProjectGameModeBase* gameModeRef;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;
	float gameDamage = 10;
};
