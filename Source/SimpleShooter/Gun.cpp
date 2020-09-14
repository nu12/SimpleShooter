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

	// DrawDegubCamera
	//DrawDebugCamera(const UWorld* InWorld, FVector const& Location, FRotator const& Rotation, float FOVDeg, float Scale=1.f, FColor const& Color=FColor::White, bool bPersistentLines=false, float LifeTime=-1.f, uint8 DepthPriority = 0);
	FVector ViewPointLocation;  // out
	FRotator ViewPointRotation; // out

	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.f, 2.f, FColor::Red, true);

	
}

bool AGun::HasNullPointers() const
{
	if (!MuzzleEffect)
	{
		UE_LOG(LogTemp, Error, TEXT("Muzzle effect not found!"));
		return true;
	}

	if (!OwnerController)
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerController not found!"));
		return true;
	}

	return false;
}