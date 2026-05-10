// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAM_PistolProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_PistolProjectile : public AActor
{
	GENERATED_BODY()

public:

	AGAM_PistolProjectile();
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
