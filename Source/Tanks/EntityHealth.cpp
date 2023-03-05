// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityHealth.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UEntityHealth::UEntityHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UEntityHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEntityHealth::Kill()
{
	if (DeathParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DeathParticles, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	}

	OnDeath.Broadcast(GetOwner());

	GetOwner()->SetActorHiddenInGame(true);
	GetOwner()->SetActorEnableCollision(false);
	GetOwner()->SetActorTickEnabled(false);

	IsDead = true;
}

// Called when the game starts
void UEntityHealth::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UEntityHealth::OnHit);
	IsDead = false;
}

void UEntityHealth::OnHit(AActor* damagedActor, float damage, const UDamageType* damageType, class AController* instigator, AActor* damageCauser)
{
	Kill();

	// Destroy the Projectile
	damageCauser->Destroy();
}
