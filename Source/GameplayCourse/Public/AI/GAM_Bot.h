// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GAM_Bot.generated.h"

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
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
