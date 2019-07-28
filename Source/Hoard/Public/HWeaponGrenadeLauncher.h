// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HWeapon.h"
#include "HWeaponGrenadeLauncher.generated.h"

class AHProjectile;

UCLASS()
class HORDE_API AHWeaponGrenadeLauncher : public AHWeapon
{
	GENERATED_BODY()
	
protected:

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AHProjectile> ProjectileClass;

	void Fire() override;
};
