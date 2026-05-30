// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GAM_Bot.generated.h"

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Bot")
	uint8 bDebug : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Bot|Properties")
	float MinDistanceToTarget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Bot|Properties")
	float ForceMagnitude;
	
	UPROPERTY(BlueprintReadOnly)
	FVector TargetPoint;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGAM_PlayerCharacter> PlayerReference;
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	
private:
	
	FVector GetNextPathPoint() const;
	
	void MoveToTargetPoint();
};
