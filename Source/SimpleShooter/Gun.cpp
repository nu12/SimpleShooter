// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (!OwnerController)
	{
		APawn* GunOwner = Cast<APawn>(GetOwner());
		if (GunOwner)
		{
			OwnerController = GunOwner->GetController();
		}
	}

	if (HasNullPointers()) return;
	
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComponent, FName(TEXT("MuzzleFlashSocket")));

	FVector ViewPointLocation;  // out
	FRotator ViewPointRotation; // out

	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
	FHitResult HitResult;

	// ECC_GameTraceChannel1: Created new trace channel. Verify in DefaultEngine.ini what is the channel name assigned to it.
	GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, LineTraceEnd, ECC_GameTraceChannel1);

	if(bDrawDebugHelpers)
	{
		DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10.f, FColor::Red, true);
	}

	// Invert the direction of the effect: the effect should be spawned towards the player camera.
	FVector OppositeDirection = -ViewPointRotation.Vector();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldEffect, HitResult.ImpactPoint, OppositeDirection.Rotation());

}

bool AGun::HasNullPointers() const
{
	if (!MuzzleEffect)
	{
		UE_LOG(LogTemp, Error, TEXT("Muzzle effect not found!"));
		return true;
	}

	if (!HitWorldEffect)
	{
		UE_LOG(LogTemp, Error, TEXT("HitWorld effect not found!"));
		return true;
	}

	if (!OwnerController)
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerController not found!"));
		return true;
	}

	return false;
}