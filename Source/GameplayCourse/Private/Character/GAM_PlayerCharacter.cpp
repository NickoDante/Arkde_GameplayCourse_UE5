// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAM_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

