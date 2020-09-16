// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "SimpleShooter/Controllers/ShooterPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	AShooterPlayerController* PlayerController = PawnKilled->GetController<AShooterPlayerController>();

	if (PlayerController)
	{ // Then player was killed
		PlayerController->GameHasEnded(nullptr, false);
	}
}