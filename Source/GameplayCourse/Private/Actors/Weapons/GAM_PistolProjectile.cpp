// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/GAM_PistolProjectile.h"

#include "Actors/Weapons/GAM_Weapon.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AGAM_PistolProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AGAM_Weapon* WeaponOwner = Cast<AGAM_Weapon>(GetOwner());
	if (IsValid(WeaponOwner))
	{
		AActor* CharacterOwner = WeaponOwner->GetOwner();
		if (IsValid(CharacterOwner))
		{
			const float Damage = WeaponOwner->GetDamage();
			const FVector HitDirection = GetActorForwardVector();
		
			FHitResult HitResult;
			HitResult.ImpactPoint = GetActorLocation();
		
			UGameplayStatics::ApplyPointDamage(OtherActor, Damage, HitDirection, HitResult, CharacterOwner->GetInstigatorController(), WeaponOwner, WeaponOwner->GetDamageType());
		}
	}
	
	Super::NotifyActorBeginOverlap(OtherActor);
	
	Destroy();
}
