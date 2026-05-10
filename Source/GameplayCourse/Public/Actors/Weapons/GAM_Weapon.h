// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/GAM_BaseInteractable.h"
#include "GAM_Weapon.generated.h"

class UStaticMeshComponent;
class ACharacter;
class AGAM_PlayerCharacter;
class UDamageType;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Weapon : public AGAM_BaseInteractable
{
	GENERATED_BODY()

public:

	AGAM_Weapon();
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	virtual void StartAction();
	virtual void StopAction();
	
	FName GetMuzzleSocketName() const { return MuzzleSocketName; }
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Debug")
	uint8 bDebug : 1;
	
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
	
	UPROPERTY()
	TObjectPtr<AGAM_PlayerCharacter> PlayerCharacterOwner;
	
	void PickUp(ACharacter* Character);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PickUp(ACharacter* Character);
};
