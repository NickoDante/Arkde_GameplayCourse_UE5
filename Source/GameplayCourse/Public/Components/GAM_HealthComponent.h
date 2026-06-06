// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GAM_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGAM_OnDeadSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGAM_OnHealthChangedSignature, float, Health, float, MaxHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEPLAYCOURSE_API UGAM_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UGAM_HealthComponent();
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FGAM_OnDeadSignature OnDeadDelegate;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FGAM_OnHealthChangedSignature OnHealthChangedDelegate;
	
	bool IsAlive() const { return !bIsDead; }
	bool IsDead() const { return bIsDead; }

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Debug")
	uint8 bDebug : 1;
	
	UPROPERTY(BlueprintReadOnly, Category = "Arkde|Health")
	uint8 bIsDead : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Health")
	float MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, Category = "Arkde|Health")
	float Health;
	
	UFUNCTION()
	void TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealthValue(const float NewValue);
};
