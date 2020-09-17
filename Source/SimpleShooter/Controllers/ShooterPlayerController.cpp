// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUDClass);
	if (!HUDWidget) return;
	HUDWidget->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	FTimerHandle RestartTimer;
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

	UUserWidget* Widget = nullptr;
	if (bIsWinner)
	{
		Widget = CreateWidget(this, WinScreenClass);
	}
	else
	{
		Widget = CreateWidget(this, LoseScreenClass);
	}
	
	if(!Widget)return;
	Widget->AddToViewport();

	if (!HUDWidget) return;
	HUDWidget->RemoveFromViewport();
}