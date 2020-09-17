// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!BehaviorTree) return;
	RunBehaviorTree(BehaviorTree);

	// Needs to add key in Blackboard editor too
	GetBlackboardComponent()->SetValueAsVector(FName(TEXT("StartLocation")), GetPawn()->GetActorLocation());
}
