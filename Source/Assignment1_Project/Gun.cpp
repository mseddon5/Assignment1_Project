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

// Called when the game starts or when spawned. Sets the gamemode reference used throught code.
void AGun::BeginPlay()
{
	Super::BeginPlay();
	gameModeRef = Cast<AAssignment1_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AGun::PullTrigger()
{
	//spawns particle system when the player pulls the trigger
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	//casts owner to variable. Does a nullptr check to avoid UE4 issues
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	//sets the controller of OwnerPawn to the variable. Does a nullptr check to avoid UE4 issues.
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	//Gets the ViewPoint of the owner controller using the variables declared as parameters
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//calculates the end point of the raycast using the variables declared above
	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;

	//adds some ignore actor parameters to avoid the player and the AI shooting their own capsules
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	//if the statment returns true, causes a line trace (raycast)
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	//if raycast is successful
	if (bSuccess)
	{
		//gets the direction of the shot
		FVector ShotDirection = -Rotation.Vector();

		//spawns a particle system at the collision point
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

		//gets the owner of the projectile
		AActor* ProjectileOwner = GetOwner();

		//gets the actor that has been hit by the raycast. Does a nullptr check to avoid UE4 issues
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			//applies the damage as follows:
			UGameplayStatics::ApplyDamage(
				HitActor, //actor that will be damaged
				gameDamage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //Controller that was responsible for causing the damage
				GetOwner(), //actor that actually caused the damage
				UDamageType::StaticClass()
			);

			//adds basic physics forces to the raycast
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());
			RootComp->AddImpulse(Rotation.Vector() * ImpulseForce * RootComp->GetMass());

		}
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}