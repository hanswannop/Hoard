// Fill out your copyright notice in the Description page of Project Settings.


#include "HWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHWeapon::AHWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AHWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AHWeapon::Fire()
{
	// Trace the world from pawn eyes to crosshair location
	
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility))
		{
			// Apply damage

		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Cyan, false, 1.0f, 0, 1.0f);

	}
}

// Called every frame
void AHWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}