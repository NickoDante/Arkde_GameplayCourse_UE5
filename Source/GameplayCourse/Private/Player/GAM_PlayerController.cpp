// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GAM_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

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
}

void AGAM_PlayerController::Move()
{
	UE_LOG(LogTemp, Warning, TEXT("AGAM_PlayerController::Move()"));
}

void AGAM_PlayerController::Look()
{
	UE_LOG(LogTemp, Warning, TEXT("AGAM_PlayerController::Look()"));
}
