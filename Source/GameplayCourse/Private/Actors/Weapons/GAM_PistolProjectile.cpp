// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_PistolProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

AGAM_PistolProjectile::AGAM_PistolProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	SetRootComponent(ProjectileMesh);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	InitialLifeSpan = 5.0f;
}
