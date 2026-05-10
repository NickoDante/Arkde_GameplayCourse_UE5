// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_PistolProjectile.h"

AGAM_PistolProjectile::AGAM_PistolProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	SetRootComponent(ProjectileMesh);
}
