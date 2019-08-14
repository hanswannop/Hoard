// Fill out your copyright notice in the Description page of Project Settings.


#include "HWeaponGrenadeLauncher.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "HProjectile.h"



void AHWeaponGrenadeLauncher::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner && ProjectileClass)
	{
			FVector EyeLocation;
			FRotator EyeRotation;
			MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); // Uses first person location by default

			FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


			// spawn the projectile at the muzzle
			GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation, SpawnParams);

			LastFireTime = GetWorld()->TimeSeconds;
	}
}
