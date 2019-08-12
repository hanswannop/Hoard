// Fill out your copyright notice in the Description page of Project Settings.


#include "HProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHProjectile::AHProjectile()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 5.0f;

	TimeBeforeExplode = 1.0f;
	BaseDamage = 150.0f;
	DamageRadius = 300.0f;

	ExplosionSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphereComp"));
	ExplosionSphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	ExplosionSphereComp->SetSphereRadius(DamageRadius);
	ExplosionSphereComp->SetupAttachment(MeshComp);

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AHProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ExplodeTimerHandle, this, &AHProjectile::Explode, TimeBeforeExplode, false);
}

void AHProjectile::Explode()
{
	if (ExplodeEffect) {
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeEffect, this->GetActorLocation());
		UGameplayStatics::ApplyRadialDamage(this, BaseDamage, this->GetActorLocation(), DamageRadius, DamageType, IgnoreActors);
		
		TArray<UPrimitiveComponent*> ComponentsToRappel;
		ExplosionSphereComp->GetOverlappingComponents(ComponentsToRappel);

		for (auto& PrimComp : ComponentsToRappel)
		{
			if (PrimComp && PrimComp->IsSimulatingPhysics())
			{
				const float SphereRadius = ExplosionSphereComp->GetScaledSphereRadius();
				const float ForceStrength = 30000;

				PrimComp->AddRadialImpulse(this->GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}

		DrawDebugSphere(GetWorld(), this->GetActorLocation(), DamageRadius, 12, FColor::Orange, false, 1.0f);

		Destroy();
	}
	
}
