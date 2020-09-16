// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!BehaviorTree) return;
	if (!PlayerPawn) return;
	RunBehaviorTree(BehaviorTree);

	// Needs to add key in Blackboard editor too
	GetBlackboardComponent()->SetValueAsVector(FName(TEXT("StartLocation")), GetPawn()->GetActorLocation());
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!BehaviorTree) return;
	if (!PlayerPawn) return;

	if (LineOfSightTo(PlayerPawn))
	{ // Chase
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PlayerLocation")), PlayerLocation);
		GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LastKnownPlayerLocation")), PlayerLocation);
	}
	else
	{ // Investigate
		GetBlackboardComponent()->ClearValue(FName(TEXT("PlayerLocation")));
	}
}