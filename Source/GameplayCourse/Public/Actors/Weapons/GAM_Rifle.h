// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAM_Weapon.h"
#include "GAM_Rifle.generated.h"

class UParticleSystem;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Rifle : public AGAM_Weapon
{
	GENERATED_BODY()

public:

	AGAM_Rifle();
	
	virtual void StartAction() override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Rifle")
	TObjectPtr<UParticleSystem> FiringEffect;
};
