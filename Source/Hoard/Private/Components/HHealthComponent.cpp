// Fill out your copyright notice in the Description page of Project Settings.


#include "HHealthComponent.h"
#include "..\..\Public\Components\HHealthComponent.h"

// Sets default values for this component's properties
UHHealthComponent::UHHealthComponent()
{
	DefaultHealth = 100;
}


// Called when the game starts
void UHHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHHealthComponent::HandleTakeAnyDamage);
	}
	Health = DefaultHealth;	
}

void UHHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauserAA)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s", *FString::SanitizeFloat(Health)));
}
