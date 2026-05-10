// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GAM_WeaponData.generated.h"

class UDamageType;

/**
 * 
 */
UCLASS()
class GAMEPLAYCOURSE_API UGAM_WeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	FName GetAttachSocketName() const { return AttachSocketName; }
	float GetTraceLength() const { return TraceLength; }
	FName GetMuzzleSocketName() const { return MuzzleSocketName; }
	float GetDamage() const { return Damage; }
	TSubclassOf<UDamageType> GetDamageType() const { return DamageType; }
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Weapon")
	FName AttachSocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Weapon")
	float TraceLength;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Weapon")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Weapon")
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Weapon")
	TSubclassOf<UDamageType> DamageType;
};
