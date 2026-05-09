// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_Rifle.h"

#include "Character/GAM_PlayerCharacter.h"

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
	const FVector EndLocation = StartLocation + (ShotDirection * TraceLength);
	
	// 4. Set Query Params
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(PlayerCharacterOwner);
	QueryParams.bTraceComplex = true;
	
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
		// TODO: Apply Damage
	}
	
	if (bDebug)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Yellow, false, 2.0f, 0, 0.5f);
	}
}

void AGAM_Rifle::StopAction()
{
	Super::StopAction();
}
