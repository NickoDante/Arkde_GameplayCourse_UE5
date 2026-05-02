// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Interactables/GAM_BaseInteractable.h"

#include "Character/GAM_PlayerCharacter.h"
#include "Components/SphereComponent.h"

AGAM_BaseInteractable::AGAM_BaseInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InteractCollision = CreateDefaultSubobject<USphereComponent>("InteractCollision");
	InteractCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AGAM_BaseInteractable::Interact_Implementation(APawn* InstigatorPawn)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 
			5.0f, 
			FColor::Cyan, 
			FString::Printf(TEXT("You are interacting with '%s'"), *GetName()));
	}
}

void AGAM_BaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(InteractCollision))
	{
		InteractCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnOverlapStarted);
		InteractCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnOverlapEnded);
	}
}

void AGAM_BaseInteractable::OnOverlapStarted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("AGAM_BaseInteractable::OnOverlapStarted: Overlap Started!"));
	}
	
	AGAM_PlayerCharacter* PlayerCharacter = Cast<AGAM_PlayerCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetCurrentInteractable(this);
	}
}

void AGAM_BaseInteractable::OnOverlapEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("AGAM_BaseInteractable::OnOverlapEnded: Overlap Ended!"));
	}
	
	AGAM_PlayerCharacter* PlayerCharacter = Cast<AGAM_PlayerCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetCurrentInteractable(nullptr);
	}
}

