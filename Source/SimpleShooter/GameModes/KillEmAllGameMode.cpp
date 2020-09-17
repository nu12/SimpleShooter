// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "SimpleShooter/Controllers/ShooterPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	AController* PawnKilledController = PawnKilled->GetController();

	if (!PawnKilledController) return;
	if (PawnKilledController->IsPlayerController())
	{ // Then player was killed
		EndGame(false);
		return;
	}

	int32 EnemyAILeft = 0;
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(Controller == PawnKilledController) continue;
		EnemyAILeft++;
	}
	
	if (EnemyAILeft <= 0 ) EndGame(true);
}


void AKillEmAllGameMode::EndGame(bool IsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()) )
	{ 
		bool IsWinner = Controller->IsPlayerController() == IsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), IsWinner);
	}
}