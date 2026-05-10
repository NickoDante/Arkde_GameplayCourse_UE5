// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_Pistol.h"

#include "Actors/Weapons/GAM_PistolProjectile.h"
#include "Character/GAM_PlayerCharacter.h"

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
	
	FTransform ProjectileTransform = PlayerCharacterOwner->GetSocketTransform(MuzzleSocketName);
	GetWorld()->SpawnActor<AGAM_PistolProjectile>(ProjectileActorClass, ProjectileTransform);
}


