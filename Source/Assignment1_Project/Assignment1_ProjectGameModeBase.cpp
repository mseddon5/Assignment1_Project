// Copyright Epic Games, Inc. All Rights Reserved.


#include "Assignment1_ProjectGameModeBase.h"
#include "Shooter_AIController.h"
#include "ShooterPlayerController.h"
#include <Kismet/GameplayStatics.h>

AAssignment1_ProjectGameModeBase::AAssignment1_ProjectGameModeBase() {
	PlayerControllerClass = AShooterPlayerController::StaticClass();

}

void AAssignment1_ProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}


void AAssignment1_ProjectGameModeBase::StartGame()
{
	score = 0;

	GetWorldTimerManager().SetTimer(timerHandle, this, &AAssignment1_ProjectGameModeBase::TimeUp, TimeBeforeSelfDestruct, false, 50.0f);
}

void AAssignment1_ProjectGameModeBase::PawnKilled(APawn* PawnKilled)
{
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		GameOver(false);
	}

	GameOver(true);
}

void AAssignment1_ProjectGameModeBase::ShotsHit()
{
	score++;
	if (score >= TargetPoints)
	{
		GameOver(true);
	}
}

void AAssignment1_ProjectGameModeBase::AIShotsHit()
{
	AIScore++;
	if (AIScore >= TargetPoints)
	{
		GameOver(false);
	}
}
void AAssignment1_ProjectGameModeBase::TimeUp()
{
	GameOver(false);
}

void AAssignment1_ProjectGameModeBase::GameOver(bool PlayerWon)
{
	if (PlayerWon)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "WinLevel");
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), "LoseLevel");
	}
}




