// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter_AIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooter_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("WaypointOne"), FVector(-127.0f,  -708.0f, -0.651672f));
		GetBlackboardComponent()->SetValueAsVector(TEXT("WaypointTwo"), FVector(534.0f, -708.0f, -0.651415f));
	}
}


void AShooter_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

bool AShooter_AIController::IsInFront(AActor* ActorToCheck)
{
	AActor* AIPawn = GetPawn();
	FVector AIForawdVector = AIPawn->GetActorForwardVector(); //pre normalised
	FVector PlayerPositionVector = ActorToCheck->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	AIToPlayerVector.Normalize(); //dot product works with normalised vectors, therefore we have to normalise this

	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForawdVector);

	if (DirectionDotProduct > 0) return true;
	else return false;
	return true;
}

//void AShooter_AIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
//{
//	AShooterCharacter* EnemyAI = Cast<AShooterCharacter>(GetPawn());
//
//	if (EnemyAI)
//	{
//		EnemyAI->MoveToWaypoints();
//	}
//}