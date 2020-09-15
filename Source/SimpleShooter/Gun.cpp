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
	if (!OwnerController) SetupController();
	if (HasNullPointers()) return;
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComponent, FName(TEXT("MuzzleFlashSocket")));

	FShootData ShootData(GetWorld(), OwnerController, MaxRange);

	if (!ShootData.HasHit) return;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldEffect, ShootData.HitResult.ImpactPoint, ShootData.OppositeRotation);
		
	if (!ShootData.HitResult.GetActor()) return;
	
	FPointDamageEvent DamageEvent(Damage, ShootData.HitResult, ShootData.OppositeDirection, nullptr);
	ShootData.HitResult.GetActor()->TakeDamage(Damage, DamageEvent,OwnerController, this);
		
	if (!bDrawDebugHelpers) return;
	DrawDebugPoint(GetWorld(), ShootData.HitResult.ImpactPoint, 10.f, FColor::Red, true);
}

void AGun::SetupController()
{
	APawn* GunOwner = Cast<APawn>(GetOwner());
	if (GunOwner)
	{
		OwnerController = GunOwner->GetController();
	}
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