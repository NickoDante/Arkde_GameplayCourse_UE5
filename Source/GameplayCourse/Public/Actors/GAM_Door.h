// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/GAM_BaseInteractable.h"
#include "GAM_Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGAM_OnOpenedSignature);

class UStaticMeshComponent;

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Door : public AGAM_BaseInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGAM_Door();

protected:
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	virtual bool CanInteract_Implementation() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorFrame;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Door;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Door")
	uint8 bHasOpenImmediately : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arkde|Door")
	uint8 bIsOpening : 1;
	
	uint8 bIsFullyOpened : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arkde|Door")
	FName ID;
	
	UPROPERTY(BlueprintAssignable)
	FGAM_OnOpenedSignature OnOpenedDelegate;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PlayDoorSound(const bool bCanOpen);
	
	UFUNCTION(BlueprintCallable)
	void OpenImmediately();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	void StartOpen();
	
	void StopOpen();
	
};
