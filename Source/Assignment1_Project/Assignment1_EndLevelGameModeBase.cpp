// Fill out your copyright notice in the Description page of Project Settings.


#include "Assignment1_EndLevelGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AAssignment1_EndLevelGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(ResetGameTimer, this, &AAssignment1_EndLevelGameModeBase::TimeUp, ResetTimerVar);
}


void AAssignment1_EndLevelGameModeBase::TimeUp()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Level_1");
}