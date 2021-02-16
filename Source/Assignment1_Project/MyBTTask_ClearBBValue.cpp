// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ClearBBValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_ClearBBValue::UMyBTTask_ClearBBValue()
{
	//gives the node a friendlier name
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UMyBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//clears the value of the blackboard component
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("LastKnownPlayerLocation"));

	//returns task as a success
	return EBTNodeResult::Succeeded;
}
