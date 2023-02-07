// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UEntityHealth : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticles;

public:	
	// Sets default values for this component's properties
	UEntityHealth();

	void Kill();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(AActor* damagedActor, float damage, const UDamageType* damageType, class AController* instigator, AActor* damageCauser);
		
};
