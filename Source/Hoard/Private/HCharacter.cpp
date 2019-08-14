// Fill out your copyright notice in the Description page of Project Settings.


#include "HCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "HWeapon.h"

// Sets default values
AHCharacter::AHCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	ZoomedFOV = 65.0F;
	ZoomInterpSpeed = 20;

	WeaponAttachSocketName = "WeaponSocket";
}

// Called when the game starts or when spawned
void AHCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultFOV = CameraComp->FieldOfView;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	//Spawn default weapon
	CurrentWeapon = GetWorld()->SpawnActor<AHWeapon>(DefaultWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}
	
}

void AHCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AHCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AHCharacter::BeginCrouch()
{
	Crouch();
}

void AHCharacter::EndCrouch()
{
	UnCrouch();
}

void AHCharacter::BeginJump()
{
	Jump();
}

void AHCharacter::EndJump()
{
	StopJumping();
}

void AHCharacter::BeginZoom()
{
	bWantsToZoom = true;
}

void AHCharacter::EndZoom()
{
	bWantsToZoom = false;
}

void AHCharacter::Fire()
{
	if (CurrentWeapon) 
	{
		CurrentWeapon->Fire();
	}
}

// Called every frame
void AHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;

	float CurrentFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	CameraComp->SetFieldOfView(CurrentFOV);
}

// Called to bind functionality to input
void AHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AHCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AHCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AHCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AHCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHCharacter::BeginJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHCharacter::EndJump);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AHCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AHCharacter::EndZoom);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHCharacter::Fire);
}

FVector AHCharacter::GetPawnViewLocation() const
{
	if (CameraComp) {
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

