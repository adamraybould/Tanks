// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Entities/Tank.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    player = Cast<ATank>(GetPawn());
}

void ATankPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::ForwardMovement);
    InputComponent->BindAxis("MoveSideways", this, &ATankPlayerController::SidewaysMovement);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult hit;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);

    player->RotateTurret(hit.ImpactPoint);
}

void ATankPlayerController::ForwardMovement(float value)
{
    FVector direction = FVector(value, 0.0f, 0.0f);
    player->Move(direction);
}

void ATankPlayerController::SidewaysMovement(float value)
{
    FVector direction = FVector(0.0f, value, 0.0f);
    player->Move(direction);
}
