// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_Weapon.h"

#include "Components/SphereComponent.h"
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
	
	AttachSocketName = NAME_None;
}

void AGAM_Weapon::Interact_Implementation(APawn* InstigatorPawn)
{
	ACharacter* Character = Cast<ACharacter>(InstigatorPawn);
	if (IsValid(Character))
	{
		PickUp(Character);
	}
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
	AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocketName);
	
	// Disable interactions
	if (InteractCollision)
	{
		InteractCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	// Set weapons owner
	SetOwner(Character);
	
	BP_PickUp(Character);
}


