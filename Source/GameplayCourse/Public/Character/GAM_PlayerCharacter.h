// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GAM_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AGAM_PlayerCharacter();
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> FollowCamera;
};
