// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"
UMyBTTask_Shoot::UMyBTTask_Shoot()
{
	//gives the node a friendlier name
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UMyBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//does a nullptr check to avoid UE4 issues
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//casts the AI to a ShooterCharacter. Does a nullptr check to avoid UE4 issues and then calls AShooterCharacter's Shoot function.
	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		//if nullptr check fails, returns as failed.
		return EBTNodeResult::Failed;
	}
	Character->Shoot();

	//task returns as a success
	return EBTNodeResult::Succeeded;
}