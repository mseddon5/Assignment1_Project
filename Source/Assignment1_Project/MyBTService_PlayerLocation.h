// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT1_PROJECT_API UMyBTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UMyBTService_PlayerLocation();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
