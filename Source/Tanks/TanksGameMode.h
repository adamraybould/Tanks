// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMissionStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMissionComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMissionFailed);

UCLASS()
class ATanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FMissionStart OnMissionStart;

	UPROPERTY(BlueprintAssignable)
	FMissionComplete OnMissionComplete;

	UPROPERTY(BlueprintAssignable)
	FMissionFailed OnMissionFailed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int playerLives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentMission = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int tankCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isMissionReady;

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> missions;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ATank>> enemyTanks;

public:
	UFUNCTION(BlueprintCallable)
	void StartMission(int mission);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class ATank> GetTank(ETankType tankType);

	bool CanPerformAction();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateMission(TSubclassOf<AActor> mission);

	UFUNCTION()
	void OnActorDeath(AActor* killedActor);

	UFUNCTION(BlueprintCallable)
	void MissionComplete();

	UFUNCTION(BlueprintCallable)
	void MissionFailed();
};



