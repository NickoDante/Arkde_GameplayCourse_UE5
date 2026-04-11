// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayCourse/Public/Actors/GAM_Door.h"
#include "Components/StaticMeshComponent.h"

AGAM_Door::AGAM_Door()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;
	
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
	
	bHasOpenImmediately = false;
	bIsOpening = false;
}

// Called when the game starts or when spawned
void AGAM_Door::BeginPlay()
{
	Super::BeginPlay();
	
	if (bHasOpenImmediately)
	{
		OpenImmediately();
		UE_LOG(LogTemp, Log, TEXT("Door opens immediately in C++"));
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, TEXT("Door opens immediately in C++!"));		
	}
	else
	{
		StartOpen();
	}
}

// Called every frame
void AGAM_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsOpening && IsValid(Door))
	{
		FRotator CurrentRotator = Door->GetRelativeRotation();
		float NewYaw = CurrentRotator.Yaw - 1.0f;
		Door->SetRelativeRotation(FRotator(0.0f, NewYaw, 0.0f));
		
		if (NewYaw < -90.0f)
		{
			StopOpen();
		}
	}
}

void AGAM_Door::OpenImmediately()
{
	if (IsValid(Door))
	{
		Door->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void AGAM_Door::StartOpen()
{
	bIsOpening = true;
}

void AGAM_Door::StopOpen()
{
	bIsOpening = false;
}

