// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Entities/Tank.h"
#include "GameFramework/FloatingPawnMovement.h"

ATankAIController::ATankAIController()
{
	
}

void ATankAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Tank = Cast<ATank>(InPawn);
	PawnMovement = Tank->FindComponentByClass<UFloatingPawnMovement>();
}

void ATankAIController::Seek(FVector position)
{
	FVector direction = (position - GetPawn()->GetActorLocation());
	direction.Normalize();

	Tank->Move(direction);
}

void ATankAIController::Wander()
{
	// Calculate Circle Position
	circleCenter = PawnMovement->Velocity;
	circleCenter.Normalize();
	circleCenter *= 5.0f;

	// Displacement Force
	displacement = FVector(0.0f, -1.0f, 0.0f);
	displacement *= 5.0f;

	displacement = wanderAngle.RotateVector(displacement);
	wanderAngle.Yaw += FMath::Rand() * 0.1f - 0.1f * 0.5f;

	FVector direction = circleCenter + displacement;
	direction.Normalize();
	Tank->Move(direction);
}
