// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ATriggerActor::ATriggerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//cretes the default subobjects
	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Mesh"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	//sets the root component to the mesh variable
	SetRootComponent(TriggerMesh);
	
	CollisionBox->SetBoxExtent(FVector((146.0f, 16.0f, 193.0f)));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CollisionBox->SetupAttachment(TriggerMesh);
}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	//adds dynamic delegates for functions OnOverlapBegin and OnOverlapEnd
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerActor::OnOverlapEnd);
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//plays entry sound at player location
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), TriggerEnterSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
}

void ATriggerActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//plays exit sound at player location
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), TriggerExitSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
}