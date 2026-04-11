// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAM_Door.generated.h"

class UStaticMeshComponent;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Door : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGAM_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorFrame;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Door;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Door")
	uint8 bHasOpenImmediately : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Door")
	uint8 bIsOpening : 1;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	void OpenImmediately();
	
	void StartOpen();
	
	void StopOpen();
	
};
