// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGrenade.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ShooterCharacter.h"
// Sets default values
APlayerGrenade::APlayerGrenade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creates the default subobjects
	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Mesh"));
	GrenadeMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Grenade Movement"));

	//sets the Grenade mesh as the root component
	SetRootComponent(GrenadeMesh);

	//makes the grenade simuulate physics in game. Also enables rigid body collisions
	GrenadeMesh->SetSimulatePhysics(true);
	GrenadeMesh->SetNotifyRigidBodyCollision(true);

	//sets the initial and maximum speed of the grenade
	GrenadeMovement->MaxSpeed = MovementSpeed;
	GrenadeMovement->InitialSpeed = MovementSpeed;
	

	InitialLifeSpan = 6.0f;

}

// Called when the game starts or when spawned
void APlayerGrenade::BeginPlay()
{
	Super::BeginPlay();
	//adds a dynamic delegate for the OnHit function
	OnActorHit.AddDynamic(this, &APlayerGrenade::OnHit);
}

// Called every frame
void APlayerGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerGrenade::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

	//sets the projectile owner. Does a basic nullptr check to avoid UE4 issues
	AActor* ProjectileOwner = GetOwner();
	if (!ProjectileOwner) {
		return;
	}

	//if the actor that will be damaged is a child of AShooterCharacter (if the grenade hits the player and not a random actor on the map) returns true
	if (OtherActor->GetClass()->IsChildOf(AShooterCharacter::StaticClass()))
	{
		// if the actor that will be damaged isnt the same actor as the one causing the damage (So the player cant kill themself) returns true
		if (OtherActor != GetOwner())
		{
			//applies damage as follows:
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				Damage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //Controller that was responsible for causing the damage
				GetOwner(), //actor that actually caused the damage
				UDamageType::StaticClass()
			);
		}
		//destroys the grenade after any collision with a chold of AShooterCharacter (player or AI)
		Destroy();
	}

}