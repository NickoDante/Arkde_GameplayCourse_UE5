// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GAM_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AGAM_PlayerCharacter;
/**
 * 
 */
UCLASS()
class GAMEPLAYCOURSE_API AGAM_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* aPawn) override;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGAM_PlayerCharacter> PlayerCharacter;
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs|Movement")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs|Movement")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs|Aim")
	TObjectPtr<UInputAction> AimAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Arkde|Inputs|Interact")
	TObjectPtr<UInputAction> InteractAction;
	
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);
	
	void StartAim();
	
	void StopAim();
	
	void StartInteract();
};
