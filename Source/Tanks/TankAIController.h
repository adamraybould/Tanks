// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	FVector circleCenter;
	FVector displacement;
	FRotator wanderAngle;

protected:
	class ATank* Tank;
	class UFloatingPawnMovement* PawnMovement;

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	ATankAIController();

	UFUNCTION(BlueprintCallable)
	void Seek(FVector position);

	UFUNCTION(BlueprintCallable)
	void Wander();
};
