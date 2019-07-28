// Fill out your copyright notice in the Description page of Project Settings.


#include "HWeaponGrenadeLauncher.h"
#include "Kismet/GameplayStatics.h"
#include "HProjectile.h"

void AHWeaponGrenadeLauncher::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		// try and fire a projectile
		if (ProjectileClass)
		{
			FVector MuzzleLocation = MeshComp->GetSocketLocation("MuzzleSocket");
			FRotator MuzzleRotation = MeshComp->GetSocketRotation("MuzzleSocket");

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorSpawnParams.Instigator = ;

			// spawn the projectile at the muzzle
			GetWorld()->SpawnActor<AHProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);
		}
	}
}
