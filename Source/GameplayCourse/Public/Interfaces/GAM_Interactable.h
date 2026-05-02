// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GAM_Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGAM_Interactable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAYCOURSE_API IGAM_Interactable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(APawn* InstigatorPawn);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanInteract();
};
