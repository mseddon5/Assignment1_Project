// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Assignment1_ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT1_PROJECT_API AAssignment1_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AAssignment1_ProjectGameModeBase();

public:
	UFUNCTION()
	void ShotsHit();
	UFUNCTION()
	void AIShotsHit();
	UFUNCTION()
	void TimeUp();
	UFUNCTION()
	void GameOver(bool PlayerWon);
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void PawnKilled(APawn* PawnKilled);
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int TargetPoints = 10;

	float TimeBeforeSelfDestruct = 10.0f;

	int score = 0;
	int AIScore = 0;

	FTimerHandle timerHandle;
};
