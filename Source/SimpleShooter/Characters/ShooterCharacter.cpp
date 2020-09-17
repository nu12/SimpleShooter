// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "SimpleShooter/Gun.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(FName(TEXT("weapon_r")), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("WeaponSocket")));
	Gun->SetOwner(this);

	CurrentHealth = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveForward")), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight")), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName(TEXT("LookUp")), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(FName(TEXT("LookUpAtRate")), this, &AShooterCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis(FName(TEXT("LookRight")), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(FName(TEXT("LookRightAtRate")), this, &AShooterCharacter::LookRightAtRate);
	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName(TEXT("Fire")), IE_Pressed, this, &AShooterCharacter::Fire);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth = FMath::Clamp<float>(CurrentHealth - DamageAmount, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (!GameMode) return DamageAmount;
		GameMode->PawnKilled(this);
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageAmount;
}

bool AShooterCharacter::IsDead() const
{
	return CurrentHealth <= 0.f;
	
}

void AShooterCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AShooterCharacter::LookUpAtRate(float Value)
{ // Make Axis Input Value framerate independent
	AddControllerPitchInput(Value * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightAtRate(float Value)
{ // Make Axis Input Value framerate independent
	AddControllerYawInput(Value * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

float AShooterCharacter::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

void AShooterCharacter::Fire()
{
	Gun->PullTrigger();
}