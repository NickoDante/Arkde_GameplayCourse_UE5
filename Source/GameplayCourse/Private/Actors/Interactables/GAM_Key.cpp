// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Interactables/GAM_Key.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AGAM_Key::AGAM_Key()
{
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("KeyMesh");
	SetRootComponent(KeyMesh);
	
	if (InteractCollision)
	{
		InteractCollision->SetupAttachment(KeyMesh);
	}
	
	ID = FName("Key ID");
}

void AGAM_Key::Interact_Implementation(class APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	
	Destroy();
}
