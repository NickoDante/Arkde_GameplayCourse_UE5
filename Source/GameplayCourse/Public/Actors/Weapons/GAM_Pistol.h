// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAM_Weapon.h"
#include "GAM_Pistol.generated.h"

class AGAM_PistolProjectile;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Pistol : public AGAM_Weapon
{
	GENERATED_BODY()

public:

	AGAM_Pistol();
	
	virtual void StartAction() override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Pistol")
	TSubclassOf<AGAM_PistolProjectile> ProjectileActorClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "Arkde|Pistol")
	TObjectPtr<AGAM_PistolProjectile> ProjectileActor;
};
