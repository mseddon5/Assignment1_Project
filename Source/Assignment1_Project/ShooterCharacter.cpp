// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"
#include "Assignment1_ProjectGameModeBase.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	myCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	ActorMesh->SetCollisionProfileName(TEXT("Pawn"));

	ActorMesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint->SetupAttachment(ActorMesh);
	springArm->SetupAttachment(ActorMesh);
	myCamera->SetupAttachment(springArm, USpringArmComponent::SocketName);

	springArm->TargetArmLength = 300.0f;
	springArm->bEnableCameraLag = true;
	springArm->CameraLagSpeed = 1.0f;
	springArm->CameraLagMaxDistance = 1.5f;

	springArm->SetRelativeRotation(FRotator(-45.0f, 0.f, 0.f));
	ProjectileSpawnPoint->SetRelativeLocation(FVector(36.0f, 38.0f, 64.0f));




}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	gameModeRef = Cast<AAssignment1_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
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
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);
	
	gameModeRef->ShotsHit();
	return DamageToApply;
}
	

void AShooterCharacter::MoveForward(float AxisValue)
{

	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{

	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::Shoot()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
	Gun->PullTrigger();
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUp(float AxisValue)
{
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
	if (GrenadeClass) { //checks teabag projectile has been set in the editor
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		APlayerGrenade* TempNade = GetWorld()->SpawnActor<APlayerGrenade>(GrenadeClass, SpawnLocation, SpawnRotation);
		TempNade->SetOwner(this);
	}
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}