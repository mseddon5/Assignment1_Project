// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ShooterCharacter.h"


void AShooterPlayerController::BeginPlay() {
	Super::BeginPlay();

	MyPawn = Cast<AShooterCharacter>(GetPawn());

	WelcomeScreen = CreateWidget(this, WelcomeClass);
	WelcomeBulletCount = CreateWidget(this, WelcomeBulletCountClass);

	if (WelcomeScreen != nullptr)
	{
		WelcomeScreen->AddToViewport();
	}

	if (WelcomeBulletCount != nullptr)
	{
		WelcomeBulletCount->AddToViewport();
	}

}

void AShooterPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterPlayerController::Shoot);
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("LookRight"), this, &AShooterPlayerController::LookRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AShooterPlayerController::LookUp);


}

void AShooterPlayerController::MoveForward(float AxisValue)
{
	if (MyPawn)
	{
		MyPawn->MoveForward(AxisValue);
	}
}

void AShooterPlayerController::MoveRight(float AxisValue)
{
	if (MyPawn)
	{
		MyPawn->MoveRight(AxisValue);
	}
}

void AShooterPlayerController::LookRight(float AxisValue)
{
	if (MyPawn)
	{
		MyPawn->LookRight(AxisValue);
	}
}

void AShooterPlayerController::LookUp(float AxisValue)
{
	if (MyPawn)
	{
		MyPawn->LookUp(AxisValue);
	}
}

void AShooterPlayerController::Shoot()
{
	if (MyPawn)
	{
		NumberOfShots++;
		MyPawn->Shoot();
	}
}

int AShooterPlayerController::GetNumberOfShots()
{
	return NumberOfShots;
}
