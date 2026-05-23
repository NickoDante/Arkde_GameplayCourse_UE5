// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GAM_HealthComponent.h"

UGAM_HealthComponent::UGAM_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	MaxHealth = 100.0f;
}

void UGAM_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	
	AActor* MyOwner = GetOwner();
	if (IsValid(MyOwner))
	{
		MyOwner->OnTakeAnyDamage.AddUniqueDynamic(this, &ThisClass::TakingDamage);
	}
}

void UGAM_HealthComponent::TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0.0)
	{
		return;
	}
	
	const float NewHealth = Health - Damage;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	
	OnHealthChangedDelegate.Broadcast(Health, MaxHealth);
	
	if (bDebug && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			3.0f,
			FColor::Yellow,
			FString::Printf(TEXT("'%s' receives '%f' damage. Health: %f/%f"), *GetOwner()->GetName(), Damage, Health, MaxHealth));
	}
	
	if (Health == 0.0)
	{
		bIsDead = true;
		OnDeadDelegate.Broadcast();
	}
}


