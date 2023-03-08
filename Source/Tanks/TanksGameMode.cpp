// Copyright Epic Games, Inc. All Rights Reserved.

#include "TanksGameMode.h"
#include "Entities/Tank.h"
#include "EntityHealth.h"
#include <Kismet/GameplayStatics.h>

void ATanksGameMode::StartMission(int mission)
{
	// This is called via Blueprints to create the Mission.
	TSubclassOf<AActor> missionPrefab = missions[mission - 1];
	CreateMission(missionPrefab);

	// Get Number of Tanks and Assign OnActorDeath calls to them.
	TArray<AActor*> tanks;
	UGameplayStatics::GetAllActorsOfClass(this, ATank::StaticClass(), tanks);
	tankCount = tanks.Num() - 1;

	for (int i = 0; i < tanks.Num(); i++)
	{
		UEntityHealth* health = tanks[i]->FindComponentByClass<UEntityHealth>();
		if (health)
		{
			health->OnDeath.AddDynamic(this, &ATanksGameMode::OnActorDeath);
		}
	}

	OnMissionStart.Broadcast();
}

TSubclassOf<ATank> ATanksGameMode::GetTank(ETankType tankType)
{
	for (int i = 0; i < enemyTanks.Num(); i++)
	{
		ATank* tank = Cast<ATank>(enemyTanks[i]->GetDefaultObject());
		if (tank)
		{
			if (tank->TankType == tankType)
				return enemyTanks[i];
		}
	}

	return nullptr;
}

bool ATanksGameMode::CanPerformAction()
{
	return isMissionReady;
}

void ATanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartMission(currentMission);
}

void ATanksGameMode::OnActorDeath(AActor* killedActor)
{
	// If the Player is Killed, Mission Failed.
	if (Cast<ATank>(killedActor)->TankType == ETankType::TANK_PLAYER)
	{
		MissionFailed();
	}
	else
	{
		score++;

		tankCount--;
		if (tankCount <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
			MissionComplete();
		}
	}
}

void ATanksGameMode::MissionComplete()
{
	OnMissionComplete.Broadcast();
	isMissionReady = false;
}

void ATanksGameMode::MissionFailed()
{
	OnMissionFailed.Broadcast();
	isMissionReady = false;
}
