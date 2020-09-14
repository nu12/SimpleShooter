// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

	void PullTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComponent = nullptr;
	UPROPERTY(EditAnywhere)
	USceneComponent* Root = nullptr;
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleEffect = nullptr;
};
