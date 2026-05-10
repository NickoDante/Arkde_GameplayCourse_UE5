// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_Pistol.h"

#include "Actors/Weapons/GAM_PistolProjectile.h"
#include "Character/GAM_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AGAM_Pistol::AGAM_Pistol()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGAM_Pistol::StartAction()
{
	Super::StartAction();
	
	if (!IsValid(ProjectileActorClass))
	{
		return;
	}
	
	if (!IsValid(PlayerCharacterOwner))
	{
		return;
	}
	
	// 1. Calculate the position where the player is looking at
	FVector EyeLocation;
	FRotator EyeRotation;
	PlayerCharacterOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	// 2. Calculate the Start Location
	const FVector StartLocation = EyeLocation;
	
	// 3. Calculate the End Location
	const FVector ShotDirection = EyeRotation.Vector();
	const FVector EndLocation = StartLocation + (ShotDirection * TraceLength);
	
	// 4. Set Query Params
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(PlayerCharacterOwner);
	QueryParams.bTraceComplex = true;
	
	// 5. Make the LineTrace
	const FTransform MuzzleTransform = PlayerCharacterOwner->GetSocketTransform(MuzzleSocketName);
	FVector ShotStart = MuzzleTransform.GetLocation();
	FVector ShotEnd = EndLocation;
	
	FHitResult HitResult;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		QueryParams
		);
	
	if (bHit)
	{
		ShotEnd = HitResult.ImpactPoint;
	}
	
	// 6. Spawn the projectile with the calculated data
	FRotator FiringRotation = UKismetMathLibrary::FindLookAtRotation(ShotStart, ShotEnd);
	
	FTransform ProjectileTransform;
	ProjectileTransform.SetLocation(ShotStart);
	ProjectileTransform.SetRotation(FiringRotation.Quaternion());
	
	ProjectileActor = GetWorld()->SpawnActor<AGAM_PistolProjectile>(ProjectileActorClass, ProjectileTransform);
	if (IsValid(ProjectileActor))
	{
		ProjectileActor->SetOwner(this);
	}
}


