// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterCharacter.h"
#include "ShooterPlayerController.generated.h"

/**
 *
 */

class AGun;
class UUserWidget;

UCLASS()
class ASSIGNMENT1_PROJECT_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent();
	virtual void MoveForward(float AxisValue);
	virtual void Shoot();
	virtual void MoveRight(float AxisValue);
	virtual void LookRight(float AxisValue);
	virtual void LookUp(float AxisValue);
	AShooterCharacter* MyPawn;

	UFUNCTION(BlueprintPure)
		int GetNumberOfShots();



	UPROPERTY(EditAnywhere)
		int NumberOfShots;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WelcomeClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WelcomeBulletCountClass;



	UPROPERTY()
		AGun* Gun;

	UPROPERTY()
		UUserWidget* WelcomeScreen;

	UPROPERTY()
		UUserWidget* WelcomeBulletCount;



};