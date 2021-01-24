// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
void AShooter_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}


void AShooter_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	

	if (LineOfSightTo(PlayerPawn) && IsInFront(PlayerPawn))
	{
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, AcceptanceRadius);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}*/
	
}

bool AShooter_AIController::IsInFront(AActor* ActorToCheck)
{
	//AActor* AIPawn = GetPawn();
	//FVector AIForawdVector = AIPawn->GetActorForwardVector(); //pre normalised
	//FVector PlayerPositionVector = ActorToCheck->GetActorLocation();
	//FVector AIPositionVector = AIPawn->GetActorLocation();
	//FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	//AIToPlayerVector.Normalize(); //dot product works with normalised vectors, therefore we have to normalise this

	//float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForawdVector);

	//if (DirectionDotProduct > 0) return true;
	//else return false;
	return true;
}