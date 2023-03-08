// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"
#include <Tanks/Entities/Tank.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = 1300.0f;
	ProjectileMovement->InitialSpeed = 1300.0f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	// On Fired
	if (FireSound)
	{
		UGameplayStatics::PlaySound2D(this, FireSound);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	AActor* owner = GetOwner();
	if (owner == nullptr)
		return;

	if (otherActor)
	{
		if (Cast<ATank>(otherActor))
		{
			UGameplayStatics::ApplyDamage(otherActor, damage, owner->GetInstigatorController(), this, UDamageType::StaticClass());
			Destroy();
		}
		else
		{
			SetActorRotation(ProjectileMovement->Velocity.Rotation());
			bounces++;

			if (bounces >= maxBounceCount)
			{
				if (HitParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
				}

				if (HitSound)
				{
					UGameplayStatics::PlaySound2D(this, HitSound);
				}

				Destroy();
			}
			else
			{
				if (BounceParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(this, BounceParticles, GetActorLocation(), GetActorRotation());
				}

				if (BounceSound)
				{
					UGameplayStatics::PlaySound2D(this, BounceSound);
				}
			}
		}
	}
}


