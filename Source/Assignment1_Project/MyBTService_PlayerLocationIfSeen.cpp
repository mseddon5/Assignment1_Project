// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"


UMyBTService_PlayerLocationIfSeen::UMyBTService_PlayerLocationIfSeen()
{
	//gives node a friendlier name
	NodeName = TEXT("Update Player Location If Seen");
}

void UMyBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//sets player pawn, does a nullptr check to avoid UE4 issues
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}

	//does a nullptr check to avoid UE4 issues
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}
	//if the AI has line of sight of the player, sets the blackboard vector component to the player's location. Does a nullptr check to avoid UE4 issues
	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
	else
	{
		//if the AI loses sight of the player (hides around the corner after AI has investigated) clears the value of the blackbaord vector component
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}


}