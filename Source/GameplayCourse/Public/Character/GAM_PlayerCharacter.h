// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GAM_PlayerCharacter.generated.h"

class UGAM_HealthComponent;
class AGAM_Weapon;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AGAM_PlayerCharacter();
	
	virtual void BeginPlay() override;
	
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;
	
	void StartAim();
	
	void StopAim();
	
	void StartInteract();
	
	bool IsAiming() const { return bIsAiming; }
	
	void SetCurrentInteractable(AActor* NewInteractable) { CurrentInteractable = NewInteractable; }
	
	void AddKey(const FName& NewID) { OwningKeyIDs.Add(NewID); }
	void RemoveKey(const FName& ID) { OwningKeyIDs.Remove(ID); }
	bool HasKey(const FName& ID) { return OwningKeyIDs.Contains(ID); }
	
	void StartWeaponAction();
	void StopWeaponAction();
	void SetCurrentWeapon(AGAM_Weapon* NewWeapon);
	FTransform GetSocketTransform(const FName& SocketName) const;
	bool CanUseWeapon() const;
	
	void StartMelee();
	UFUNCTION(BlueprintCallable)
	void StopMelee();
	bool CanMelee() const;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UGAM_HealthComponent> HealthComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "Arkde|Aim")
	uint8 bIsAiming : 1;
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractable;
	
	TArray<FName> OwningKeyIDs;
	
	UPROPERTY(BlueprintReadOnly, Category = "Arkde|Weapon")
	TObjectPtr<AGAM_Weapon> CurrentWeapon;
	
	UPROPERTY(BlueprintReadOnly, Category = "Arkde|Melee")
	uint8 bIsDoingMelee : 1;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartAim();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StopAim();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartMelee();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_StopMelee();
	
	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth);
	
	UFUNCTION()
	void OnDead();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnHealthChanged(float Health, float MaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnDead();
};
