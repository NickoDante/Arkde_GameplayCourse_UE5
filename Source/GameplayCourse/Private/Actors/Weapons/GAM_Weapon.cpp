// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_Weapon.h"

#include "Character/GAM_PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/GAM_WeaponData.h"
#include "GameFramework/Character.h"

AGAM_Weapon::AGAM_Weapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);
	
	if (InteractCollision)
	{
		InteractCollision->SetupAttachment(WeaponMesh);
	}
	
	if (IsValid(InteractWidgetComponent))
	{
		InteractWidgetComponent->SetupAttachment(WeaponMesh);
	}
}

void AGAM_Weapon::Interact_Implementation(APawn* InstigatorPawn)
{
	ACharacter* Character = Cast<ACharacter>(InstigatorPawn);
	if (IsValid(Character))
	{
		PickUp(Character);
	}
}

void AGAM_Weapon::StartAction()
{
	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 
			5.0f, 
			FColor::Green,
			FString::Printf(TEXT("Starting Weapon: %s"), *GetName()));
	}
}

void AGAM_Weapon::StopAction()
{
	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 
			5.0f, 
			FColor::Orange,
			FString::Printf(TEXT("Stopping Weapon: %s"), *GetName()));
	}
}

void AGAM_Weapon::Release()
{
	Destroy();
}

void AGAM_Weapon::PickUp(ACharacter* Character)
{
	if (!IsValid(Character))
	{
		return;
	}
	
	USkeletalMeshComponent* SkeletalMeshComponent = Character->GetMesh();
	if (!IsValid(SkeletalMeshComponent))
	{
		return;
	}
	
	// Attach to the character
	AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponData->GetAttachSocketName());
	
	// Disable interactions
	if (InteractCollision)
	{
		InteractCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	// Set weapons owner
	PlayerCharacterOwner = Cast<AGAM_PlayerCharacter>(Character);
	if (IsValid(PlayerCharacterOwner))
	{
		PlayerCharacterOwner->SetCurrentWeapon(this);
	}
	
	SetOwner(Character);
	
	BP_PickUp(Character);
}


