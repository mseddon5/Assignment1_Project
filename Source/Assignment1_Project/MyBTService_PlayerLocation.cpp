// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UMyBTService_PlayerLocation::UMyBTService_PlayerLocation()
{
	//gives the node a friendlier name
	NodeName = TEXT("Update Player Location");
}

void UMyBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//sets the Player pawn. Does a nullptr check to avoid UE4 issues
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}

	//sets the blackboard vector component to the location of the variable in parameter
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}