// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAM_BaseInteractable.h"
#include "GAM_Key.generated.h"

UCLASS()
class GAMEPLAYCOURSE_API AGAM_Key : public AGAM_BaseInteractable
{
	GENERATED_BODY()

public:

	AGAM_Key();
	
	virtual void Interact_Implementation(class APawn* InstigatorPawn) override;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> KeyMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arkde|Key")
	FName ID;
};
