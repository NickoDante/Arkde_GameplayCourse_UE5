// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAM_Weapon.h"
#include "GAM_Rifle.generated.h"

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Rifle : public AGAM_Weapon
{
	GENERATED_BODY()

public:

	AGAM_Rifle();
	
	virtual void StartAction() override;
	virtual void StopAction() override;
};
