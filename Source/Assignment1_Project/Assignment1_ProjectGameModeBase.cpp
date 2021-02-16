// Copyright Epic Games, Inc. All Rights Reserved.


#include "Assignment1_ProjectGameModeBase.h"
#include "Shooter_AIController.h"
#include "ShooterPlayerController.h"
#include <Kismet/GameplayStatics.h>

//constructor, sets the PlayerControllerClass to contain a static class of AShooterPlayerController
AAssignment1_ProjectGameModeBase::AAssignment1_ProjectGameModeBase() {
	PlayerControllerClass = AShooterPlayerController::StaticClass();

}
//starts the game
void AAssignment1_ProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

//sets the score to 0 and starts a timer to count down from 50 seconds. When the time is up, calls the AAssignment1_ProjectGameModeBase::TimeUp function.
void AAssignment1_ProjectGameModeBase::StartGame()
{
	GetWorldTimerManager().SetTimer(timerHandle, this, &AAssignment1_ProjectGameModeBase::TimeUp, TimeBeforeSelfDestruct, false, TimeBeforeSelfDestruct);
}

// if the player dies, calls the lose level, if the player wins, calls the win level
void AAssignment1_ProjectGameModeBase::PawnKilled(APawn* PawnKilled)
{
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		GameOver(false);
	}

	GameOver(true);
}

//a counter function. If the player hits 10 shots, calls the win level
void AAssignment1_ProjectGameModeBase::ShotsHit()
{
	score++;
	if (score >= TargetPoints)
	{
		GameOver(true);
	}
}
//a counter function. If the AI hits 10 shots, calls the lose level
void AAssignment1_ProjectGameModeBase::AIShotsHit()
{
	AIScore++;
	if (AIScore >= TargetPoints)
	{
		GameOver(false);
	}
}
//the function referenced in the StartGame function. Calls lose level when time is up.
void AAssignment1_ProjectGameModeBase::TimeUp()
{
	GameOver(false);
}

//function containing the bool results from the prev. functions. 
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