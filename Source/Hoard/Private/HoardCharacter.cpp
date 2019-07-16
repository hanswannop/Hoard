// Fill out your copyright notice in the Description page of Project Settings.


#include "HoardCharacter.h"
//#include "Camera/CameraComponent.h"

// Sets default values
AHoardCharacter::AHoardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
//	CameraComp->bUsePawnControlRotation(true);
}

// Called when the game starts or when spawned
void AHoardCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHoardCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AHoardCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

// Called every frame
void AHoardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHoardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHoardCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHoardCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AHoardCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AHoardCharacter::AddControllerYawInput);
}

