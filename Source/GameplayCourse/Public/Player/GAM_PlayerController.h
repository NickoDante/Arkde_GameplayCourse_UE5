// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GAM_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class GAMEPLAYCOURSE_API AGAM_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	virtual void SetupInputComponent() override;
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs|Movement")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs|Movement")
	TObjectPtr<UInputAction> LookAction;
	
	void Move();
	
	void Look();
	
};
