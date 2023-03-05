// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UParticleSystemComponent* TrailParticles;

	// Particles
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* BounceParticles;

	//Audio
	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* BounceSound;

	// Propeties
	UPROPERTY(EditAnywhere, Category = "Combat");
	int damage;

	UPROPERTY(EditAnywhere, Category = "Movement");
	int maxBounceCount = 1;
	int bounces = 0;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
};
