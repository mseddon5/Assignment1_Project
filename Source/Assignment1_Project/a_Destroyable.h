// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "a_Destroyable.generated.h"

UCLASS()
class ASSIGNMENT1_PROJECT_API Aa_Destroyable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aa_Destroyable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
