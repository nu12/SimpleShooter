// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

class APawn;

UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool IsPlayerWinner);
};
