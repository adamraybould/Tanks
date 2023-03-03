// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityHealth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathSignature, AActor*, killedActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UEntityHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Damage")
	FDeathSignature OnDeath;

private:
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* DeathParticles;

public:	
	// Sets default values for this component's properties
	UEntityHealth();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BLueprintCallable)
	void Kill();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(AActor* damagedActor, float damage, const UDamageType* damageType, class AController* instigator, AActor* damageCauser);
};
