// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityHealth.h"
#include <Perception/AIPerceptionComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UEntityHealth::UEntityHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UEntityHealth::Kill()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	}

	GetOwner()->Destroy();
}

// Called when the game starts
void UEntityHealth::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UEntityHealth::OnHit);
}

void UEntityHealth::OnHit(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* damageCauser)
{
	Kill();
}
