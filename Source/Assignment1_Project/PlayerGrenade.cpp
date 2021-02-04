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

	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Mesh"));
	GrenadeMesh->SetSimulatePhysics(true);
	SetRootComponent(GrenadeMesh);
	GrenadeMesh->SetNotifyRigidBodyCollision(true);

	GrenadeMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Grenade Movement"));
	GrenadeMovement->MaxSpeed = MovementSpeed;
	GrenadeMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 6.0f;
}

// Called when the game starts or when spawned
void APlayerGrenade::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &APlayerGrenade::OnHit);
}

// Called every frame
void APlayerGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerGrenade::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner();

	if (!ProjectileOwner) {
		//UE_LOG Error
		return;
	}

	if (OtherActor->GetClass()->IsChildOf(AShooterCharacter::StaticClass()))
	{
		
		if (OtherActor != GetOwner())
		{
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				Damage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //Controller that was responsible for causing the damage
				GetOwner(), //actor that actually caused the damage
				UDamageType::StaticClass()
			);
		}
		Destroy();
	}
	
}

