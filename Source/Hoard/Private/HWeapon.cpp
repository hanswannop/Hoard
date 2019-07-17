// Fill out your copyright notice in the Description page of Project Settings.


#include "HWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AHWeapon::AHWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);
}

// Called when the game starts or when spawned
void AHWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}