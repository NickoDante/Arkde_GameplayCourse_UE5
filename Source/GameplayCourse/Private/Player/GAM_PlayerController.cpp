// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GAM_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Character/GAM_PlayerCharacter.h"

void AGAM_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem))
	{
		return;
	}
	
	for (UInputMappingContext* Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ThisClass::StartAim);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ThisClass::StopAim);
}

void AGAM_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	PlayerCharacter = Cast<AGAM_PlayerCharacter>(aPawn);
}

void AGAM_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn()))
	{
		return;
	}
	
	const FVector2D MovementVector = Value.Get<FVector2D>().GetSafeNormal();
	
	const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void AGAM_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>().GetSafeNormal();
	
	const bool bIsPlayerAiming = IsValid(PlayerCharacter) && PlayerCharacter->IsAiming();
	const float LookMultiplier = bIsPlayerAiming ? 0.5f : 1.0f;
	
	AddYawInput(LookVector.X * LookMultiplier);
	AddPitchInput(LookVector.Y * LookMultiplier);
}

void AGAM_PlayerController::StartAim()
{
	if (!IsValid(PlayerCharacter))
	{
		return;
	}
	
	PlayerCharacter->StartAim();
}

void AGAM_PlayerController::StopAim()
{
	if (!IsValid(PlayerCharacter))
	{
		return;
	}
	
	PlayerCharacter->StopAim();
}
