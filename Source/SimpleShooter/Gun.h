// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;
class APawn;
class AController;

struct FShootData {
	FVector StartLocation;
	FRotator StartRotation;
	FVector EndLocation;
	FVector OppositeDirection;
	FRotator OppositeRotation;
	FHitResult HitResult;
	bool HasHit;

	FShootData(UWorld* World, AController* Controller, float Range)
	{
		Controller->GetPlayerViewPoint(StartLocation, StartRotation);
		EndLocation = StartLocation + StartRotation.Vector() * Range;
		OppositeDirection = -StartRotation.Vector();
		OppositeRotation = OppositeDirection.Rotation();

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Controller->GetPawn());
		// ECC_GameTraceChannel1: Created new trace channel. Verify in DefaultEngine.ini what is the channel name assigned to it.
		HasHit = World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, CollisionParams);
	}
};

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	void SetupController();

private:
	bool HasNullPointers() const;

	void PlayMuzzleEffects() const;

	void PlayHitEffects(FShootData& ShootData) const;

	void DealDamage(FShootData& ShootData);

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleEffect = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* HitWorldEffect = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MuzzleSound = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	USoundBase* HitWorldSound = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	AController* OwnerController = nullptr;
};
