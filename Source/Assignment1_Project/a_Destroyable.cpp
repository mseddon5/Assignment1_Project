// Fill out your copyright notice in the Description page of Project Settings.


#include "a_Destroyable.h"

// Sets default values
Aa_Destroyable::Aa_Destroyable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aa_Destroyable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aa_Destroyable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

