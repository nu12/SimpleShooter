// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;
class APawn;
class AController;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

private:
	bool HasNullPointers() const;


protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere)
	bool bDrawDebugHelpers = false;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComponent = nullptr;
	UPROPERTY(EditAnywhere)
	USceneComponent* Root = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleEffect = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* HitWorldEffect = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000.f;

	AController* OwnerController = nullptr;
};
