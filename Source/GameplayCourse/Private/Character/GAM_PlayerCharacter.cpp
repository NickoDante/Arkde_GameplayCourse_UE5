// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAM_PlayerCharacter.h"

#include "Actors/Weapons/GAM_Weapon.h"
#include "Camera/CameraComponent.h"
#include "DataAssets/GAM_WeaponData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/GAM_Interactable.h"

// Sets default values
AGAM_PlayerCharacter::AGAM_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
	// Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	
	CameraBoom->TargetArmLength = 180.0;
	CameraBoom->bUsePawnControlRotation = true;
	
	CameraBoom->SocketOffset = FVector(0.0f, 75.0f, 65.0f);
	
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 15.0f;
	
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 7.5f;
	CameraBoom->CameraLagMaxDistance = 7.5f;
	
	// Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

void AGAM_PlayerCharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	if (bIsAiming)
	{
		OutLocation = FollowCamera->GetComponentLocation();
		OutRotation = FollowCamera->GetComponentRotation();
	}
	else
	{
		if (CurrentWeapon)
		{
			UGAM_WeaponData* WeaponData = CurrentWeapon->GetWeaponData();
			const FName SocketName = IsValid(WeaponData) ? WeaponData->GetMuzzleSocketName() : NAME_None;
			FTransform SocketTransform = GetSocketTransform(SocketName);
			
			OutLocation = SocketTransform.GetLocation();
			OutRotation = GetActorRotation();
		}
		else
		{
			Super::GetActorEyesViewPoint(OutLocation, OutRotation);
		}
	}
}

void AGAM_PlayerCharacter::StartAim()
{
	bIsAiming = true;
	BP_StartAim();
}

void AGAM_PlayerCharacter::StopAim()
{
	bIsAiming = false;
	BP_StopAim();
}

void AGAM_PlayerCharacter::StartInteract()
{
	if (IsValid(CurrentInteractable) && CurrentInteractable->GetClass()->ImplementsInterface(UGAM_Interactable::StaticClass()))
	{
		IGAM_Interactable::Execute_Interact(CurrentInteractable, this);
	}
}

void AGAM_PlayerCharacter::StartWeaponAction()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartAction();
	}
}

void AGAM_PlayerCharacter::StopWeaponAction()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();
	}
}

void AGAM_PlayerCharacter::SetCurrentWeapon(AGAM_Weapon* NewWeapon)
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->Release();
	}
	
	CurrentWeapon = NewWeapon;
}

FTransform AGAM_PlayerCharacter::GetSocketTransform(const FName& SocketName) const
{
	return GetMesh()->GetSocketTransform(SocketName);
}

void AGAM_PlayerCharacter::StartMelee()
{
	bIsDoingMelee = true;
	BP_StartMelee();
}

void AGAM_PlayerCharacter::StopMelee()
{
	bIsDoingMelee = false;
	BP_StopMelee();
}

