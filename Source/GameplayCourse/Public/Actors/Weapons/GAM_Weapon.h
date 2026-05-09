// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/GAM_BaseInteractable.h"
#include "GAM_Weapon.generated.h"

class UStaticMeshComponent;
class ACharacter;
class AGAM_PlayerCharacter;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Weapon : public AGAM_BaseInteractable
{
	GENERATED_BODY()

public:

	AGAM_Weapon();
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	void StartAction();
	void StopAction();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Debug")
	uint8 bDebug : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Weapon")
	FName AttachSocketName;
	
	UPROPERTY()
	TObjectPtr<AGAM_PlayerCharacter> PlayerCharacterOwner;
	
	void PickUp(ACharacter* Character);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PickUp(ACharacter* Character);
};
