// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Projectile.h"
#include "Tanks/EntityHealth.h"
#include "Components/AudioComponent.h"
#include <Tanks/TanksGameMode.h>

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(BoxCollider);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BoxCollider);

	LeftTrack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Track Mesh"));
	LeftTrack->SetupAttachment(BaseMesh);

	RightTrack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Track Mesh"));
	RightTrack->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	TurretDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Turret Direction"));
	TurretDirection->SetupAttachment(TurretMesh);

	EntityHealth = CreateDefaultSubobject<UEntityHealth>(TEXT("Entity Health"));
	AddOwnedComponent(EntityHealth);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
	AddOwnedComponent(PawnMovement);

	MovementAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Movement Audio"));
	AddOwnedComponent(MovementAudio);
	MovementAudio->VolumeMultiplier = 0.2f;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	tanksGameMode = Cast<ATanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	EntityHealth->OnDeath.AddDynamic(this, &ATank::OnDeath);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Move(FVector direction)
{
	if (EntityHealth->IsDead || !tanksGameMode->CanPerformAction())
		return;

	PawnMovement->AddInputVector(direction);

	if (PawnMovement->Velocity != FVector::ZeroVector)
	{
		RotateBase(GetActorLocation() + PawnMovement->Velocity);

		// Play Movement Audio if not Already
		if (!MovementAudio->IsPlaying())
		{
			MovementAudio->Play();
		}
	}
	else
	{
		// Stop Movement Audio if Not Moving
		if (MovementAudio->IsPlaying())
		{
			MovementAudio->FadeOut(0.2f, 0.0f);
		}
	}
}

float ATank::RotateBase(FVector direction)
{
	if (EntityHealth->IsDead || !tanksGameMode->CanPerformAction())
		return 0.0f;

	FVector toTarget = direction - GetActorLocation();
	FRotator lookAtRotation = FRotator(0.0f, toTarget.Rotation().Yaw, 0.0f);

	BaseMesh->SetWorldRotation(FMath::RInterpTo(BaseMesh->GetComponentRotation(), lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), rotationSpeed));

	// Gets the Dot Product
	return toTarget.Dot(BaseMesh->GetForwardVector());
}

float ATank::RotateTurret(FVector direction)
{
	if (EntityHealth->IsDead || !tanksGameMode->CanPerformAction())
		return 0.0f;

	FVector toTarget = direction - TurretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.0f, toTarget.Rotation().Yaw, 0.0f);

	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), rotationSpeed));
	//DrawDebugLine(GetWorld(), GetActorLocation(), direction, FColor::Red, false, -1.0f);

	// Gets the Dot Product
	return toTarget.Dot(TurretMesh->GetForwardVector());
}

AActor* ATank::FireBarrelRay()
{
	if (EntityHealth->IsDead || !tanksGameMode->CanPerformAction())
		return nullptr;

	FHitResult* hit = new FHitResult();
	FVector start = ProjectileSpawnPoint->GetComponentLocation();
	FVector end = start + (TurretMesh->GetForwardVector() * 5000.0f);

	FCollisionQueryParams parms;
	parms.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility, parms, FCollisionResponseParams()))
	{
		if (hit->GetActor() != nullptr)
		{
			return hit->GetActor();
		}
	}

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, -1.0f);

	return nullptr;
}

void ATank::OnDeath(AActor* killedTank)
{
	MovementAudio->Stop();
}
