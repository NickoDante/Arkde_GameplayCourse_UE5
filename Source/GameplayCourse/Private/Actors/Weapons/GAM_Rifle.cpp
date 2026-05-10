// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_Rifle.h"

#include "Character/GAM_PlayerCharacter.h"
#include "DataAssets/GAM_WeaponData.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystem.h"

AGAM_Rifle::AGAM_Rifle()
{
	
}

void AGAM_Rifle::StartAction()
{
	Super::StartAction();
	
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
	const FVector EndLocation = StartLocation + (ShotDirection * WeaponData->GetTraceLength());
	
	// 4. Set Query Params
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(PlayerCharacterOwner);
	QueryParams.bTraceComplex = true;
	
	// 5. Make the LineTrace
	const FTransform MuzzleTransform = PlayerCharacterOwner->GetSocketTransform(WeaponData->GetMuzzleSocketName());
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
		AActor* HitActor = HitResult.GetActor();
		if (IsValid(HitActor))
		{
			UGameplayStatics::ApplyPointDamage(HitActor, WeaponData->GetDamage(), ShotDirection, HitResult, PlayerCharacterOwner->GetInstigatorController(), this, WeaponData->GetDamageType());
		}
	}
	
	if (bDebug)
	{
		// Debug from camera to point view
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Yellow, false, 2.0f, 0, 0.5f);
		
		// Debug from Weapon to point view
		DrawDebugLine(GetWorld(), ShotStart, ShotEnd , FColor::White, false, 2.0f, 0, 0.5f);
	}
	
	if (IsValid(FiringEffect))
	{
		const FRotator FiringRotation = UKismetMathLibrary::FindLookAtRotation(ShotStart, ShotEnd);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FiringEffect, ShotStart, FiringRotation);
	}
}
