// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GAM_Bot.h"

#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Character/GAM_PlayerCharacter.h"
#include "Components/GAM_HealthComponent.h"
#include "Kismet/GameplayStatics.h"

AGAM_Bot::AGAM_Bot()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCanEverAffectNavigation(false);
	SetRootComponent(MeshComponent);
	
	HealthComponent = CreateDefaultSubobject<UGAM_HealthComponent>("HealthComponent");
	
	bDebug = true;
	MinDistanceToTarget = 150.f;
	ForceMagnitude = 2000.f;
}

void AGAM_Bot::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	PlayerReference = Cast<AGAM_PlayerCharacter>(PlayerPawn);
	
	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthChangedDelegate.AddUniqueDynamic(this, &AGAM_Bot::OnTakingDamage);
		HealthComponent->OnDeadDelegate.AddUniqueDynamic(this, &AGAM_Bot::OnDead);
	}
	
	BotMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComponent->GetMaterial(0));
	
	TargetPoint = GetNextPathPoint();
}

void AGAM_Bot::OnTakingDamage(float Health, float MaxHealth)
{
	if (IsValid(BotMaterial))
	{
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);
	}
}

void AGAM_Bot::OnDead()
{
	Explode();
}

void AGAM_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveToTargetPoint();
}

FVector AGAM_Bot::GetNextPathPoint() const
{
	if (!IsValid(PlayerReference))
	{
		return GetActorLocation();
	}
	
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(
		GetWorld(), 
		GetActorLocation(), 
		PlayerReference);
	
	if (IsValid(NavigationPath) && NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}
	
	return GetActorLocation();
}

void AGAM_Bot::MoveToTargetPoint()
{
	const FVector ToTargetPoint = TargetPoint - GetActorLocation();
	const float Distance = ToTargetPoint.Size();
	
	if (Distance <= MinDistanceToTarget)
	{
		TargetPoint = GetNextPathPoint();
	}
	else
	{
		const FVector Direction = ToTargetPoint.GetSafeNormal();
		const FVector ForceDirection = Direction * ForceMagnitude;
		
		MeshComponent->AddForce(ForceDirection, NAME_None, true);
	}
	
	if (bDebug)
	{
		DrawDebugSphere(
			GetWorld(), 
			TargetPoint, 
			30.f,
			12,
			FColor::Purple,
			false,
			0.0,
			0,
			1.f);
	}
}

void AGAM_Bot::Explode()
{
	Destroy();
}


