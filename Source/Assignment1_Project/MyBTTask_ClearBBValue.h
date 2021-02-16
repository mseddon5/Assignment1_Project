// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_ClearBBValue.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT1_PROJECT_API UMyBTTask_ClearBBValue : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UMyBTTask_ClearBBValue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
