// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Assignment1_ProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	

	/*Mesh.AddDynamic(this, &AGun::PullTrigger);*/
}

void AGun::PullTrigger(/*AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& HitResult*/)
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;


	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		AActor* ProjectileOwner = GetOwner();
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			//FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			//HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			/*CallShotHit->ShotsHit();*/
			UGameplayStatics::ApplyDamage(
				HitActor, //actor that will be damaged
				gameDamage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //Controller that was responsible for causing the damage
				this, //actor that actually caused the damage
				UDamageType::StaticClass()
				
			);
			
		}
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

