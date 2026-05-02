// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Interactables/GAM_Key.h"

#include "Character/GAM_PlayerCharacter.h"
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

void AGAM_Key::Interact_Implementation(APawn* InstigatorPawn)
{
	AGAM_PlayerCharacter* PlayerCharacter = Cast<AGAM_PlayerCharacter>(InstigatorPawn);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->AddKey(ID);
		GEngine->AddOnScreenDebugMessage(-1, 
			5.0f, 
			FColor::Green, 
			FString::Printf(TEXT("AGAM_Key::Interact --> Adding Key with ID: %s"), *ID.ToString()));
	}
	
	Destroy();
}
