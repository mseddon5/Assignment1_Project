// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Waypoints.h"
#include "Shooter_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Assignment1_ProjectGameModeBase.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sets the default subobjects
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Map Arm"));
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	myCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mapComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Map Component"));

	//attaches the component to their relavent components
	ActorMesh->SetupAttachment(RootComponent);
	mapComponent->SetupAttachment(mapArm);
	ProjectileSpawnPoint->SetupAttachment(ActorMesh);
	springArm->SetupAttachment(ActorMesh);
	mapArm->SetupAttachment(ActorMesh);
	myCamera->SetupAttachment(springArm, USpringArmComponent::SocketName);

	ActorMesh->SetCollisionProfileName(TEXT("Pawn"));

	//sets the spring arm up to match what a third person shooter should be
	springArm->TargetArmLength = TargetArmLengthVariable;
	springArm->bEnableCameraLag = true;
	springArm->CameraLagSpeed = LagSpeedVariable;
	springArm->CameraLagMaxDistance = CameraLagMaxDistanceVariable;

	//sets the relative locations and rotations
	springArm->SetRelativeRotation(SpringArmRelativeRotation);
	ProjectileSpawnPoint->SetRelativeLocation(ProjectileSpawnPointRelativeLocation);
	mapArm->SetRelativeRotation(MapArmRelativeRotation);

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//hides the bones in the skeletal mesh to allow for our own gun to be added
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	//
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);


	gameModeRef = Cast<AAssignment1_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));


	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoints::StaticClass(), Waypoints);
	//MoveToWaypoints();
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &AShooterCharacter::OnEndFire);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//sets variable
	DamagePawn = Cast <APawn>(DamageCauser);

	//if the pawn that was damaged was player controlled, returns true, if not, returns false
	if (DamagePawn->IsPlayerControlled())
	{
		//calls function in the game mode (Player)
		gameModeRef->ShotsHit();
	}
	else
	{
		//calls function in the game mode (AI)
		gameModeRef->AIShotsHit();
	}

	//takes the damage amount away from current HP. Returns the amount of damage.
	Health -= DamageAmount;
	return DamageAmount;

}



void AShooterCharacter::MoveForward(float AxisValue)
{
	//multiplies the forward vector by the function parameter
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	//multiplies the right vector by the function parameter
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::Shoot()
{
	//plays a sound at the instigators location, then calls the pulltrigger function inside Gun
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation(), VolumeVariable, PitchVariable, StartTimeVariable);
	Gun->PullTrigger();
}

void AShooterCharacter::LookRight(float AxisValue)
{
	//multiplies the values together to calculate how much to look right
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUp(float AxisValue)
{
	//creates a temporary variable that contains the current pitch rotation plus the function variable
	// if the result is in range of the conditions, then returns true (stops the player to infinitly look up/down
	float rotTemp = springArm->GetRelativeRotation().Pitch + AxisValue;
	if (rotTemp < 30 && rotTemp > -70)
	{
		springArm->AddLocalRotation(FRotator(AxisValue, 0.0f, 0.0f));
	}

}
void AShooterCharacter::OnBeginFire()
{

}

void AShooterCharacter::OnEndFire()
{
	if (GrenadeClass) { //checks grenade projectile has been set in the editor
		//sets the spawn location and rotation
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		//spawns a grenade and sets the owner to the controller
		APlayerGrenade* TempNade = GetWorld()->SpawnActor<APlayerGrenade>(GrenadeClass, SpawnLocation, SpawnRotation);
		TempNade->SetOwner(this);
	}
}

bool AShooterCharacter::IsDead() const
{
	//bool used to check if the player or AI is dead
	return Health <= 0;
}
