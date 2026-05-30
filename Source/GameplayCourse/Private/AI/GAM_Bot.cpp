// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GAM_Bot.h"

AGAM_Bot::AGAM_Bot()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetSimulatePhysics(true);
	SetRootComponent(MeshComponent);
}

void AGAM_Bot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGAM_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


