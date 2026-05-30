// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAM_Definitions.h"
#include "GameFramework/Pawn.h"
#include "GAM_Bot.generated.h"

class UGAM_HealthComponent;
class AGAM_PlayerCharacter;
class UStaticMeshComponent;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Bot : public APawn
{
	GENERATED_BODY()

public:
	
	AGAM_Bot();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UGAM_HealthComponent> HealthComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Bot")
	uint8 bDebug : 1;
	
	uint8 bIsCountingToDestroy:1;
	
	float MinDistanceToTarget;
	
	float ForceMagnitude;
	
	float ExplosionDamage;
	
	float ExplosionRadius;
	
	float MinPlayerRadius;
	
	float CountingRate;
	
	float SelfDamage;
	
	UPROPERTY(BlueprintReadOnly)
	FVector TargetPoint;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGAM_PlayerCharacter> PlayerReference;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BotMaterial;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Bot|Effects")
	TObjectPtr<UParticleSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Bot|Properties")
	TObjectPtr<UDataTable> BotDataTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Bot|Properties")
	EGAM_Difficulty BotDifficulty;
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnTakingDamage(float Health, float MaxHealth);
	
	UFUNCTION()
	void OnDead();

public:
	
	virtual void Tick(float DeltaTime) override;
	
private:
	
	void InitProperties();
	
	FVector GetNextPathPoint() const;
	
	void MoveToTargetPoint();
	
	void Explode();
	
	void CheckCountDownToDestroy();
	
	void StartCountDownToDestroy();
	
	void MakeSelfDamage();
};
