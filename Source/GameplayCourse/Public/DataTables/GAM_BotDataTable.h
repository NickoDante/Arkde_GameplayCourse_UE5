// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GAM_BotDataTable.generated.h"

USTRUCT(BlueprintType)
struct FGAM_BotData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDistanceToTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForceMagnitude;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionDamage = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionRadius = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinPlayerRadius {300.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CountingRate {0.25f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SelfDamage {10.f};
	
	FGAM_BotData () : 
		MinDistanceToTarget(150.f),
		ForceMagnitude(2000.f),
		ExplosionDamage(100.0f),
		ExplosionRadius(300.f),
		MinPlayerRadius(300.f),
		CountingRate(0.25f),
		SelfDamage(10.f)
	{}
};

/**
 * 
 */
UCLASS()
class GAMEPLAYCOURSE_API UGAM_BotDataTable : public UDataTable
{
	GENERATED_BODY()
};
