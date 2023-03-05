// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameMode.generated.h"

UCLASS()
class ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int playerLives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int tankCount;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnActorDeath(AActor* killedActor);
};



