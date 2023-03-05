// Copyright Epic Games, Inc. All Rights Reserved.

#include "TanksGameMode.h"
#include "Entities/Tank.h"
#include "EntityHealth.h"
#include <Kismet/GameplayStatics.h>

void ATanksGameMode::BeginPlay()
{
	TArray<AActor*> tanks;
	UGameplayStatics::GetAllActorsOfClass(this, AActor::StaticClass(), tanks);
	tankCount = tanks.Num();

	for (int i = 0; i < tanks.Num(); i++)
	{
		UEntityHealth* health = tanks[i]->FindComponentByClass<UEntityHealth>();
		if (health)
		{
			health->OnDeath.AddDynamic(this, &ATanksGameMode::OnActorDeath);
		}
	}
}