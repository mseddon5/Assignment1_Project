// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter_AIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooter_AIController::BeginPlay()
{
	Super::BeginPlay();

	//does a nullptr check to avoid UE4 issues
	if (AIBehavior != nullptr)
	{
		//runs the behaviour tree
		RunBehaviorTree(AIBehavior);

		//sets the player pawn
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		//initialises the blackboard vector components at play time
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("WaypointOne"), FVector(-92.0, -663.0f, 11.728275f));
		GetBlackboardComponent()->SetValueAsVector(TEXT("WaypointTwo"), FVector(540.0f, -663.0f, 11.350196f));
	}
}


void AShooter_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

bool AShooter_AIController::IsInFront(AActor* ActorToCheck)
{
	//sets the AI pawn
	AActor* AIPawn = GetPawn();

	//sets the forward vector of the AI to use in a dot product calculation. The result is pre normalised
	FVector AIForawdVector = AIPawn->GetActorForwardVector(); 

	//sets the player position vector
	FVector PlayerPositionVector = ActorToCheck->GetActorLocation();

	//gets the AI location
	FVector AIPositionVector = AIPawn->GetActorLocation();

	//gets the vector between the player and the AI
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;

	//dot product works with normalised vectors, therefore we have to normalise this
	AIToPlayerVector.Normalize(); 

	//does a dot product calculation to get the direction of the player
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForawdVector);

	//if the player is infront, returns true. If not, returns false
	if (DirectionDotProduct > 0) return true;
	else return false;
	return true;
}