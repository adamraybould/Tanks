// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/FloatingPawnMovement.h"

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
	TurretMesh->SetupAttachment(BaseMesh);

	LeftTrack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Track Mesh"));
	LeftTrack->SetupAttachment(BaseMesh);

	RightTrack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Track Mesh"));
	RightTrack->SetupAttachment(BaseMesh);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
	AddOwnedComponent(PawnMovement);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
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
	PawnMovement->AddInputVector(direction);

	if (PawnMovement->Velocity != FVector::ZeroVector)
	{
		movementDirection = GetActorLocation() + PawnMovement->Velocity;
		RotateBase(movementDirection);
	}
}

void ATank::RotateBase(FVector direction)
{
	FVector toTarget = direction - GetActorLocation();
	FRotator lookAtRotation = FRotator(0.0f, toTarget.Rotation().Yaw, 0.0f);

	BaseMesh->SetWorldRotation(FMath::RInterpTo(BaseMesh->GetComponentRotation(), lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), rotationSpeed));
}

void ATank::RotateTurret(FVector direction)
{
	FVector toTarget = direction - TurretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.0f, toTarget.Rotation().Yaw, 0.0f);

	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), rotationSpeed));
	DrawDebugLine(GetWorld(), GetActorLocation(), direction, FColor::Red, false, -1.0f);
}