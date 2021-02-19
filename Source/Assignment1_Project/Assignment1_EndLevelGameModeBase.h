// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Assignment1_EndLevelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT1_PROJECT_API AAssignment1_EndLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle ResetGameTimer;

	UPROPERTY(EditAnywhere)
		float ResetTimerVar = 5.0f;

	UFUNCTION()
		void TimeUp();
};
