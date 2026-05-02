// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GAM_Interactable.h"
#include "GAM_BaseInteractable.generated.h"

class USphereComponent;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_BaseInteractable : public AActor, public IGAM_Interactable
{
	GENERATED_BODY()

public:
	
	AGAM_BaseInteractable();
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> InteractCollision;
	
	UFUNCTION()
	void OnOverlapStarted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnOverlapEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
