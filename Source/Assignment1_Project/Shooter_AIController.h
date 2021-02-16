// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Shooter_AIController.generated.h"

/**
 *
 */
UCLASS()
class ASSIGNMENT1_PROJECT_API AShooter_AIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;


	bool IsInFront(AActor* ActorToCheck);
};