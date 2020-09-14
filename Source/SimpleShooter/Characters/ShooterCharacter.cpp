// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

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